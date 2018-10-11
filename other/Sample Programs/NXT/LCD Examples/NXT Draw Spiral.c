//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                      								Draws a Spiral on the NXT LCD
//
// Contributed by forum member "Count Olaf."
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT)
#pragma DebuggerWindows("nxtLCDScreen")

float nAngle;
int X, Y;
float nRadius;

task main()
{
	eraseDisplay();
	while (true)
	{
		//
		// Draw the spiral
		//
		nRadius = 32;
		nAngle = 0;
		while(nRadius > 0)
		{
			float xSin1;
			float yCos1;
			float xSin2;
			float yCos2;
			float fRadians;

			fRadians = nAngle * PI /(float) 180.0;
			xSin1 = sin(fRadians);
			yCos1 = cos(fRadians);
			xSin2 = sinDegrees(nAngle);
			yCos2 = cosDegrees(nAngle);
			X = sinDegrees(nAngle) * nRadius;
			Y = cosDegrees(nAngle) * nRadius;
			setPixel(X + 50, Y + 32); // Center of screen is (50, 32)
			wait1Msec(1);
			nRadius -=.02;
			++nAngle;
		}
		//
		// Erase the spiral
		//
		while(nRadius <= 32)
		{
			X = sinDegrees(nAngle)  * nRadius;
			Y = cosDegrees(nAngle) * nRadius;
			clearPixel(X + 50, Y + 32); // Center of screen is (50, 32)
			wait1Msec(1);
			nRadius += .02;
			--nAngle;
		}
	}
}
