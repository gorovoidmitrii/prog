////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    Bluetooth Operational Tests
//
// ROBOTC provides access and control over the NXT Bluetooth link. This program contains many samples
// to illustrate this functionality.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT)

long nElapsedTime;
float fThroughput = 0;
long nSendTotal = 0;
long nSendGood = 0;
long nSendBad = 0;
long nSendBusy = 0;

long nRcvCnt = 0;
long nReadCnt = 0;
long nReadBad = 0;

long nMsgCntRcv = 0;
long nMsgCntXmit  = 0;


void readAndSendBluetoothMessages();
void sendMessages();
void checkBTLinkConnected();

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Main Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	checkBTLinkConnected();
	eraseDisplay();
	bNxtLCDStatusDisplay = true;
	wait1Msec(500);

	sendMessages();

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Send Messages Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

const int kMaxSizeOfMessage = 5;
const TMailboxIDs kQueueID = mailbox1;


void sendDataMsg()
{
	ubyte nXmitBuffer[kMaxSizeOfMessage];
	const bool bWaitForReply = false;
  TFileIOResult nBTCmdErrorStatus;
	long   nLastSentMsg = -1;

	if (nLastSentMsg >= nMsgCntRcv)
	{
		playSound(soundBeepBeep);
		return;
	}
	nMsgCntXmit = nMsgCntRcv + 1;
	nXmitBuffer[0] = nMsgCntXmit;
	nXmitBuffer[1] = nMsgCntXmit >>  8;
	nXmitBuffer[2] = nMsgCntXmit >> 16;
	nXmitBuffer[3] = nMsgCntXmit >> 24;
	displayTextLine(1, "Send      %6d", nSendTotal);

	nBTCmdErrorStatus = nBluetoothCmdStatus;
	if (nBluetoothCmdStatus == ioRsltInProgress)
	{
		displayTextLine(2, "Send Busy %6d", ++nSendBusy);
		return;
	}

  nBTCmdErrorStatus = cCmdMessageWriteToBluetooth(nBTCurrentStreamIndex, nXmitBuffer, kMaxSizeOfMessage, kQueueID);
  switch (nBTCmdErrorStatus)
  {
	case ioRsltSuccess:
	case ioRsltCommPending:
	  nLastSentMsg = nMsgCntRcv;
	  displayTextLine(3, "Send OK   %6d", ++nSendGood);
	  break;

	case ioRsltCommChannelBad:
	default:
		displayTextLine(4, "Send Bad  %6d", ++nSendBad);
		break;
	}


	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////


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

void purgeBluetoothInput()
{
  /*
  TFileIOResult nBTCmdRdErrorStatus;
	int nSizeOfMessage;
	ubyte nRcvBuffer[kMaxSizeOfMessage * 5];
  static long nLastSendTime = 0;

	while (true)
	{
		nSizeOfMessage = cCmdMessageGetSize(kQueueID);
		if (nSizeOfMessage <= 0)
			break;
		if (nSizeOfMessage > kMaxSizeOfMessage)
		  nSizeOfMessage = kMaxSizeOfMessage;
	  nBTCmdRdErrorStatus = cCmdMessageRead(nRcvBuffer, nSizeOfMessage, kQueueID);
	}
	*/
	return;
}

void readAndSendBluetoothMessages()
{
	const bool bWaitForReply = false;
  TFileIOResult nBTCmdRdErrorStatus;
	int nSizeOfMessage;
	ubyte nRcvBuffer[kMaxSizeOfMessage * 5];
  static long nLastSendTime = 0;

	//sMsg  = "Rd Tries ";
	//sTemp = nRcvCnt;
	//sMsg += sTemp;
	//displayTextLine(6, sMsg);
	while (true)
	{
		displayTextLine(5, "Rd Tries  %6d", ++nRcvCnt);
		nSizeOfMessage = cCmdMessageGetSize(kQueueID);
		if (nSizeOfMessage <= 0)
		{
			wait1Msec(1);
		  if ((nPgmTime - nLastSendTime) > 200)
		  {
		  	sendDataMsg();
		  	nLastSendTime = nPgmTime;
		  }
			break;
		}
		if (nSizeOfMessage > kMaxSizeOfMessage)
		  nSizeOfMessage = kMaxSizeOfMessage;
	  nBTCmdRdErrorStatus = cCmdMessageRead(nRcvBuffer, nSizeOfMessage, kQueueID);
	  if (nBTCmdRdErrorStatus == ioRsltSuccess)
	  {
			// Keep a running count of the number of messages successfully read
	  	displayTextLine(6, "Read OK   %6d", ++nReadCnt);
	  	nMsgCntRcv   = 0xFF & nRcvBuffer[3];    nMsgCntRcv <<= 8;
	  	nMsgCntRcv  |= 0xFF & nRcvBuffer[2];  	nMsgCntRcv <<= 8;
	  	nMsgCntRcv  |= 0xFF & nRcvBuffer[1];    nMsgCntRcv <<= 8;
	  	nMsgCntRcv  |= 0xFF & nRcvBuffer[0];
			nElapsedTime = nPgmTime;
	  	fThroughput = nElapsedTime / (float) nReadCnt;
		}
	  else
	  	displayTextLine(6, "Read Bad  %6d", ++nReadBad);

	  if (nBTCmdRdErrorStatus == ioRsltSuccess)
	  {
	  	sendDataMsg();
	  	nLastSendTime = nPgmTime;
	  }
	}
	nElapsedTime = nPgmTime;
	return;
}

void sendMessages()
{
	purgeBluetoothInput();
	//
	// Send 1M messages
	//
	for (nSendTotal = 0; nSendTotal < 1000000; ++nSendTotal)
	{
		checkBTLinkConnected();
		readAndSendBluetoothMessages();
		if (false && (nBTCurrentStreamIndex != 0))
		{
			for (int i = 0; i < 300; ++i)
			{
				if (!bBTBusy)
				{
					btRequestLinkQuality(nBTCurrentStreamIndex);
					while (bBTBusy)
					{}
					break;
				}
			}

		}
	}
}
