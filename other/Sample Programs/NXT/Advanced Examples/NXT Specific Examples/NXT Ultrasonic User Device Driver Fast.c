///////////////////////////////////////////////////////////////////////////////
//
//                    Digital Sensor I2C Test Program
//
//
// This is a quick and simple program to test out the initial implementation of
// I2C messaging on the NXT in ROBOTC
//
// The program illustrates a user written device driver for the Lego Sonar sensor.
// The driver is very simple. It loops forever in a state machine generating
// messages to the SONAR sensor on port S1. The state machine has the following states
//
// 1. Initializaton.
//         - configures the sensor for custom I2C operation
//         - sends a initialization message to the SONAR sensor
//
// 2. Wait for Initialize complete
//        - waits for I2C idle signal indicating sensor has been initialized.
//        - Once idle, move to next state.
//
// 3. I2C messaging is idle.
//        - send a poll request to the SONAR sensor
//
// 4. Wait for Polling complete
//        - waits for the reply from the polling value.
//        - updates the "sensorValue" so that it can be used by other programs
//        - re-enters the polling stateBrake
//
// A future version of ROBOTC will improve on this initial implementation for
// better performance improvements. Most notably in the following:
//    - "int" (16-bit) variables are used to hold the arrays for sending and
//      receiving messages. Support for byte values is coming in a future release.
//    - The wait for reply message does an inline wait of 2-msec. A new function
//      will be implemented in the ROBOTC OS to "wait until either a timeout or a
//      specified event has happened". In this case the specified event will be a
//      change in the I2C signalling status.
//
//
// There are four "intrinsic" / "native" functions in ROBOTC for support of I2C
// sensor messages:
//
//   nI2CStatus      is an array that provides the current status of I2C messaging
//                   on the indexed port. The possible values are defined in the
//                   enum definition for 'TI2CStatus'
//
//   nI2CBytesReady  is an array indicating how many bytes are ready in the I2C
//                   input buffer for the selected port.
//
//	 sendI2CMsg(const tSensors nPort, int &sendMsg, const int nReplySize)
//										Sends a I2C message.
//                       nPort      - the sensor port (one of enums 'S1' to 'S4')
//                       sendMsg    - the first element of an array containing the
//                                    outgoing message.
//                       nReplySize - the number of reply bytes expected from msg.
//
//   void readI2CReply(const tSensors nPort, int &replyBytes, const int nBytesToRead)
//                    Reads the reply bytes for an I2C message.
//                       nPort        - the sensor port (one of enums 'S1' to 'S4')
//                       sendMsg      - the first element of an array where the reply
//                                      bytes should be copied
//                       nBytesToRead - the number of reply bytes to copy.
//
///////////////////////////////////////////////////////////////////////////////

//
// Use port S4 for the SONAR sensor
//
const tSensors kTestPort = S4;


///////////////////////////////////////////////////////////////////////////////
//
//                           SonarDeviceDriver
//
// ROBOTC is a multi-tasking system. For this example, the Sonar device driver
// has been written as a separate task to illustrate the capabilities of the system.
// In reality, a Lego SONAR sensor driver is directly implemented in the ROBOTC
// firmware.
//
// But this illustrates the development of a custom driver.
//
// Note the use of "SensorType[kTestPort] = Lowspeed_9V_Custom0;' assignment. This
// tells the ROBOTC firmware that this is a special I2C sensor with a user written
// device driver as a separate task.
//
// Also note the assignment of "SensorValue[kTestPort] = replyMsg[0];" within the
// driver where the value read via an I2C message is assigned to "SensorValue". This
// allows custom sensors to be seamlessly used by regular ROBOTC programs as
// "SensorValue" array is the internal array used to access the value of any of the
// four NXT sensor ports.
//
///////////////////////////////////////////////////////////////////////////////

const int kDelayBForHWStartup  = 15;
static int kDelayBetweenPolls  =  6;
int nNewValue;
int nStableValue;



