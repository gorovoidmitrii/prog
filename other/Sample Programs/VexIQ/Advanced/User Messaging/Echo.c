
// Check platform
#ifndef VexIQ
#error "This program is designed for the VexIQ platform"
#else

// Check if Smart Radio features are enabled
#ifndef VexIQ_SR
#error "This sample needs to have the smart radio features enabled"
#else

char usrMsg[41]; //extra byte for null char
task main()
{
	while (true)//continuously poll
	{
		if (userMessageAvailable())//checks for message
		{
			readUserMessage(usrMsg);//save user message to variable
			sendUserMessage(usrMsg);//send user message to bluetooth device
		}

		sleep(50);//pauses to avoiding hogging the CPU
	}
}

#endif // End Smart Radio features enabled check
#endif // End platform check
