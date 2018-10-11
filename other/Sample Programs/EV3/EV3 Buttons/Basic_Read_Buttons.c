
task main()
{
	// Use this if you want to use the back button as well
  // Not advisable.
	// setBlockBackButton(true);

	displayCenteredTextLine(1, "Pressed button:");
	// Loop forever
	while (true)
	{
		// Possible values for getButtonPress() are:
		// buttonNone 	= 0,
		// buttonUp 		= 1,
		// buttonEnter 	= 2,
		// buttonDown 	= 3,
		// buttonRight 	= 4,
		// buttonLeft 	= 5,
		// buttonBack 	= 6,
		// buttonAny		= 7
		if (getButtonPress(buttonUp))
			displayCenteredBigTextLine(4, "Up");
		else if (getButtonPress(buttonEnter))
			displayCenteredBigTextLine(4, "Enter");
		else if (getButtonPress(buttonDown))
			displayCenteredBigTextLine(4, "Down");
		else if (getButtonPress(buttonRight))
			displayCenteredBigTextLine(4, "Right");
		else if (getButtonPress(buttonLeft))
			displayCenteredBigTextLine(4, "Left");
		else if (getButtonPress(buttonAny))
			displayCenteredBigTextLine(4, "Any");
		else
			displayCenteredBigTextLine(4, "");

		// Wait 20 ms, this gives us 50 readings per second
		sleep(20);
	}
	return;
}
