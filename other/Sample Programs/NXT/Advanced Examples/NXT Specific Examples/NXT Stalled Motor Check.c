//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Sample program to show how you can use a separate task to monitor for a stalled motor. This task will
// run independently of your normal robot control program and will simply check to see if the motor
// is not moving very fast.
//
// Your main program can easily check for the stalled condition.
//
// Using a separate task gives a common solution that can work for any user program. User program logic
// does not have to include the logice for stalled program.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define bMotorAStalled()   (nStallCount > 3)

int nStallCount = 0;


task stallMonitoringTask()
{
  int nLastEncoder;

  //
  // Check every 50 msec to see if the motor encoder has moved. If not, increment a counter
  //
  nLastEncoder = nMotorEncoder[motorA];
  while (true)
  {
    int nEncoderDelta;

    wait1Msec(20);
    nEncoderDelta = (nMotorEncoder[motorA] - nLastEncoder);
    if ((nEncoderDelta > 2) || (nEncoderDelta < -2))
    {
    	nStallCount = 0;
    	nLastEncoder = nMotorEncoder[motorA];
    }
    else
    {
      if (nStallCount < 1000)
        ++nStallCount;
    }
  }
}

//
// For illustrative purposes a dummy main task is included to show how you can use the above
// in a user application.
//

task main()
{
  //
  // Startup sequence of your main task
  //

  // Insert your own code here

  startTask(stallMonitoringTask);   // This will start the stall monitoring task

  //
  // Main Robot Control loop
  //
  while (true)
  {

    // Your code here

    if (bMotorAStalled())
    {
      // Do something smart
    }
  }
  stopAllTasks(); // Need to stop 'stallMonitoringTask' from running
  return;
}
