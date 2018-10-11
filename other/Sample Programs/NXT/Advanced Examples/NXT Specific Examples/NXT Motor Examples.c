///////////////////////////////////////////////////////////////////////////////////////
//
//    Program to Demonstrate Synchronization of Two NXT Motors using ROBOTC
//
// This example will loop continuously. Motor A is rotated one complete revolution. Motor
// C is slaved to motor A movement. As defined it is same speed and reverse direction from
// motor A.
//
// There will be a brief pause / wait before the next iteration of the loop.

// You can best view the motor movement by attaching a beam to each of the motor output to
// create / a shape like the 'hand' on a clock.
//
///////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT)

task main()
{
  //
  // These variables are declared as RAM values. This will allow you, in the ROBOTC
  // interactive real-time debugger to change them and watch the effect on the motor.
  //
  int nCount;
  const int kMaxCounts = 2;

  const tMotor         kPrimaryMotor = motorA;
  //
  // Setup the motor configuration
  //
  bFloatDuringInactiveMotorPWM = false;

  nMotorEncoder[kPrimaryMotor]       = 0;
  nMotorEncoderTarget[kPrimaryMotor] = 0;

  nPidUpdateInterval       = 10;  // Best performance if we do really frequent updates
                                     // (i.e. calculation) on the motor speeds to correct
                                     // for errors.
  //
  // Move two motors forward at exactly the same speed. Slave motor turns at 50% of the primary motor speed
  //    motorA is primary motor
  //    motorC is slave   motor
  //
  // One revolution each, repeat 10 times
  //
  for (nCount = 0; nCount < kMaxCounts; ++nCount)
  {
	  nSyncedMotors            						= synchAC;   // "A" will be synchronized to "C".
	  nSyncedTurnRatio         						= 100;       // straight line
    nMotorEncoderTarget[motorA] 			  = 360;       // incremental amount to move motor -- one revolution
    motor[motorA]               				= 75;        // motor speed
    while (nMotorRunState[motorA] != runStateIdle)
    {}  																						// wait for action to complete
    wait1Msec(2000);																// a little delay between actions
  }

  //
  // Move two motors forward in a turn. Slave motor turns at 50% of the primary motor speed
  //    motorA is primary motor
  //    motorC is slave   motor
  //
  // One revolution each of primary motor, repeat 10 times
  //
  for (nCount = 0; nCount < kMaxCounts; ++nCount)
  {
	  nSyncedMotors            						= synchAC;   // "A" will be synchronized to "C".
	  nSyncedTurnRatio         						= 50;        // Turn towards motor C
    nMotorEncoderTarget[motorA] 			  = 360;       // incremental amount to move motor -- one revolution
    motor[motorA]               				= 75;        // motor speed
    while (nMotorRunState[motorA] != runStateIdle)
    {}  																						// wait for action to complete
    wait1Msec(2000);																// a little delay between actions
  }

  //
  // Move two motors forward in a turn. Slave motor turns at 50% of the primary motor speed
  //    motorC is primary motor
  //    motorA is slave   motor
  //
  // One revolution each of primary motor, repeat 10 times
  //
  for (nCount = 0; nCount < kMaxCounts; ++nCount)
  {
	  nSyncedMotors            						= synchCA;   // "C" will be synchronized to "A".
	  nSyncedTurnRatio         						= 50;        // Turn towards motor A
    nMotorEncoderTarget[motorC] 	      = 360;       // incremental amount to move motor -- one revolution
    motor[motorC]               				= 75;        // motor speed
    while (nMotorRunState[motorC] != runStateIdle)
    {}  																						// wait for action to complete
    wait1Msec(2000);																// a little delay between actions
  }

  //
  // Rotate about center of virtual "axle" joinging two motors.
  //   Primary motor forward
  //   Slave   motor reverse
  //
  for (nCount = 0; nCount < kMaxCounts; ++nCount)
  {
	  nSyncedMotors            						= synchCA;   // "C" will be synchronized to "A".
	  nSyncedTurnRatio         						= -100;      // Reversed
    nMotorEncoderTarget[motorC] 	      = 360;       // incremental amount to move motor -- one revolution
    motor[motorC]               				= 75;        // motor speed
    while (nMotorRunState[motorC] != runStateIdle)
    {}  																						// wait for action to complete
    wait1Msec(2000);																// a little delay between actions
  }
}
