task main()
{
  nMotorEncoder[motorC] = 0;
  nMotorEncoder[motorB] = 0;

  nMotorEncoderTarget[motorC] = 1800;
  nMotorEncoderTarget[motorB] = 1800;

  motor[motorC] = 50;
  motor[motorB] = 50;
  wait1Msec(10000);
}
