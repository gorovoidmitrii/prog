TEV3LEDPatterns color;

task main()
{
	for(color = ledOff; color <= ledOrangePulse; color++)
	{
		setLEDColor(color);
		sleep(1500);
	}

	color = ledOff;
	setLEDColor(color);
}
