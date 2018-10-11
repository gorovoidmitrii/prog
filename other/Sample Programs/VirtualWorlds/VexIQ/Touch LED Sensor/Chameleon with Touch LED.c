#pragma config(StandardModel, "VEX IQ Clawbot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
  This program will take the Hue value from the Color sensor and send it to the TouchLED sensor.
  The Touch LED will output the color the color sensor sees by using the "setTouchLEDHue" function.

                            ROBOT CONFIGURATION: VEX IQ Clawbot
    MOTORS & SENSORS:
    [I/O Port]          [Name]              [Type]                			[Location]
    Port 5       				colorDetector       VEX IQ Color		      			Color Detector (Hue Color Mode)
    Port 12							touchLED						VEX IQ Touch LED						Detect Touches and Set Colors
------------------------------------------------------------------------------------------------*/

task main()
{
	int currentHueValue;
	while(true)
	{
			currentHueValue = getColorValue(colorDetector);
			setTouchLEDHue(touchLED, currentHueValue);
			sleep(25);
	}
}
