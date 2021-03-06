#pragma config(Sensor, S3,     light,               sensorLightInactive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma fileExtension("rtm")

task main()
{
	//
	// Grab LCD screen and initialize display
	//
	nVolume = 2;

	eraseDisplay();
	displayCenteredBigTextLine(0, "Light");
	displayCenteredBigTextLine(2, "Sensor");
	wait1Msec(100);

	//
	// Wait for Sensor to be connected
	//
	while (SensorValue[light] == 0)
	{
		playSound(soundBeepBeep);
		displayCenteredTextLine(6, "Connect Sensor");
		displayCenteredTextLine(7, "to Port S3");
		wait1Msec(700);
		displayTextLine(6, "");
		displayTextLine(7, "");
		wait1Msec(300);
	}

	displayTextLine(4, "Sensor on port 3");
	while (true)
	{
	  int nValue;

	  nValue = SensorValue[light];
	  playImmediateTone(nValue * 80, 50);
		displayCenteredBigTextLine(6, "%d", nValue);
		wait1Msec(200);
	}
}
