task main()
{
  nMotorEncoder[motorB] = 0;
  nMotorEncoder[motorC] = 0;

  while(nMotorEncoder[motorB] < 1800)
  {
    motor[motorC] = 50;
    motor[motorB] = 50;
  }
}
