#pragma config(StandardModel, "VEX IQ Clawbot")
#pragma config(RenamedStdModelSensor, port3, lineDetector)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
	The color sensor also has a "proximity" detection ability that will allow you to know if color sensor
	is far or close to the object it is currently detecting.

	The "proximity" values range from 0-1023, but expect values to be between 100-500,
	with higher values being "closer" to an object. To assist with debugging,
	this program will print the proximity value to the screen.

 Note: Lighting conditions change from place to place, so the value '600' may need to be changed
       to better suit your environment. Grayscale Values can range from 0 to 2000 (possibly even higher)

                            ROBOT CONFIGURATION: VEX IQ Clawbot
    MOTORS & SENSORS:
    [I/O Port]          [Name]              [Type]                			[Location]
    Port 1        			leftMotor           VEX IQ Motor		      			Left side motor
    Port 6       				rightMotor          VEX IQ Motor		      			Right side motor (reversed)
		Port 5       				lineDetector       	VEX IQ Color		      			Color Detector (Grayscale Mode)
------------------------------------------------------------------------------------------------*/

task main()
{
	while(true)
	{
		// Display the grayscale reading on the LCD screen using '600' as a dark/light threshold.
		if(getColorValue(lineDetector) > 600)
		{
			displayTextLine(1, "Light Area Detected");
		}
		else
		{
			displayTextLine(1, "Dark Area Detected");
		}

		//Set your color proximity threshold to say if we're close or far away from an object.
		//To learn what values you get, we'll also print the proximity value to the LCD screen.
		if(getColorProximity(lineDetector) > 200)
		{
			displayTextLine(2, "Detected Close");
			displayTextLine(3, "Proximity Value: %d", getColorProximity(lineDetector));
		}
		else
		{
			displayTextLine(2, "Detected Far Away");
			displayTextLine(3, "Proximity Value: %d", getColorProximity(lineDetector));
		}

		sleep(100);
	}
}
