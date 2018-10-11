////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    Simple Bluetooth Messaging
//
// Small sample program to send messages on a periodic basis to another NXT over BT. Simultaneously
// another task is scanning for new incoming bluetooth messages and processing them. The same program
// can be executed in both NXTs of a Bluetooth pair.
//
// Remember to manually set up the connection between the two NXTs before running the program.
//
// Program progress can be monitored via ROBOTC's debugger window and examining the values of global
// variables in the debugger as the program is running.
//
// Messages are a very simplified form of communication between a pair of NXTs over Bluetooth. THe content
// of a message is limited to three 16-bit data fields. A common interface is used with both the
// NXT Bluetooth communications and the RCX Infrared communications.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma platform(NXT)

long nElapsedTime = 0;
long nNearEndSent = 0;
long nNearEndRead = 0;
int  nFarEndSent  = 0;
int  nFarEndRead  = 0;
long nSendBusy    = 0;

int  nMessage  = 0;
long nRcxNoMsg = 0;
long nReadOutOfSequence  = 0;  // Out Of Sequence

long nMsgXmit     = 0;

//
// Function Prorotype Declarations
//
task sendMessages();
void checkBTLinkConnected();
void readMessages();


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
	checkBTLinkConnected();
	eraseDisplay();
	bNxtLCDStatusDisplay = true; // Enable top status line display
	wait1Msec(500);
	startTask(sendMessages);
	readMessages();
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Send Messages Task
//
// Periodically send a message containing a few progress indicators.
//
// Messages are sent every 25 milliseconds or so. This is no real benefit of sending at a faster rate
// since the Bluecore module collects many periodic user packets into a larger bluetooth packet that is
// then transmitted all at once. So even though it appears more messages are being sent the value of
// shorter interval is marginal because of the bundling.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

task sendMessages()
{
	const int kMinTimeBetweenMsg = 50;
	//long nInterMsgTime;
	static long nLastSendTime = 0;

	while (true)
	{
		//
		// Delay between messages.
		//
		if ((nPgmTime - nLastSendTime) < kMinTimeBetweenMsg)
		{
			wait1Msec(6);
			continue;
		}

		if (bBTBusy)
		{
			++nSendBusy;
			wait1Msec(5);
			continue;
		}

	  ++nNearEndSent;
		++nMsgXmit;
		if (nMsgXmit == 0)
			nMsgXmit = 1; // Don't send illegal value
	  sendMessageWithParm(nMsgXmit, nNearEndSent, nNearEndRead);
	  nLastSendTime = nPgmTime;
	}
	return;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Receive Messages
//
// Far end device is periodically sending message. Here we loop continuously absorbing/processing
// the message.
//
// Far end increments the message / mailbox by one over the last message sent. we can use this to
// validate that the messages arrive in order and are not dropped.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

void readMessages()
{
	static int nLastMessage = 0;

	while (true)
	{
	  nMessage = message;
	  if (nMessage != 0)
	  {
	  	++nNearEndRead;// Keep a running count of the number of messages successfully read
	  	if (nMessage != (nLastMessage + 1))
	  	  ++nReadOutOfSequence;
	  	nLastMessage = nMessage;
	  	nFarEndSent  = messageParm[1];
	  	nFarEndRead  = messageParm[2];
	  	ClearMessage();
			nElapsedTime  = nPgmTime;
		}
		else
		  ++nRcxNoMsg;
		wait1Msec(1);
	}
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
