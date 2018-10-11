////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                 Program to Demonstrate Multiple Tasks on The NXT
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT) // This program only runs on the NXT

const int kMinDelayTime 	=  10;
const int kDelayTime      = 100;
const int kDelayTimeMain  = 100;

const bool kPlaySounds = false;
long nCycles[10];

void wasteTimeInTask(int nTaskIndex)
{
  static int nCyclesThisInvocation = 0;
  long nWasteCPU;

  nSchedulePriority = kDefaultTaskPriority + random(4);
  while (true)
  {
    int nDelayCycles;
    nDelayCycles = (kMinDelayTime + random(kDelayTime));
    wait1Msec(nDelayCycles);
    for (nWasteCPU = nDelayCycles; nWasteCPU >= 0; --nWasteCPU)
		{}

		++nCyclesThisInvocation;
    displayTextLine(nTaskIndex,  "#%d. Cnt:%5d", nTaskIndex + 1, nCyclesThisInvocation);
    if (kPlaySounds)
      playSound(soundBlip);

		++nCycles[nTaskIndex];
  }
  return;
}

task task1()	{wasteTimeInTask(0);}
task task2()	{wasteTimeInTask(1);}
task task3()	{wasteTimeInTask(2);}
task task4()	{wasteTimeInTask(3);}
task task5()	{wasteTimeInTask(4);}
task task6()	{wasteTimeInTask(5);}
task task7()	{wasteTimeInTask(6);}
task task8()	{wasteTimeInTask(7);}
task task9()	{wasteTimeInTask(8);}

task main()
{
  int nCount = 0;
  int nTaskToStop;

  nVolume = 2;

  //
  // Boost priority so that all tasks start immediately
  //
  //nSchedulePriority = kHighPriority;

  hogCPU();
  stopTask(task1);
  startTask(task2);
  startTask(task3);
  startTask(task4);
  startTask(task5);
  startTask(task6);
  startTask(task7);
  startTask(task8);
  startTask(task9);
  releaseCPU();

  //
  // Restore to normal priority
  //
  nSchedulePriority = kHighPriority;

  while (true)
  {
    wait1Msec(random(kDelayTimeMain) / 2);

    nTaskToStop = 1 + random(8);
    switch (nTaskToStop)
    {
    //case 0: stopTask(0);  break;
    case 1: stopTask(1);  break;
    case 2: stopTask(2);  break;
    case 3: stopTask(3);  break;
    case 4: stopTask(4);  break;
    case 5: stopTask(5);  break;
    case 6: stopTask(6);  break;
    case 7: stopTask(7);  break;
    case 8: stopTask(8);  break;
    case 9: stopTask(9);  break;
    }

    wait1Msec(5);

    switch (nTaskToStop)
    {
    //case 0: startTask(0);  break;
    case 1: startTask(1);  break;
    case 2: startTask(2);  break;
    case 3: startTask(3);  break;
    case 4: startTask(4);  break;
    case 5: startTask(5);  break;
    case 6: startTask(6);  break;
    case 7: startTask(7);  break;
    case 8: startTask(8);  break;
    case 9: startTask(9);  break;
    }

    ++nCount;
    //nxtDisplayTextLine(0,  "%s.  Cycle:%4d", "main", nCount);
  }
  return;
}
