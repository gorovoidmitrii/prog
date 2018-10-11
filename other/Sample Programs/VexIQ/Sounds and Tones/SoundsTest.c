task main()
{
	int nSoundID;
	char *pzSound;
	clearDebugStream();
	bPlaySounds = true;  // Otherwise this program wouldn't work.

	while (true)
	{
		for (nSoundID = 0; nSoundID < 100; ++nSoundID)
		{
			while (!bPlaySounds)
			{
				displayCenteredTextLine(3, "Sound Off");
			}

			switch (nSoundID)
			{
			default:										continue;
			case soundSiren2:						pzSound = "Siren2";						break;
			case soundWrongWay:         pzSound = "WrongWay";					break;
			case soundWrongWays:        pzSound = "WrongWays";				break;
			case soundGasFillup:        pzSound = "GasFillup";				break;
			case soundHeadlightsOn:     pzSound = "HeadlightsOn";			break;
			case soundHeadlightsOff:    pzSound = "HeadlightsOff";		break;
			case soundTollBooth:        pzSound = "TollBooth";				break;
			case soundCarAlarm2:        pzSound = "CarAlarm2";				break;
			case soundTada:             pzSound = "Tada";							break;
			case soundGarageDoorClose: 	pzSound = "GarageDoorClose";	break;
			case soundRatchet:          pzSound = "Ratchet";					break;
			case soundAirWrench:				pzSound = "AirWrench";				break;
			case soundSiren4:						pzSound = "Siren4";						break;
			case soundRatchet4:					pzSound = "Ratchet4";					break;
			case soundCarAlarm4:				pzSound = "CarAlarm4";				break;
			case soundPowerOff2:				pzSound = "PowerOff2";				break;
			}
			displayCenteredTextLine(1, "Play: (%d)", nSoundID - kFirstSoundInChipRom);
			if (strlen(pzSound) > 10)
			{
				displayCenteredTextLine(3, pzSound);
				displayClearTextLine(4);
			}
			else
				displayCenteredBigTextLine(3, pzSound);

			playSound(nSoundID);
			while (bSoundActive && bPlaySounds)
			{
				for (int i = 0; i < 5; ++i)
				{
					switch (i)
					{
					case 0:		drawUserText(2 * 9, 0, ".    ");				break;
					case 1:		drawUserText(2 * 9, 0, "..   ");				break;
					case 2:		drawUserText(2 * 9, 0, "...  ");				break;
					case 3:		drawUserText(2 * 9, 0, ".... ");				break;
					case 4:		drawUserText(2 * 9, 0, ".....");				break;
					}
					sleep(50);
					if (!bSoundActive)
						break;
				}
			}
			sleep(600);
		}
	}

}
