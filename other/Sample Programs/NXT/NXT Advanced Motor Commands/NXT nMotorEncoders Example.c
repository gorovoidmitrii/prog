
//                  nMotorEncoder Example

// The program below demonstrates how to use the nMotorEndocer function
// There are three steps to using the function
//    1. Zero out the encoder using "nMotorEncoder(motorX) = 0"   Lines 13 and 14.
//    2. Place the function into a conditional statement like a while loop.  Line 16
//    3. Turn the motors off. Lines 22 and 23.

task main()
{

  nMotorEncoder[motorC] = 0;  //clear the LEGO encoders in motors B and C
  nMotorEncoder[motorB] = 0;

  while (nMotorEncoder[motorC] < 360) //while the encoder wheel turns one revolution
  {
    motor[motorC] = 30; //turn both motors on at 30 percent power
    motor[motorB] = 30;
  }

  motor[motorC] = 0; //turn both motors off
  motor[motorB] = 0;

  wait1Msec(3000); // wait 3 seconds to see feedback from the debugger screens
                    // open the "NXT Devices" window to see the distance the encoder
                    //spins. The robot will coast a little bit.
}
