#pragma config(StandardModel, "EV3_REMBOT")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	repeat(forever)
	{
		displayTextLine(1, "Light: %d", getColorReflected(colorSensor));
		sleep(250);
	}
}
