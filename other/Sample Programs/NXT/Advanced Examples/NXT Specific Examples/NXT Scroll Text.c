///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                             Test Text Line Scrolling on the NXT LCD Display
//
// ROBOTC has function to draw text on the NXT LCD display using the display as a scrolling window.
//
// There are eight lines of text on the NXT LCD.
//
// When the function is called:
//   1. The existing pixels on the LCD display are shifted up 8 pixels (i.e. the height of one text line).
//   2. The text is drawn on the bottom line of the NXT LCD screen.
//
// This sample progrm cycles 1000 times drawing a line of scrolling text.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT)   // Program applies only to the NXT platform

{
	int nIndex;

	for (nIndex = 0; nIndex < 1000; ++nIndex)
	{
  	scrollText("Scroll #%d.", nIndex);
		wait1Msec(400);
	}
	return;
}
