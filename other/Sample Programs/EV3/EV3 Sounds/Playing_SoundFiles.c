void testCustomExceptions()
{
	setException(exceptionInternalError);
	setUserExceptionType1();
	setUserExceptionType2();
	setUserExceptionType3();
	throwBadSensorPortException();
	return;
}

void testSounds()
{
	int nRead;
	int nFreq;

	for (int nVol = 0; nVol< 127; ++nVol)
	{
		setSoundVolume(nVol);
		nRead = getSoundVolume();
		VERIFY(nRead == nVol);
	}

	setSoundVolume(30);
	while (true)
	{
		for (nFreq = 50; nFreq < 4000; nFreq += 25)
		{
			playTone(nFreq, 1);
			while (!bSoundQueueAvailable)
			{}
		}
		for (; nFreq > 50; nFreq -= 25)
		{
			playTone(nFreq, 1);
			while (!bSoundQueueAvailable)
			{}
		}
	}
}

void checkSoundFile(const char *pFileName)
{
	bool bExists;

	bExists = bEv3FileExists(pFileName);
	while (!bSoundQueueAvailable)
	{}
	playSoundFile(pFileName);
	return;
}


void testPlaySoundFiles()
{
	checkSoundFile("Black");
	checkSoundFile("Backing alert");
	checkSoundFile("Blip 2");
	checkSoundFile("Boing");
	checkSoundFile("Cheering");
	checkSoundFile("Crunching");
}

task main()
{
	setSoundVolume(20);
	testPlaySoundFiles();
	testSounds();
	testCustomExceptions();
}
