#pragma config(StandardModel, "VEX IQ Clawbot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
  This program will cycle through all 256 (0-255) Hue values and assign them to the TouchLED Sensor.

  To turn off the Touch LED, set the "hue" value to zero.

                            ROBOT CONFIGURATION: VEX IQ Clawbot
    MOTORS & SENSORS:
    [I/O Port]          [Name]              [Type]                			[Location]
    port 12							touchLED						VEX IQ Touch LED						Detect Touches and Set Colors
------------------------------------------------------------------------------------------------*/

task main()
{
	for(int nHueValue = 0; nHueValue < 255; nHueValue++)
	{
		setTouchLEDHue(touchLED, nHueValue);
		sleep(100);
	}
}
