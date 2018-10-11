
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                         NXT Motor Analysis
//
// This program will graph the distance travelled from a stopped condition at a constant power/speed
// level.
//
// It compares the use of 'brake' mode vs 'float' mode on the NXT.
///////////////////////////////////////////////////////////////////////////////////////////////////////

//
// ROBOTC supports procedure "prototypes". These are simply declarations for the "header" of a
// procedure so that the procedure/subroutine can be called before it is actually defined.
//
void initializeGraphs();
void addDataPointFloat(int nXValue, int nEncoderCounts);
void addDataPointBrake(int nXValue, int nEncoderCounts);
void drawGraphs();

//
// Standard 'C' does not support scalar 'const' declarations. ROBOTC does. It's nicer than using
//     "#define kGraphWidth 100"
//
const int kGraphFloatLeft =  0;
const int kGraphBrakeLeft = 50;
const int kGraphTop    		= 56;
const int kGraphBottom 		=  0;
const int kGraphHeight 		= kGraphTop - kGraphBottom + 1;
const int kGraphWidth 		= 100 / 2;

int index;
int nPower;

//
// Note variables can be initialized in the declaration statement with the use of an optional
// "= <epxression>" clause after the declaration.
//
int   nMaxGraphPoint = kGraphHeight;
float fGraphScaler   = 1;
int   nGraphFloat[kGraphWidth];
int   nGraphBrake[kGraphWidth];

task main()
{
	nVolume = 2;

	//
	// Grab LCD screen and initialize display
	//
	initializeGraphs();
	eraseDisplay();
	displayTextLine(0, " Distance vs Time");
	displayTextLine(1, "   Analysis");

	//
	// Wait for motor to be connected
	//
	nMotorEncoder[motorA] = 0;
	motor[motorA] = 100;
	while (nMotorEncoder[motorA] < 10)
	{
		playSound(soundBeepBeep);
		displayTextLine(6, " Connect Motor");
		displayTextLine(7, "  to Port 1");
		wait1Msec(400);
		displayTextLine(6, "");
		displayTextLine(7, "");
		wait1Msec(400);
	}

	eraseDisplay();
	for (nPower = 20; nPower <= 100; nPower += 20)
	{
		const int kMeasurementInterval = 25;

		displayTextLine(0, " Float %2d Brake", nPower);
		initializeGraphs();
		playTone( 750, 5);
		playTone(1500, 5);
		motor[motorA] = nPower;

		// Brake mode testing

		bFloatDuringInactiveMotorPWM = false;
		motor[motorA] = 0;
		wait1Msec(500); // wait for steady state stopped
		bFloatDuringInactiveMotorPWM = false;
		nMotorEncoder[motorA] = 0;
		motor[motorA] = nPower;
		alive();

		motor[motorA] = nPower;
		for (index = 0; index < kGraphWidth; ++index)
		{
			wait1Msec(kMeasurementInterval);
			addDataPointBrake(index, nMotorEncoder[motorA]);
		}
		motor[motorA] = 0;
		drawGraphs();


		// Float mode testing

		bFloatDuringInactiveMotorPWM = false;
		motor[motorA] = 0;
		wait1Msec(500); // wait for steady state stopped
		bFloatDuringInactiveMotorPWM = true;
		nMotorEncoder[motorA] = 0;
		motor[motorA] = nPower;
		alive();
		for (index = 0; index < kGraphWidth; ++index)
		{
			wait1Msec(kMeasurementInterval);
			addDataPointFloat(index, nMotorEncoder[motorA]);
		}
		motor[motorA] = 0;
		drawGraphs();


		wait1Msec(1000);
	}
	motor[motorA] = 0;
	displayTextLine(0, " Float vs Brake");
	while (true)
	{
		// wait for user to cancel program
	}
}

void eraseGraphingArea()
{
	eraseRect(kGraphFloatLeft, kGraphTop, kGraphFloatLeft + kGraphWidth - 1, kGraphBottom);
	eraseRect(kGraphBrakeLeft, kGraphTop, kGraphBrakeLeft + kGraphWidth - 1, kGraphBottom);
	drawLine(kGraphFloatLeft, kGraphTop - 1, kGraphBrakeLeft + kGraphWidth - 1, kGraphTop - 1);
}

void initializeGraphs()
{
	//
	// Zero out the histogram entries
	//
	int i;

	for (i = 0; i < kGraphWidth; ++i)
	{
		nGraphFloat[i] = 0;
		nGraphBrake[i] = 0;
	}
	eraseGraphingArea();
	return;
}

void rescaleGraphs(int nCurrentMaximumValue)
{
	int i;

	eraseGraphingArea();
	nMaxGraphPoint = nCurrentMaximumValue;
	displayString(1, "%d", nMaxGraphPoint);
	if (nCurrentMaximumValue == 0)
		nCurrentMaximumValue = 1;
	fGraphScaler = ((float) kGraphHeight - 1) / nCurrentMaximumValue;

	for (i = 0; i < kGraphWidth; ++ i)
	{
		if (nGraphFloat[i] != 0)
		  setPixel(i + kGraphFloatLeft, kGraphBottom + (int) (nGraphFloat[i] * fGraphScaler));
		if (nGraphBrake[i] != 0)
		  setPixel(i + kGraphBrakeLeft, kGraphBottom + (int) (nGraphBrake[i] * fGraphScaler));
	}
	return;
}


void drawGraphs()
{
	int i;

	nMaxGraphPoint = 0;
	for (i = 0; i < kGraphWidth; ++ i)
	{
		if (nGraphFloat[i] > nMaxGraphPoint)
		  nMaxGraphPoint = nGraphFloat[i];
		if (nGraphBrake[i] > nMaxGraphPoint)
		  nMaxGraphPoint = nGraphBrake[i];
	}
	rescaleGraphs(nMaxGraphPoint);
}

void addDataPointFloat(int nXValue, int nEncoderCounts)
{
	if (nXValue > (kGraphWidth - 1))
		nXValue = kGraphWidth - 1;

	nGraphFloat[nXValue] = nEncoderCounts;
	return;

	if (nEncoderCounts < nMaxGraphPoint)
		setPixel(kGraphFloatLeft + nXValue, kGraphBottom + (int) (nEncoderCounts * fGraphScaler));
	else if (nEncoderCounts > nMaxGraphPoint)
		rescaleGraphs(nEncoderCounts);
	return;
}

void addDataPointBrake(int nXValue, int nEncoderCounts)
{
	if (nXValue > (kGraphWidth - 1))
		nXValue = kGraphWidth - 1;

	nGraphBrake[nXValue] = nEncoderCounts;
	return;

	if (nEncoderCounts < nMaxGraphPoint)
		setPixel(kGraphBrakeLeft + nXValue, kGraphBottom + (int) (nEncoderCounts * fGraphScaler));
	else if (nEncoderCounts > nMaxGraphPoint)
		rescaleGraphs(nEncoderCounts);
	return;
}
