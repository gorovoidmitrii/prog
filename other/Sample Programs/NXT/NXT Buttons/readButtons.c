
task main()
{
	// Set the number of  button presses for the exit button
  // to 2 before the program exits.  This allows you to use
  // this button in your own program without causing the
  // program to exit straight away.
	nNxtExitClicks = 3;

	displayCenteredTextLine(1, "Pressed button:");
	// Loop forever
	while (true)
	{
		// The nNxtButtonPressed variable contains
	  // the name of the button that is being pressed.
		// Read this and display its value on the screen.
		switch(nNxtButtonPressed)
		{
			case kNoButton: 		displayCenteredBigTextLine(4, "None"); 	break;
			case kLeftButton: 	displayCenteredBigTextLine(4, "Left"); 	break;
			case kEnterButton: 	displayCenteredBigTextLine(4, "Enter"); break;
			case kRightButton: 	displayCenteredBigTextLine(4, "Right"); break;
			case kExitButton: 	displayCenteredBigTextLine(4, "Exit"); 	break;
		}
		// Wait 20 ms, this gives us 50 readings per second
		sleep(20);
	}
	return;
}
