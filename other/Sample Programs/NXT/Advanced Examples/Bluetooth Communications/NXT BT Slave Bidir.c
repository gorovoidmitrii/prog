////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    Bluetooth Operational Tests
//
// ROBOTC provides access and control over the NXT Bluetooth link. This program contains many samples
// to illustrate this functionality.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                  waitForBTCommandToComplete
//
// Most BT commands take several "time slices" to complete. The NXT CPU sends a command request to the
// Bluetooth chip. The chip processes the command and then sends a reply message back to the NXT CPU
// containing the results.
//
// The NXT firmware internally does a 'time out' test to check if the command has completed so a user
// application program can rely on this and not do its own testing. There are three different timeout
// values used by the firmware
//    0.5 second for commands that only operate on the internal variables in the bluetooth chip
//    2.0 seconds for commands that manipulate the bluetooth radio
//   30.0 seconds for commands like 'search', 'connect', etc that are setting up or tearing down links
//
////////////////////////////////////////////////////////////////////////////////////////////////////////



long nSendCnt = 0;
long nGoodMessages = 0;

long nRcvCnt = 0;
long nReadCnt = 0;

//#define Master

#if defined(Master)

  const int kBTPort = 1;

#else

  const int kBTPort = 0;

#endif

void readDataMsg();

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Send Messages Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

const int kMaxSizeOfMessage = 5;


void sendDataMsg()
{
	const TMailboxIDs kQueueID = mailbox1;
	ubyte nXmitBuffer[kMaxSizeOfMessage] = {0x01, 0x02, 0x03, 0x04, 0x00}; // For NXT-G compatability, last byte of message must be zero because of string messsages.
	const bool bWaitForReply = false;
  TFileIOResult nBTCmdErrorStatus;
  string sMsg;
	string sTemp;

	sMsg  = "Send Data ";
	sTemp = nSendCnt;
	sMsg += sTemp;
	displayTextLine(3, sMsg);
  nBTCmdErrorStatus = cCmdMessageWriteToBluetooth(kBTPort, nXmitBuffer, kMaxSizeOfMessage, kQueueID);
  if ((nBTCmdErrorStatus == ioRsltSuccess) || (nBTCmdErrorStatus == ioRsltCommPending))
  {
  	++nGoodMessages;
		sMsg  = "Send OK ";
		sTemp = nGoodMessages;
		sMsg += sTemp;
		displayTextLine(4, sMsg);
  }
	while (nBluetoothCmdStatus == ioRsltCommPending)
	{
		wait1Msec(1);
	}
	return;
}

task sendMessages()
{
	//
	// Send 1M messages
	//
	for (nSendCnt = 0; nSendCnt < 1000000; ++nSendCnt)
	{
		sendDataMsg();
		readDataMsg();
		wait1Msec(1);
		//EndTimeSlice();
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Receive Messages Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

void readDataMsg()
{
	const TMailboxIDs kQueueID = mailbox1;

	const bool bWaitForReply = false;
  TFileIOResult nBTCmdErrorStatus;
	int nSizeOfMessage;
	ubyte nRcvBuffer[kMaxSizeOfMessage * 5];
	string sMsg;
	string sTemp;

	sMsg  = "Read Data ";
	sTemp = nRcvCnt;
	sMsg += sTemp;
	displayTextLine(6, sMsg);
	nSizeOfMessage = cCmdMessageGetSize(kQueueID);
	if (nSizeOfMessage <= 0)
	{
		wait1Msec(1);
		return;
	}
	if (nSizeOfMessage > kMaxSizeOfMessage)
	  nSizeOfMessage = kMaxSizeOfMessage;
  nBTCmdErrorStatus = cCmdMessageRead(nRcvBuffer, nSizeOfMessage, kQueueID);
  if (nBTCmdErrorStatus == ioRsltSuccess)
  {
		// Keep a running count of the number of messages successfully read
  	++nReadCnt;
		sMsg  = "Mag Read ";
		sTemp = nReadCnt;
		sMsg += sTemp;
		displayTextLine(7, sMsg);
	}
	return;
}

/*
task getMessages()
{
	//
	// Send 1M messages
	//
	for (nRcvCnt = 0; nRcvCnt < 1000000; ++nRcvCnt)
	{
		readDataMsg();
		wait1Msec(1);
	}
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Main Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	//
	// Test Ability to Turn Bluetooth On or Off
	//
	bNxtLCDStatusDisplay = true;
	wait1Msec(2000);

#if defined(Master)

	StartTask(sendMessages);
	//StartTask(getMessages);

#else

	startTask(sendMessages);
	//StartTask(getMessages);

#endif

while ((nSendCnt < 1000000) && (nRcvCnt < 1000000))
	{
		wait1Msec(1000);
	}
	return;
}
