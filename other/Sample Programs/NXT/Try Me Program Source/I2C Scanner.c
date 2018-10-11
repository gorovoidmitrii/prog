
//////////////////////////////////////////////////////////////////////////////////////////
//
//                      Sensor Port Scanner for I2C Devices
//
// This is a handy utility program to scan sensor ports for I2C devices.
//
// It is based on a program original written by Dr. Nitin Patil of Mindsensors and modified
// by Scott Briscoe.
//
//////////////////////////////////////////////////////////////////////////////////////////

#pragma fileExtension("rtm")
#pragma platform("NXT")

const int i2cScanVersion          = 0x00;
const int i2cScanManufacturer     = 0x08;
const int i2cScanDeviceName       = 0x10;

typedef struct
{
	tSensors nPort;
	int      nDeviceAddress;
	string   sVersion;
	string   sManufacturer;
	string   sDeviceType;
} TDeviceInfo;

TI2CStatus nStatus;
byte replyMsg[10];
static int nNumbOfDevices;
const int kArraySize = 12;
TDeviceInfo nSensors[kArraySize];

//////////////////////////////////////////////////////////////////////////////
//
//      Read the  data from I2C sensor
//
//
/////////////////////////////////////////////////////////////////////////////

bool scanI2CforResponse(int nSensorPort, int nScanID)
{
	//TI2CStatus nStatus;
	//
	// Message to see if "sensor" is responding to I2C
	//
  byte i2cScanMsg[] =
  {
  	2,                  // Message size
  	nScanID,            // Address
  	i2cScanDeviceName
  };

  while (true)
  {
  	// Wait for I2C bus to be ready
  	nStatus = nI2CStatus[nSensorPort];
  	if (nStatus != STAT_COMM_PENDING)
  	  break;
  }

  sendI2CMsg((tSensors) nSensorPort, &i2cScanMsg[0], 8);
  nStatus = nI2CStatus[nSensorPort];
  while (true)
  {
  	nStatus = nI2CStatus[nSensorPort];
  	switch (nStatus)
  	{
  	case STAT_COMM_PENDING:
  	  continue;

  	case NO_ERR:
		  readI2CReply((tSensors) nSensorPort, &replyMsg[0], 8);
			nStatus = nI2CStatus[nSensorPort];
			return nStatus == NO_ERR;

  	case ERR_COMM_CHAN_NOT_READY:
    case ERR_COMM_BUS_ERR:
	    return false;

		default:
			ASSERT(false);
			return false;
  }
 }
}

bool scanI2Cfor8Bytes(int nSensorPort, int nScanID, int nLocation, string &sReply)
{
  //
	// Message to scan "sensor" is responding to I2C
	//
  byte i2cscanMsgWithReply[] =
  {
  	2,                  // Message size
  	nScanID,             // Address
  	nLocation           // Internal address location
  };


  while (true)
  {
  	// Wait for I2C bus to be ready
  	nStatus = nI2CStatus[nSensorPort];
  	if (nStatus != STAT_COMM_PENDING)
  	  break;
  }

  memset(replyMsg, 0, sizeof(replyMsg));
  //nI2CBytesReady[nSensorPort] = 0;
  sendI2CMsg((tSensors) nSensorPort, &i2cscanMsgWithReply[0], 8);                                        // Send the message
  nStatus = nI2CStatus[nSensorPort];
  if (nStatus == ERR_COMM_BUS_ERR)
    return false;

  while (true)
  {
  	// Wait for I2C bus to be ready
  	nStatus = nI2CStatus[nSensorPort];
  	if (nStatus != STAT_COMM_PENDING)
  	  break;
  }
	switch (nStatus)
	{
	case NO_ERR:
		break;

	case ERR_COMM_CHAN_NOT_READY:
		sReply = "Not Rdy";
		return false;

	case ERR_COMM_BUS_ERR:
		sReply = "Bus Err";
		return false;

	case ERR_COMM_CHAN_INVALID:
		sReply = "Bad Chnl";
		return false;


	default:
		sReply = "I2C Err";
		return false;
	}
  readI2CReply((tSensors) nSensorPort, &replyMsg[0], 8);
  if (replyMsg[0] == 0x00)
  {
  	sReply = "Bad Data";
  	return false;
  }
  strcpy(sReply, &replyMsg[0]);

  return true;
}


//////////////////////////////////////////////////////////////////////////////
//
//      Sensors that the scan will identify
//
/////////////////////////////////////////////////////////////////////////////

bool isRXMux(int nSensorPort)
{
  // Device does not return a name, but has a fixed I2C address //
  if (nSensorPort == 0x7E)
    return true;
  else
    return false;
}


void displaySensorInfo(int nIndex)
{
	if (nIndex < kArraySize)
	{
		displayCenteredBigTextLine(0, nSensors[nIndex].sDeviceType);
		displayTextLine(2, "Port:S%1d Addr:%02X", (int) nSensors[nIndex].nPort + 1, nSensors[nIndex].nDeviceAddress);
	  displayTextLine(3, "Vendor: %s", nSensors[nIndex].sManufacturer);
	  displayTextLine(4, "Version: %s", nSensors[nIndex].sVersion);
	}

	displayStringAt(6, 19, "%d Devices Total", nNumbOfDevices);
  return;
}



