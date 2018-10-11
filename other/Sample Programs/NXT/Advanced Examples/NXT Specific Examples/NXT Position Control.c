

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



task main()
{
  //
  // These variables are declared as RAM values. This will allow you, in the ROBOTC
  // interactive real-time debugger to change them and watch the effect on the motor.
  //
  int nMoveSize     = 5000;
  int nSpeed        = 100;
  int nDelay        = 5000;

  //
  // Setup the motor configuration
  //
  bFloatDuringInactiveMotorPWM = false;

  nMotorEncoder[motorB]       = 0;
  nMotorEncoderTarget[motorB] = 0;
  nMotorEncoder[motorC]       = 0;
  nMotorEncoderTarget[motorC] = 0;

  while (true)
  {
    //
    // Loop continuously moving the motor forward a small increment
    //
    nMotorEncoderTarget[motorB] = nMoveSize; // incremental amount to move motor
    nMotorEncoderTarget[motorC] = nMoveSize; // incremental amount to move motor
    wait1Msec(1000);
    motor[motorB]               = nSpeed;    // motor speed
    motor[motorC]               = nSpeed;    // motor speed
    wait1Msec(nDelay);                       // wait for action to complete
  }
}
