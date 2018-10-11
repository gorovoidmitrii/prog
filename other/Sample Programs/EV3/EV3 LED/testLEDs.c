TEV3LEDPatterns color;

task main()
{
	for(color = ledOff; color <= ledOrangePulse; color++)
	{
		setLEDColor(color);
		sleep(500);
	}

	setLEDColor(ledOff);
}