void scanSensorPort(int nPort)
{
  int nScanAddress;
  TSensorTypes nSaveSensorType;
  //bool bDeviceFoundOnPort = false;

  nSaveSensorType = SensorType[nPort];
	SensorType[nPort] = sensorI2CCustom;
	//SensorType[nPort] = sensorI2CCustomFast; //sensorI2CCustomFast9V;

  writeDebugStreamLine("Scanning port S%1d...", nPort);
  for (nScanAddress = 0x02; nScanAddress < 0xFF; nScanAddress += 0x02)
  {
  	displayCenteredTextLine(7, "Scanning: S%1d/%02X", (int) nPort + 1, nScanAddress);

    if (!scanI2CforResponse(nPort, nScanAddress))
    {
    	// Scan twice. The Codatext sensor needs to wake up first.

    	if (!scanI2CforResponse(nPort, nScanAddress))
        continue;
    }

    writeDebugStreamLine("   Found I2C at address 0x%02X on port S%1d", nScanAddress, nPort);
    //bDeviceFoundOnPort = true;
    if (nNumbOfDevices < kArraySize)
    {
    	nSensors[nNumbOfDevices].nPort = (tSensors) nPort;
	    nSensors[nNumbOfDevices].nDeviceAddress = nScanAddress;
	    if (isRXMux(nPort))
	    {
	    	nSensors[nNumbOfDevices].sManufacturer = "MndSensor";
	    	nSensors[nNumbOfDevices].sDeviceType   = "RXMux";
	    	nSensors[nNumbOfDevices].sVersion      = "";
	    }
	    else
	    {
	    	scanI2Cfor8Bytes(nPort, nScanAddress, i2cScanManufacturer, nSensors[nNumbOfDevices].sManufacturer);
	    	scanI2Cfor8Bytes(nPort, nScanAddress, i2cScanDeviceName,   nSensors[nNumbOfDevices].sDeviceType);
	    	scanI2Cfor8Bytes(nPort, nScanAddress, i2cScanVersion,      nSensors[nNumbOfDevices].sVersion);
	    }
	  }
	  ++nNumbOfDevices;
	  displaySensorInfo(nNumbOfDevices - 1);
  }
  writeDebugStreamLine("...Finished Scanning port S%1d", nPort);
  displayTextLine(7, "");

  SensorType[nPort] = nSaveSensorType;
}


void displayMenu(int nIndex)
{
	string sMenu;

	if (nNumbOfDevices <= 1)
    sMenu = "     ReScan     ";
	else if (nIndex == 0)
    sMenu = "     ReScan NEXT";
  else if (nIndex >= (nNumbOfDevices - 1))
    sMenu = "PREV ReScan     ";
  else
    sMenu = "PREV ReScan NEXT";

  displayCenteredTextLine(7, sMenu);
}

void doButtons()
{
	int nCurrDisplay;

	if (nNumbOfDevices == 0)
	  return;


	nCurrDisplay = 0;
	while (true)
	{
		//
		// Some dummy code to do some work. In this case we'll simply display a count of the number of times
		// each button has been pressed.
		//
		TButtons nBtn;

	  displayMenu(nCurrDisplay);
	  displaySensorInfo(nCurrDisplay);


	  while (nNxtButtonPressed != -1) // wait for button release
	  {
	  }

	  while (true) // wait for button press
	  {
	  	nBtn = nNxtButtonPressed;
	  	if (nBtn != -1)
	  	  break;
	  }

	  switch (nBtn)
	  {
	  	case kRightButton:	if (nCurrDisplay < (nNumbOfDevices - 1)) ++nCurrDisplay;   			break;
			case kLeftButton:	  if (nCurrDisplay > 0)                   --nCurrDisplay;   			break;
			case kEnterButton:	return;   // will cause a rescan
		}
		//PlaySoundFile("! Click.rso");

  }
}

void StartupDisplay()
{
	displayCenteredBigTextLine(0, "I2C Scan");
	displayCenteredTextLine(3, "Program to scan");
	displayCenteredTextLine(4, "all sensor port");
	displayCenteredTextLine(5, "for I2C devices");
	displayCenteredTextLine(6, "Use keys to");
	displayCenteredTextLine(7, "scroll items");
	wait1Msec(1500);
	eraseDisplay();
	return;
}

//////////////////////////////////////////////////////////////////////////////
//
//      scans the port 1 and Display the results on NXT display
//
/////////////////////////////////////////////////////////////////////////////

task main()
{
	StartupDisplay();

	//
	// "Hi-jack" buttons for user program control.
	//
	nNxtButtonTask  = -2;   // Grab control of the buttons. '-2' is invalid for task, so no task will be
	                        // executed when a button is pressed.

	//
	// Note: program cannot be terminated if we hijack the 'exit' button. So there has to be an escape sequence
	//       that will return buttons to system control! We'll use a single click
	//
	nNxtExitClicks  = 1; // Triple clicking EXIT button will terminate program


  while (true)
  {
  	writeDebugStreamLine("");
  	nNumbOfDevices = 0;
  	scanSensorPort(S1);
	  scanSensorPort(S2);
	  scanSensorPort(S3);
	  scanSensorPort(S4);

	  doButtons();
	}
}
