#pragma config(Sensor, S4,     sColour,        sensorEV3_Color)
long greenValue;
long blueValue;
long redValue;
task main()
{

	getColorRGB(sColour, redValue, greenValue, blueValue);
	setSensorMode(sColour,modeEV3Color_Color);
	while(true)
	{
		getColorRGB(sColour, redValue, greenValue, blueValue);
		displayTextLine(4, "%f", redValue);
		displayTextLine(5, "%f", greenValue);
		displayTextLine(6, "%f", blueValue);
		sleep(100);
	}

}
