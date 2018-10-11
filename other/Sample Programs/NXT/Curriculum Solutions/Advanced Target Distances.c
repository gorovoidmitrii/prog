task main()
{
	//resets the motor encoders
  nMotorEncoder[motorB] = 0;
  nMotorEncoder[motorC] = 0;

  //gives the robot a distance and a speed with which to travel
  nMotorEncoderTarget[motorB] = 1800;
  nMotorEncoderTarget[motorC] = 1800;

  motor[motorC] = 50;
  motor[motorB] = 50;

  //continues the program in an empty loop until both motors are idle, then stops
  while(nMotorRunState[motorB] != runStateIdle || nMotorRunState[motorC] != runStateIdle)
  {

  }
}
