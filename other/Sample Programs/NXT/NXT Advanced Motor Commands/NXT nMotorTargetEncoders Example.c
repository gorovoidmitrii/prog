

//                  nMotorEncoderTarget Example
//
// The program below demonstrates how to use the nMotorEndocerTarget function
// There are four steps to using the function
//  Step 1 - Zero out the encoder using "nMotorEncoder(motorX) = 0"   Lines 25 and 26.
//  Step 2 - Set the target distance using the nMotorEncoderTarget function.
//           Lines 28 and 29.
//  Step 3 - Turn the motors on. Lines 31 and 32.
//  Step 4 - Wait for the motor's "runstate" to reach idle. Line 34 through 38.
//
//  nMotorTargetEncoder is coupled with the nMotorRunState function.
//    The nMotorRunState function watches the "state" of the motor in three conditions:
//       1. "runStateRunning" - While the motor is running
//       2. "runStateHoldPosition" - While the motor is begining to slow down.
//          nMotorEncoderTarget sets the condition when the motor begins to slow down.
//       3. "runStateIdle" - Reports back to the controller that the motor is in an
//           idle position; this is when the motor is stopped.


task main()
{

  nMotorEncoder[motorC] = 0;  //clear the LEGO motor encoders
  nMotorEncoder[motorB] = 0;

  nMotorEncoderTarget[motorC] = 360; //set the target stoping position
  nMotorEncoderTarget[motorB] = 360;

  motor[motorC] = 30; //turn both motors on at 30 percent power
  motor[motorB] = 30;

  while (nMotorRunState[motorC] != runStateIdle || nMotorRunState[motorB] != runStateIdle) //while the encoder wheel turns one revolution
  {
    // This condition waits for motors B + C to come to an idle position. Both motors stop
    // and then jumps out of the loop
  }

  motor[motorC] = 0; //turn both motors off
  motor[motorB] = 0;

  wait1Msec(3000);  // wait 3 seconds to see feedback on the debugger screens
                    // open the "NXT Devices" window to see the distance the encoder spins.
                    // the robot will come to a stop at the nMotorEncoderTarget position.
}
