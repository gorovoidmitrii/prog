#pragma platform(NXT)


task main()
{
	int nSoundIndex;
	while (true)
	{
		alive();
		for (nSoundIndex = 0; nSoundIndex <= 113; ++nSoundIndex)
		{
			displayCenteredBigTextLine(3, "%d", nSoundIndex);
			playSound((TSounds) nSoundIndex);
			if (bSoundActive)
			{
				while (bSoundActive)
				{
					wait1Msec(1);
				}
				wait1Msec(500);
			}
		}
	}
}
