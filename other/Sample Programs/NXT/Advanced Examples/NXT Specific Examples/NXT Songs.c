//*!!Sensor,    S1,               button, sensorTouch,      ,                    !!*//
//*!!                                                                            !!*//
//*!!Start automatically generated configuration code.                           !!*//
const tSensors button               = (tSensors) S1;   //sensorTouch        //*!!!!*//
//*!!CLICK to edit 'wizard' created sensor & motor configuration.                !!*//

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    Somg Playback Demonstration
//
// This program demonstrates the sound playback routines of ROBOTC.
//
// It contains three songs that are played sequentially.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// An optional touch sensor can be used to start/stop the program. Following flag indicates whether
// it should be used. The touch sensor should be given the name "button" in the config wizard.
//
const bool bTouchSensorForStartStop = false;

void BeethovenFifth()
{
	//  Piano Player II
	//    rest);
	wait1Msec(750);
	playTone(784,15);	wait1Msec(190);
	playTone(784,15);	wait1Msec(190);
	playTone(784,15);	wait1Msec(190);
	playTone(622,38);	wait1Msec(380);
	//    rest);
	wait1Msec(380);
	playTone(698,15);	wait1Msec(190);
	playTone(698,15);	wait1Msec(190);
	playTone(698,15);	wait1Msec(190);
	playTone(587,38);	wait1Msec(380);
	//    rest);
	wait1Msec(750);
	playTone(784,15);	wait1Msec(190);
	playTone(784,15);	wait1Msec(190);
	playTone(784,15);	wait1Msec(190);
	playTone(622,15);	wait1Msec(190);
	playTone(831,15);	wait1Msec(190);
	playTone(831,15);	wait1Msec(190);
	playTone(831,15);	wait1Msec(190);
	playTone(784,15);	wait1Msec(190);
	playTone(1244,15);	wait1Msec(190);
	playTone(1244,15);	wait1Msec(190);
	playTone(1244,15);	wait1Msec(190);
	playTone(1047,38);	wait1Msec(380);
	//    rest);
	wait1Msec(190);
	playTone(784,15);	wait1Msec(190);
	playTone(784,15);	wait1Msec(190);
	playTone(784,15);	wait1Msec(190);
	playTone(587,15);	wait1Msec(190);
	playTone(831,15);	wait1Msec(190);
	playTone(831,15);	wait1Msec(190);
	playTone(831,15);	wait1Msec(190);
	playTone(784,15);	wait1Msec(190);
	playTone(1397,15);	wait1Msec(190);
	playTone(1397,15);	wait1Msec(190);
	playTone(1397,15);	wait1Msec(190);
	playTone(1175,38);	wait1Msec(380);
	//    rest);
	wait1Msec(190);
	playTone(1568,15);	wait1Msec(190);
	playTone(1568,15);	wait1Msec(190);
	playTone(1397,15);	wait1Msec(190);
	playTone(1244,19);	wait1Msec(190);
	//    rest);
	wait1Msec(190);
	playTone(1175,15);	wait1Msec(190);
	playTone(1568,15);	wait1Msec(190);
	playTone(1568,15);	wait1Msec(190);
	playTone(1397,15);	wait1Msec(190);
	playTone(1244,19);	wait1Msec(190);
	//    rest);
	wait1Msec(190);
	playTone(1175,15);	wait1Msec(190);
	playTone(1568,15);	wait1Msec(190);
	playTone(1568,15);	wait1Msec(190);
	playTone(1397,15);	wait1Msec(190);
	playTone(1244,19);	wait1Msec(190);
	//    rest);
	wait1Msec(380);
	playTone(1047,19);	wait1Msec(190);
	//    rest);
	wait1Msec(380);
	playTone(784,38);	wait1Msec(380);
	return;
}


