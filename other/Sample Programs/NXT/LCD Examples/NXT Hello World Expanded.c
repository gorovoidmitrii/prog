///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                             Hello World
//
// ROBOTC has funciton to draw text on the NXT LCD display.
//
// This is the 'classic' "Hello World" program.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT)   // Program applies only to the NXT platform
#pragma DebuggerWindows("nxtLCDScreen")

{
	//
	// Display it on the second line of the screen using standard 8-pixel high font
	//
	displayTextLine(1, "   Hello World  ");
	//
	// Display it using bigger 16-pixel high font
	//
	displayBigStringAt(20, 36, "Hello");
	displayBigStringAt(20, 20, "World");
	playSound(soundFastUpwardTones);
	wait1Msec(10000);

	//
	// End with a sound
	//
	playSound(soundBeepBeep);
	while(bSoundActive)
	{} // wait for sound to complete
	return;
}
