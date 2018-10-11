

task main()
{
	const tMotor encoder = motorA;
	int nLastLastX;
	int nLastLastY;
	int nLastX;
	int nLastY;

	nMotorEncoder[encoder] = 0;
  displayTextLine(0, "   Sine Test");
  displayTextLine(2, "Connect Motor to");
  displayTextLine(3, "   Port A. ");
  displayTextLine(4, "Rotate it for");
  displayTextLine(5, "Trig demo on LCD");
  displayTextLine(6, "screen");
  bFloatDuringInactiveMotorPWM = true;

	while (nMotorEncoder[encoder] == 0)
	{
		// Wait for some movement on the motor encoder.
	}

	//
	// Clear screen and setup variables
	//
	eraseDisplay();
	nLastX = 32; // out of range to force initial display
	nLastY = 32; // out of range to force initial display
	nLastLastX = 32; // out of range to force initial display
	nLastLastY  = 32; // out of range to force initial display
	//
	// Repeat forever display angle and sine on the NXT LCD display
	//
	while (true)
	{
		int nAngle;
		int X;
		int Y;
		float fSine;
		float fCosine;

		nLastLastX = nLastX = 32;
		//
		// Prevent 16-bit overflow of the motor encoder
		//
		if ((nMotorEncoder[encoder] >= 18000) || (nMotorEncoder[encoder] <= -18000))
			nMotorEncoder[encoder] = 0;

	  //
	  // Normalize
	  //
	  nAngle = -nMotorEncoder[encoder];
	  nAngle %= 360;
	  if (nAngle < 0)
	    nAngle += 360;
	  nAngle = 360 - nAngle; // Reverse direction because it's wrong

    fSine   =   sin((PI / 180.0) * nAngle);
    fCosine =   cos(nAngle * (PI / 180.0));
    X = 32 + (float) (fCosine   * 31);
    Y = 32 + (float) (fSine * 31);
	  if ((nLastX != X)  || (nLastY != Y) || (nLastLastX != X)  || (nLastLastY != Y))
	  {
	  	//
	  	// Position has changed. Redraw screen
	  	//
	  	eraseRect(0, 62, 62, 0);
		  //
		  // Draw horizontal and vertical lines for right-angle triangle.
		  //
		  drawLine(32, 32, X, 32); // Vertical    line length is proportional to cosine
		  drawLine( X, 32, X,  Y); // Horizaontal line length is proportional to sine

		  //
		  // Draw the last three lines so that we have some "persistence" instead of a faint line
		  //  when rotating the motor encoder fast.
		  //
		  drawLine(32, 32, nLastLastX, nLastLastY);
		  drawLine(32, 32, nLastX, nLastY);
		  drawLine(32, 32, X,  Y);

		  //
		  // Numeric display of 'sin' and 'cos' values on right of screen
		  //
		  displayStringAt(65, 60, "Sine");
		  displayStringAt(65, 52, "%1.4f", fSine);

		 	displayStringAt(65, 38, "Angle");
		  displayStringAt(65, 30, "%3d ", nAngle);


		  displayStringAt(65, 16, "Cosine");
		  displayStringAt(65,  8, "%1.4f",   fCosine);

		  drawEllipse(0, 62, 62, 0);
		  nLastLastX = nLastX;
		  nLastLastY = nLastY;
		  nLastX = X;
		  nLastY = Y;
			wait1Msec(29);
		}
  }
  return;
}
