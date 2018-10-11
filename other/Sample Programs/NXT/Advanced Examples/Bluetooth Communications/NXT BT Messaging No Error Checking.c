
////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    Bluetooth Sample Program
//
// ROBOTC provides easy send and receive of messages over Bluetooth. This sample program illustrate the
// basic concept. Bluetooth error checking has been removed from the program to make it easier to
// follow the program logic.
//
// There are other sample programs in the ROBOTC distribution that include Bluetooth using error
// checking.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT)

long nLastXmitTimeStamp = nPgmTime;
long nDeltaTime         = 0;

const int kTimeBetweenXmit = 30;

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Check to See if Bluetooth Link is Connection
//
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
//                                        Send Messages Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

const int kMaxSizeOfMessage = 5;
const TMailboxIDs kQueueID = mailbox1;

void sendDataMsg()
{
  ubyte nXmitBuffer[kMaxSizeOfMessage] = {0x01, 0x02, 0x03, 0x04, 0x00}; // For NXT-G compatability, last byte of message must be zero because of string messsages.
  const bool bWaitForReply = false;
  TFileIOResult nBTCmdErrorStatus;

  nDeltaTime = nPgmTime - nLastXmitTimeStamp;
  if (nDeltaTime < kTimeBetweenXmit)
    return;

  if (bBTBusy)
    return;

  nBTCmdErrorStatus = cCmdMessageWriteToBluetooth(nXmitBuffer, kMaxSizeOfMessage, kQueueID);
  switch (nBTCmdErrorStatus)
  {
  case ioRsltSuccess:
  case ioRsltCommPending:
    nLastXmitTimeStamp = nPgmTime;
    break;

  case ioRsltCommChannelBad:
  default:
    break;
  }
  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Receive Messages Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

void readMultipleDataMsgs()
{
  TFileIOResult nBTCmdRdErrorStatus;
  int nSizeOfMessage;
  ubyte nRcvBuffer[kMaxSizeOfMessage];

  while (true)
  {
    // Check to see if a message is available

    nSizeOfMessage = cCmdMessageGetSize(kQueueID);
    if (nSizeOfMessage <= 0)
    {
      wait1Msec(1);    // Give other tasks a chance to run
      break;           // No more message this time
    }

    if (nSizeOfMessage > kMaxSizeOfMessage)
      nSizeOfMessage = kMaxSizeOfMessage;
    nBTCmdRdErrorStatus = cCmdMessageRead(nRcvBuffer, nSizeOfMessage, kQueueID);

    // Add your code to process the message here.
  }
  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Main Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  bNxtLCDStatusDisplay = true;
  wait1Msec(2000); // Give time to start the program at the far end as well

  //
  // Send and receive 1M messages
  //
  for (long nSendTotal = 0; nSendTotal < 1000000; ++nSendTotal)
  {
    checkBTLinkConnected();
    sendDataMsg();
    readMultipleDataMsgs();
    wait1Msec(1);
  }

  return;
}