void HallOfMountainKing()
{
	wait1Msec(80);  // Rest
	playTone(220,12);  wait1Msec(150);
	playTone(247,12);  wait1Msec(150);
	playTone(262,12);  wait1Msec(150);
	playTone(294,12);  wait1Msec(150);
	playTone(330,12);  wait1Msec(150);
	playTone(262,12);  wait1Msec(150);
	playTone(330,24);  wait1Msec(300);
	playTone(311,12);  wait1Msec(150);
	playTone(247,12);  wait1Msec(150);
	playTone(311,24);  wait1Msec(300);
	playTone(294,12);  wait1Msec(150);
	playTone(233,12);  wait1Msec(150);
	playTone(294,24);  wait1Msec(300);
	playTone(220,12);  wait1Msec(150);
	playTone(247,12);  wait1Msec(150);
	playTone(262,12);  wait1Msec(150);
	playTone(294,12);  wait1Msec(150);
	playTone(330,12);  wait1Msec(150);
	playTone(262,12);  wait1Msec(150);
	playTone(330,12);  wait1Msec(150);
	playTone(440,12);  wait1Msec(150);
	playTone(392,12);  wait1Msec(150);
	playTone(330,12);  wait1Msec(150);
	playTone(262,12);  wait1Msec(150);
	playTone(330,12);  wait1Msec(150);
	playTone(392,48);  wait1Msec(600);
	wait1Msec(80);  // Rest
	playTone(220,12);  wait1Msec(150);
	playTone(247,12);  wait1Msec(150);
	playTone(262,12);  wait1Msec(150);
	playTone(294,12);  wait1Msec(150);
	playTone(330,12);  wait1Msec(150);
	playTone(262,12);  wait1Msec(150);
	playTone(330,24);  wait1Msec(300);
	playTone(311,12);  wait1Msec(150);
	playTone(247,12);  wait1Msec(150);
	playTone(311,24);  wait1Msec(300);
	playTone(294,12);  wait1Msec(150);
	playTone(233,12);  wait1Msec(150);
	playTone(294,24);  wait1Msec(300);
	playTone(220,12);  wait1Msec(150);
	playTone(247,12);  wait1Msec(150);
	playTone(262,12);  wait1Msec(150);
	playTone(294,12);  wait1Msec(150);
	playTone(330,12);  wait1Msec(150);
	playTone(262,12);  wait1Msec(150);
	playTone(330,12);  wait1Msec(150);
	playTone(440,12);  wait1Msec(150);
	playTone(392,12);  wait1Msec(150);
	playTone(330,12);  wait1Msec(150);
	playTone(262,12);  wait1Msec(150);
	playTone(330,12);  wait1Msec(150);
	playTone(392,48);  wait1Msec(600);
	wait1Msec(80);  // Rest
	playTone(330,12);  wait1Msec(150);
	playTone(370,12);  wait1Msec(150);
	playTone(415,12);  wait1Msec(150);
	playTone(440,12);  wait1Msec(150);
	playTone(494,12);  wait1Msec(150);
	playTone(415,12);  wait1Msec(150);
	playTone(494,24);  wait1Msec(300);
	playTone(523,12);  wait1Msec(150);
	playTone(440,12);  wait1Msec(150);
	playTone(523,24);  wait1Msec(300);
	playTone(494,12);  wait1Msec(150);
	playTone(415,12);  wait1Msec(150);
	playTone(494,24);  wait1Msec(300);
	playTone(330,12);  wait1Msec(150);
	playTone(370,12);  wait1Msec(150);
	playTone(415,12);  wait1Msec(150);
	playTone(440,12);  wait1Msec(150);
	playTone(494,12);  wait1Msec(150);
	playTone(415,12);  wait1Msec(150);
	playTone(494,24);  wait1Msec(300);
	playTone(523,12);  wait1Msec(150);
	playTone(440,12);  wait1Msec(150);
	playTone(523,24);  wait1Msec(300);
	playTone(494,48);  wait1Msec(600);
	wait1Msec(80);  // Rest
	playTone(330,12);  wait1Msec(150);
	playTone(370,12);  wait1Msec(150);
	playTone(415,12);  wait1Msec(150);
	playTone(440,12);  wait1Msec(150);
	playTone(494,12);  wait1Msec(150);
	playTone(415,12);  wait1Msec(150);
	playTone(494,24);  wait1Msec(300);
	playTone(523,12);  wait1Msec(150);
	playTone(440,12);  wait1Msec(150);
	playTone(523,24);  wait1Msec(300);
	playTone(494,12);  wait1Msec(150);
	playTone(415,12);  wait1Msec(150);
	playTone(494,24);  wait1Msec(300);
	playTone(330,12);  wait1Msec(150);
	playTone(370,12);  wait1Msec(150);
	playTone(415,12);  wait1Msec(150);
	playTone(440,12);  wait1Msec(150);
	playTone(494,12);  wait1Msec(150);
	playTone(415,12);  wait1Msec(150);
	playTone(494,24);  wait1Msec(300);
	playTone(523,12);  wait1Msec(150);
	playTone(440,12);  wait1Msec(150);
	playTone(523,24);  wait1Msec(300);
	playTone(494,48);  wait1Msec(600);
	wait1Msec(80);  // Rest
	wait1Msec(80);  // Rest
	playTone(440,8);  wait1Msec(150);
	playTone(494,8);  wait1Msec(150);
	playTone(523,8);  wait1Msec(150);
	playTone(587,8);  wait1Msec(150);
	playTone(659,8);  wait1Msec(150);
	playTone(523,8);  wait1Msec(150);
	playTone(659,24);  wait1Msec(300);
	playTone(622,8);  wait1Msec(150);
	playTone(494,8);  wait1Msec(150);
	playTone(622,24);  wait1Msec(300);
	playTone(587,8);  wait1Msec(150);
	playTone(466,8);  wait1Msec(150);
	playTone(587,24);  wait1Msec(300);
	playTone(440,8);  wait1Msec(150);
	playTone(494,8);  wait1Msec(150);
	playTone(523,8);  wait1Msec(150);
	playTone(587,8);  wait1Msec(150);
	playTone(659,8);  wait1Msec(150);
	playTone(523,8);  wait1Msec(150);
	playTone(659,8);  wait1Msec(150);
	playTone(880,8);  wait1Msec(150);
	playTone(784,8);  wait1Msec(150);
	playTone(659,8);  wait1Msec(150);
	playTone(523,8);  wait1Msec(150);
	playTone(659,8);  wait1Msec(150);
	playTone(784,48);  wait1Msec(600);
	wait1Msec(80);  // Rest
	playTone(440,8);  wait1Msec(150);
	playTone(494,8);  wait1Msec(150);
	playTone(523,8);  wait1Msec(150);
	playTone(587,8);  wait1Msec(150);
	playTone(659,8);  wait1Msec(150);
	playTone(523,8);  wait1Msec(150);
	playTone(659,24);  wait1Msec(300);
	playTone(622,8);  wait1Msec(150);
	playTone(494,8);  wait1Msec(150);
	playTone(622,24);  wait1Msec(300);
	playTone(587,8);  wait1Msec(150);
	playTone(466,8);  wait1Msec(150);
	playTone(587,24);  wait1Msec(300);
	playTone(440,8);  wait1Msec(150);
	playTone(494,8);  wait1Msec(150);
	playTone(523,8);  wait1Msec(150);
	playTone(587,8);  wait1Msec(150);
	playTone(659,8);  wait1Msec(150);
	playTone(523,8);  wait1Msec(150);
	playTone(659,8);  wait1Msec(150);
	playTone(880,8);  wait1Msec(150);
	playTone(831,8);  wait1Msec(150);
	playTone(659,8);  wait1Msec(150);
	playTone(831,8);  wait1Msec(150);
	playTone(988,8);  wait1Msec(150);
	playTone(880,48); wait1Msec(600);
	return;
}

