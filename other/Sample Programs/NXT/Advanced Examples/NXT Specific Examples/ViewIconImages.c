//////////////////////////////////////////////////////////////////////////////////////
//
//                    Test Program to Display Firmware Built-in Icons
//
//////////////////////////////////////////////////////////////////////////////////////

#include "MenusAndIcons.c"

task main()
{
	TMenuAnimationType nAnimation;
	TIconIndex leftIcon;
	TIconIndex centerIcon;
	TIconIndex rightIcon;
	string sText;
	TIconIndex nPrev;
	int nNumbLeft  = 0;
	int nNumbRight = 0;
	int nNumbEnter = 0;
	int nNumbExit  = 0;
	int index = iconNone;

	leftIcon   = iconNone;
	centerIcon = iconNone;
	rightIcon  = iconNone;
	nPrev      = iconNone;

	nAnimation = menuFromLeft;

	sText = (int) index;
	drawMenu(menuOverwrite, iconDecrement, (TIconIndex) index, iconIncrement, sText, "View Icons");

	nNxtButtonTask = -2;
	while (true)
	{
		const int kMaxIconIndex = 150;

		switch (nNxtButtonTransition)
		{
		case kRightButton:
		  ++nNumbRight;
		  while (true)
		  {
		  	++index;
		  	index %= kMaxIconIndex;
		  	if (bValidIcon((TIconIndex) index))
		  	  break;
		  }
		  break;


		case kLeftButton:
		  ++nNumbLeft;
		  while (true)
		  {
		  	index += (kMaxIconIndex - 1);
		  	index %= kMaxIconIndex;
		  	if (bValidIcon((TIconIndex) index))
		  	  break;
		  }
		  break;

		case kExitButton:
		  ++nNumbExit;
		  playSound(soundBeepBeep);
		  continue;

		case kEnterButton:
		  ++nNumbEnter;
		  playSound(soundBeepBeep);
		  continue;

		default:
		  continue;
		}

		sText = (int) index;
		drawMenu(menuOverwrite, iconDecrement, (TIconIndex) index, iconIncrement, sText, "View Icons");
	}

	for (int i = 0; i < 150; ++i)
	{
		if (!bValidIcon((TIconIndex) i))
		  continue;

		rightIcon  = centerIcon;
		centerIcon = leftIcon;
		leftIcon   = (TIconIndex) i;
		stringFormat(sText, "%d", (int) nPrev);
		//sText = (int) nPrev;
    nPrev = (TIconIndex) i;
		drawMenu(nAnimation, leftIcon, centerIcon, rightIcon, sText, "View Icons");
		wait1Msec(2000);
	}
}
