void playMenuSelection()
{
	int nSoundID;

	nSoundID = menuGetSelection();

	playNote(0, 1);
	sleep(100);
	playSound(nSoundID);
}

void debounceButtons()
{
	//PlaySound(soundBlip);
	while (nLCDButtons != 0)
	{}
	sleep(20);
}

void buildMenuOfSounds()
{
	int nSoundID;
	char *pzSound;

	menuInitialize();
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
		menuAddItem(nSoundID, pzSound);
	}
	menuSetTitle("Select Sound");
	menuRepaint();
}

task main()
{
	setUserDebugWindow(false);
	sleep(300);
	setUserDebugWindow(true);
	sleep(300);

	bPlaySounds = true;  // Otherwise this program wouldn't work.

	while (!bPlaySounds)
	{
	  displayCenteredTextLine(3, "Sound is Off");
	}

	buildMenuOfSounds();

	while (true)
	{
		while (true)
		{
			// Loop until a button is pressed

			if (nLCDButtons & kButtonUp)
			{
				debounceButtons();
				menuScroll(false);
				break;
			}

			else if (nLCDButtons & kButtonDown)
			{
				debounceButtons();
				menuScroll(true);
				playMenuSelection();
				break;
			}

			else if (nLCDButtons & kButtonSelect)
			{
				debounceButtons();
				playMenuSelection();
			}
		}
	}
}
