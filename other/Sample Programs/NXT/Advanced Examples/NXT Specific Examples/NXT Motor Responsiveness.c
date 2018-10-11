///////////////////////////////////////////////////////////////////////////////////////
//
//    Program to Demonstrate Precise Positional Control of a NXT motor using ROBOTC
//
// This example will loop continuously rotating a motor 6 degrees. The movement is very
// precise +/- 1 degree) with absolutely no overshoot. It stops exactly at the targeted
// position
//
// You can best view the motor movement by attaching a beam to the motor output to create
// a shape like the 'hand' on a clock.
//
///////////////////////////////////////////////////////////////////////////////////////

  //
  // These variables are declared as RAM values. This will allow you, in the ROBOTC
  // interactive real-time debugger to change them and watch the effect on the motor.
  //
  int nSpeed        =  50;
  int nDelay        = 500;

int nResponse1First;
int nResponse2First;
int nResponse1Ten;
int nResponse2Ten;

long nSum1First = 0;
long nSum2First = 0;
long nSum1Ten = 0;
long nSum2Ten = 0;
float nAvg1First;
float nAvg2First;
float nAvg1Ten;
float nAvg2Ten;
long nSamples = 0;

const int kResponseTimes = 100;
int nMotor1Response[kResponseTimes + 1];
int nMotor2Response[kResponseTimes + 1];

task main()
{
  memset(nMotor1Response, 0, sizeof(nMotor1Response));
  memset(nMotor2Response, 0, sizeof(nMotor2Response));
  //
  // Setup the motor configuration
  //
  bFloatDuringInactiveMotorPWM = false;

  while (true)
  {
    motor[motorB] = 0;
    motor[motorC] = 0;
    motor[motorA] = 0;
    wait1Msec(300);
    nMotorEncoder[motorB] = 0; // incremental amount to move motor
    nMotorEncoder[motorC] = 0; // incremental amount to move motor
    nResponse1First = 0;
    nResponse2First = 0;
    nResponse1Ten = 0;
    nResponse2Ten = 0;
    time1[T1] = 0;
    motor[motorB] = nSpeed;
    motor[motorC] = nSpeed;
    motor[motorA]    = nSpeed * 2;
    while (true)
    {
    	if (nMotorEncoder[motorB] != 0)
    	{
    		if (nResponse1First == 0)
    	    nResponse1First = time1[T1];
    	}
    	if (nMotorEncoder[motorC] != 0)
    	{
    		if (nResponse2First == 0)
    	    nResponse2First = time1[T1];
    	}

    	if (nMotorEncoder[motorB] >= 10)
    	{
    		if (nResponse1Ten == 0)
    	    nResponse1Ten = time1[T1];
    	}

    	if (nMotorEncoder[motorC] >= 10)
    	{
    		if (nResponse2Ten == 0)
    	    nResponse2Ten = time1[T1];
    	}

    	if (time1[T1] > 400)
    	  break;
    	if ((nResponse1Ten != 0) && (nResponse2Ten != 0))
    	  break;
    }
    ++nSamples;
    nSum1First += nResponse1First;
    nSum2First += nResponse2First;
    nAvg1First = (float) nSum1First / nSamples;
    nAvg2First = (float) nSum2First / nSamples;

    nSum1Ten += nResponse1Ten;
    nSum2Ten += nResponse2Ten;
    nAvg1Ten = (float) nSum1Ten / nSamples;
    nAvg2Ten = (float) nSum2Ten / nSamples;
    ++nMotor1Response[nResponse1First];
    ++nMotor2Response[nResponse2First];
    motor[motorB] = 0;    // motor speed
    motor[motorC] = 0;    // motor speed
    wait1Msec(nDelay);                       // wait for action to complete
  }
}
