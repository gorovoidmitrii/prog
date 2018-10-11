//////////////////////////////////////////////////////////////////////////////
//
//										VEX IQ Button Test Routine
//
// This program visually displays the VEX IQ buttons on the LCD screen. The
// each button either an empty or filled rectange is drawn.
//
// NOTE: The EXIT button will terminate the program. So do not try to test it!
//
//////////////////////////////////////////////////////////////////////////////

void drawButton(bool bButtonPressed, int left, int top)
{
  // Draw either a filled or empty rectangle on the screen

	if (bButtonPressed)
    fillRect(left,      top,      left + 9, top + 12);
  else
  {
    drawRect(left,      top,      left + 9, top + 12);
    eraseRect(left + 1, top + 1,  left + 8, top + 11);
  }
}

task main()
{
  setUserDebugWindow(true);
  displayCenteredTextLine(2, "Button Test");
  while (true)
  {
    drawButton((nLCDButtons & kButtonUp)    != 0,   2,  30);
	  drawButton((nLCDButtons & kButtonDown)  != 0,   2,   2);
	  drawButton((nLCDButtons & kButtonSelect)!= 0, 116,  30);

	  // Exit button (currently) EXITs program. Do not use!
	  //drawButton((nLCDButtons & kButtonExit)  != 0, 116,   2);
	  sleep(10);
	}
}
