////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    Bluetooth Operational Tests
//
// ROBOTC provides access and control over the NXT Bluetooth link. This program contains many samples
// to illustrate this functionality.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT)

long nElapsedTime = 0;
float fThroughput = 0;
long nSendTotal = 0;
long nSendGood = 0;
long nSendBad = 0;
long nSendBusy1 = 0;
long nSendBusy2 = 0;

long nRcvTries = 0;
long nReadCnt = 0;
long nReadBad = 0;

long nLastXmitTimeStamp = nPgmTime;
long nLastRcvdTimeStamp = nPgmTime;
long nDeltaTime         = 0;

const int kTimestampHistogramSize = 41;
int nRcvHistogram[kTimestampHistogramSize];
int nXmitHistogram[kTimestampHistogramSize];

const int kTimeBetweenXmit = 30;

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Send Messages Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

const int kMaxSizeOfMessage = 5;
const TMailboxIDs kQueueID = mailbox1;

void readDataMsg();

void sendDataMsg()
{
	ubyte nXmitBuffer[kMaxSizeOfMessage] = {0x01, 0x02, 0x03, 0x04, 0x00}; // For NXT-G compatability, last byte of message must be zero because of string messsages.
	const bool bWaitForReply = false;
  TFileIOResult nBTCmdErrorStatus;

	displayTextLine(1, "Send      %6d", nSendTotal);

	nDeltaTime = nPgmTime - nLastXmitTimeStamp;
	if (nDeltaTime < kTimeBetweenXmit)
	{
		displayTextLine(2, "Bsy%6d %6d", nSendBusy1, ++nSendBusy2);
		return;
	}

	if (bBTBusy)
	{
		displayTextLine(2, "Bsy%6d %6d", ++nSendBusy1, nSendBusy2);
		return;
	}


  nBTCmdErrorStatus = cCmdMessageWriteToBluetooth(nXmitBuffer, kMaxSizeOfMessage, kQueueID);
  switch (nBTCmdErrorStatus)
  {
	case ioRsltSuccess:
	case ioRsltCommPending:
		displayTextLine(3, "Send OK   %6d", ++nSendGood);
		nDeltaTime = nPgmTime - nLastXmitTimeStamp;
		nLastXmitTimeStamp = nPgmTime;
		if (nDeltaTime >= kTimestampHistogramSize)
		  nDeltaTime = kTimestampHistogramSize - 1;
		++nXmitHistogram[nDeltaTime];
		break;

	case ioRsltCommChannelBad:
	default:
		displayTextLine(4, "Send Bad  %6d", ++nSendBad);
		break;
	}
	return;
}

void checkBTLinkConnected()
{
	if (nBTCurrentStreamIndex >= 0)
	  return;

	playSound(soundLowBuzz);
	playSound(soundLowBuzz);
	eraseDisplay();
	displayCenteredTextLine(3, "BT not");
	displayCenteredTextLine(4, "Connected");
	wait1Msec(3000);
	stopAllTasks();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Receive Messages Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////


void readDataMsg()
{

	const bool bWaitForReply = false;
  TFileIOResult nBTCmdRdErrorStatus;
	int nSizeOfMessage;
	ubyte nRcvBuffer[kMaxSizeOfMessage * 5];

	while (true)
	{
		displayTextLine(5, "Rd Tries  %6d", ++nRcvTries);

		// Check to see if a message is available

		nSizeOfMessage = cCmdMessageGetSize(kQueueID);
		if (nSizeOfMessage <= 0)
		{
			wait1Msec(1);    // Give other tasks a chance to run
			break;           // No message this time
		}

	  if (nSizeOfMessage > kMaxSizeOfMessage)
	    nSizeOfMessage = kMaxSizeOfMessage;
	  nBTCmdRdErrorStatus = cCmdMessageRead(nRcvBuffer, nSizeOfMessage, kQueueID);
	  if (nBTCmdRdErrorStatus == ioRsltSuccess)
	  {

			nDeltaTime = nPgmTime - nLastRcvdTimeStamp;
			nLastRcvdTimeStamp = nPgmTime;
			if (nDeltaTime >= kTimestampHistogramSize)
			  nDeltaTime = kTimestampHistogramSize - 1;
			++nRcvHistogram[nDeltaTime];
			// Keep a running count of the number of messages successfully read
	  	displayTextLine(6, "Read OK   %6d", ++nReadCnt);
 		  fThroughput = nElapsedTime / (float) nReadCnt;
		}
	  else
	    displayTextLine(7, "Read Bad  %6d", ++nReadBad);
	}
	return;
}

void sendMessages()
{
	//
	// Send and receive 1M messages
	//
	for (nSendTotal = 0; nSendTotal < 1000000; ++nSendTotal)
	{
		checkBTLinkConnected();
		sendDataMsg();
		readDataMsg();
		nElapsedTime = nPgmTime;
		wait1Msec(1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Main Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	bNxtLCDStatusDisplay = true;
	memset(nRcvHistogram,  0, sizeof(nRcvHistogram));
	memset(nXmitHistogram, 0, sizeof(nXmitHistogram));
	wait1Msec(2000);
	sendMessages();
	return;
}