void FrereJacque()
{
	playTone(523,40);	wait1Msec(500);
	playTone(587,40);	wait1Msec(500);
	playTone(659,40);	wait1Msec(500);
	playTone(523,40);	wait1Msec(500);
	playTone(523,40);	wait1Msec(500);
	playTone(587,40);	wait1Msec(500);
	playTone(659,40);	wait1Msec(500);
	playTone(523,40);	wait1Msec(500);
	playTone(659,40);	wait1Msec(500);
	playTone(698,40);	wait1Msec(500);
	playTone(784,80);	wait1Msec(900);
	playTone(659,40);	wait1Msec(500);
	playTone(698,40);	wait1Msec(500);
	playTone(784,80);	wait1Msec(900);
	playTone(784,20);	wait1Msec(300);
	playTone(880,20);	wait1Msec(300);
	playTone(784,20);	wait1Msec(300);
	playTone(698,20);	wait1Msec(300);
	playTone(659,40);	wait1Msec(500);
	playTone(523,40);	wait1Msec(500);
	playTone(784,20);	wait1Msec(300);
	playTone(880,20);	wait1Msec(300);
	playTone(784,20);	wait1Msec(300);
	playTone(698,20);	wait1Msec(300);
	playTone(659,40);	wait1Msec(500);
	playTone(523,40);	wait1Msec(500);
	playTone(523,40);	wait1Msec(500);
	playTone(392,40);	wait1Msec(500);
	playTone(523,80);	wait1Msec(900);
	playTone(523,40);	wait1Msec(500);
	playTone(392,40);	wait1Msec(500);
	playTone(523,80);	wait1Msec(900);
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Separate task to actually play the three songs
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

task playSongs()
{
	//
	// Set the task to high priority so that there is no jitter in the playback of sounds
	//
	nSchedulePriority = kHighPriority;

	//
	// Play the three songs in sequential order
	//
	HallOfMountainKing();
	wait1Msec(500);

	BeethovenFifth();
	wait1Msec(500);

	FrereJacque();
	wait1Msec(500);

	stopAllTasks(); // we're finished.
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        The main Task
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	int nLastButton;

	//
	// If we're using a touch sensor to start/stop the playback, then wait for button pressed, with debounce
	//
	if (bTouchSensorForStartStop)
	{
		//
		// Wait for button to be pressed. Debounce the button to avoid glitches.
		//
		while (bTouchSensorForStartStop)
		{
			//
			// debounce is find button in same state with 5-msec wait in-between.
			//
			// NOTE: don't need to debounce on the NXT. I think this is done either in the hardware or low-level s/w
			//
			nLastButton = SensorBoolean[button];
			wait1Msec(50);
			if (nLastButton != SensorBoolean[button])
				continue;
			if (SensorBoolean[button])
				break;
		}
		//
		// Wait for button release, with debounce
		//
		while (bTouchSensorForStartStop)
		{
			nLastButton = SensorBoolean[button];
			wait1Msec(50);
			if (nLastButton != SensorBoolean[button])
				continue;
			if (!SensorBoolean[button])
				break;
		}
	}

	//
	// Play the songs in a separate task. We don't need to do this, but it's a useful way
	// to demonstrate the multi-tasking capabilities of ROBOTC.
	//
	startTask (playSongs);

	//
	// Look for button to be pressed to stop program
	//
	while (true)
	{
		//
		//
		//
		if (!bTouchSensorForStartStop)
		{
			//
			// We're not using a touch sensor for start/stop. So simply repeat the loop
			//
			continue;
		}
		if (SensorBoolean[button])
		{
			// Touch Sensor is pushed. Time to finish up

			stopTask(playSongs);
			break;
		}
	}
	return;
}
