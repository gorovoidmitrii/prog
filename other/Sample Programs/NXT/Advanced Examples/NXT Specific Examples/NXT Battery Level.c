////////////////////////////////////////////////////////////////////////////////////////////////
//
//														NXT Battery Level Access
//
// Test program to:
//	 1. Read the NXT battery levels and display on LCD.
//	 2. Use the battery level in a user program to make a decision on program flow.
//
// Two ROBOTC intrinisc variables are available:
//				nAvgBatteryLevel
//				nImmediateBatteryLevel
//
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT)
const int kMinimumBatteryLevel = 6300;

task main()
{
	int nCounter = 0;

  //
	// Illustrate variables that control NXT power saving modes and auto power-off.
	//
	nPowerDownDelayMinutes  = 15;   // NXT will power off after 15 minutes of inactivity
  bNoPowerDownOnACAdaptor = true; // NXT will not automatically power off if connected to an AC adaptor.

  while (true)
	{
		if (nImmediateBatteryLevel < kMinimumBatteryLevel)
		{
			//
			// Battery level too low to proceeed.
			//
			playSound(soundLowBuzz);
			break;
		}
		displayTextLine(0, "	 Battery Level");

		//
		// Display the Battery levels
		//
		displayTextLine(2, "Avg %3.1fV;Now %3.1f", nAvgBatteryLevel / (float) 1000, nImmediateBatteryLevel / (float) 1000);
		displayBigStringAt(20, 52, "%3.1f V", nImmediateBatteryLevel / (float) 1000);

		//
		// Display the voltage level at which the NXT will "shutdown"
		//
		displayTextLine(4, "Shutdown at %d fV", kMinimumBatteryLevel / (float) 1000);

		//
		// Display the voltage level at which the NXT will "shutdown"
		//
		displayTextLine(5, "Sleep Tmr: %d min", nPowerDownDelayMinutes);

		//
		// Display the Battery type: rechargeable or one-time only
		//
		if (bNxtRechargable)							 //
			displayTextLine(7, "Rechargable");
		else
			displayTextLine(7, "Non-Rechargeable");

		//
		// You can also immediately power off the NXT as follows:
		//
		wait1Msec(10);
		++nCounter;
		if (nCounter > 15000)
			powerOff();
	}
	return;
}