task SonarDeviceDriver()
{
  //
  // Message constants for Lego Sonar (Ultra Sonic) sensor
  //
  const ubyte kSonarID               = 2;
  const ubyte kContinuousMeasurement = 2;
  const ubyte kInitializeSonar       = 0x41;
  const ubyte kReadSonarResult       = 0x42;

  //
  // I2C Message definition for SONAR sensor
  //
  static const byte kSonarInitialize[4] = {3, kSonarID, kInitializeSonar, kContinuousMeasurement};

  static const byte kSonarRead[3]       = {2, kSonarID, kReadSonarResult};
	const int kSonarReplySize     = 1;

	const int kOutOfRangeSonar    = 255; // Value returned when SONAR sensor was out of range

  //
  //  state machine for SONAR "device driver"
  //
  typedef enum TSonarState
  {
  	stateInitializing,
  	stateWaitForInitDone,
  	stateSendPollMessage,
  	stateWaitingForReply,
  } TSonarState;

  static TSonarState nSonarState;

  //
  // Keep some statistics on message counts and errors
  //
  static long nTotalInitErrors = 0;
  static long nTotalBusErrors  = 0;
  static long nTotalBusErrorsDuringStartup  = 0;
  static long nTotalValuesRead = 0;
  static float fAvgPollInterval = 0.0;
  static long nTotalReadAttempts = 0;
  static long nTotalRangeErrors  = 0;
  static long nTotalInitializations = 0;
  static long nPollStartTime    = 0;
  static long nValues[255];

  //
  // Set up port 'kTestPort' as user defined I2C sensor
  //
	memset(nValues, 0, sizeof(nValues));
  nI2CRetries = 0;
  SensorType[kTestPort] = sensorI2CCustom9V;
	nSonarState = stateInitializing;
  while(true)
  {
  	//
  	// Loop forever, polling the SONAR sensor
  	//
  	switch (nSonarState)
	  {
	  case stateInitializing:
	  	//
	  	// Send initialize message to Sonar sensor
	  	//
	  	sendI2CMsg(kTestPort, &kSonarInitialize[0], 0);
	  	++nTotalInitializations;
	  	nSonarState = stateWaitForInitDone;
	  	break;

	  case stateWaitForInitDone:
	  	//
	  	// Wait for Sonar sensor initialization to complete
	  	//
	  	switch (nI2CStatus[kTestPort])
	  	{
  		case NO_ERR:
		  	nSonarState = stateSendPollMessage;
		  	wait1Msec(kDelayBForHWStartup);
		  	nPollStartTime = nPgmTime;
		  	break;

  		case STAT_COMM_PENDING:
  			// Keep waiting for reply. I2C messaging is not complete
  			wait1Msec(1);
  			break;

  		default:
  		case (TI2CStatus) ERR_COMM_BUS_ERR:
		  	// re-initialize sensor. An I2C messaging error occurred.
		  	++nTotalInitErrors;
		  	nSonarState = stateInitializing;
		  	break;
			}
			break;

	  case stateSendPollMessage:
	  	//
	  	// Ready to send next polling message to Sensor
	  	//
	  	nI2CBytesReady[kTestPort] = 0; // Clear any pending bytes
	  	++nTotalReadAttempts;
	  	sendI2CMsg(kTestPort, &kSonarRead[0], kSonarReplySize);
	  	nSonarState = stateWaitingForReply;
	  	break;


	  case stateWaitingForReply:
	  	//
	  	// Wait for reply from SONAR sensor
	  	//
	  	switch (nI2CStatus[kTestPort])
	  	{
  		case NO_ERR:
		  	// Reply from SONAR sensor is ready to be read.
		  	//    - Update sensor value
		  	//    - Setup to send next polling message.

		  	byte replyMsg[1];

		  	//
		  	// Read the SONAR value and store it in "SensorValue" array so that it can be used
		  	// by other tasks as a standard sensor.
		  	//
		  	readI2CReply(kTestPort, &replyMsg[0], kSonarReplySize);
		  	if (replyMsg[0] != kOutOfRangeSonar)
		  	  SensorValue[kTestPort] = replyMsg[0];
		  	else
		  		++nTotalRangeErrors;
		  	++nTotalValuesRead;
	  		++nValues[replyMsg[0]];
		  	fAvgPollInterval = (nPgmTime - nPollStartTime) / (float) nTotalValuesRead;
		  	nSonarState = stateSendPollMessage;

		  	//
		  	// Sonar hardware delay. If the next poll request is immediately sent to
		  	// the SONAR sensor, then the message gets corrupted and generates a
		  	// 'ERR_COMM_BUS_ERR' error. So we'll put a little delay in here. I'm not
		  	// certain if this is a problem in the sonar sensor or a problem in the
		  	// bit-banged firmware trying to do too many things in one timeslice or
		  	// a problem in the ROBOTC firmware. The error message is that when
		  	// transmitting the next polling I2C message an ack is not received by the
		  	// the ARM processor after transmitting a byte of the message. Suspicion
		  	// is that this is bug in SONAR sensor.
		  	//
		  	// We really only need to wait a few msec to fix above problem. But might as
		  	// well go ahead and wait longer because sonar pulses are only sent out on a
		  	// 50 to 80 period.
		  	//
		  	if (kDelayBForHWStartup != 0)
					wait1Msec(kDelayBetweenPolls);
		  	break;

  		case STAT_COMM_PENDING:
  			// Insert short wait for reply. I2C messaging xmit/rcv is not complete
  			wait1Msec(1);
  			break;

  		default:
  		case (TI2CStatus) ERR_COMM_BUS_ERR:
		  	// re-initialize sensor. An I2C messaging error occurred.
		  	++nTotalBusErrors;
  			if (nTotalValuesRead <= 5)
  				++nTotalBusErrorsDuringStartup;
		  	nSonarState = stateInitializing;
  			wait1Msec(2);
		  	break;
			}
			break;
		}
	}
	return;
}

///////////////////////////////////////////////////////////////////////////////
//
//                                 task main()
//
// Multi-tasking illustration of user written I2C device driver. The task
// "SonarDeviceDriver" is the device driver.
//
// The "main" task is simply a copy of the "try me" program for SONAR sensor
// with the addition of one line to start the device driver task.
//
///////////////////////////////////////////////////////////////////////////////

task main()
{
  static long nSensorValueChanges = 0;
	//
	// Start the SONAR device driver
	//
	startTask(SonarDeviceDriver);

	//
	// Grab LCD screen and initialize display
	//
	displayTextLine(3, "Please use port:");
	displayTextLine(4, "4 - Ultrasonic");
	displayTextLine(5, "Listen Sound !");

	int nLastValue;
	static int nGoodRange = 3;

	wait1Msec(250);  // Ensure that SONAR is at a steady state value
	nStableValue = SensorValue[kTestPort];
	while (true)
	{
	  nNewValue = SensorValue[kTestPort];
	  playImmediateTone(nNewValue * 5 + 220, 1);
	  if (nNewValue != nLastValue)
	  {
	  	if (abs(nStableValue - nNewValue) > nGoodRange)
	  	  ++nSensorValueChanges;
	  }
	}
	return;
}
