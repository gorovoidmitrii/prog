void turnLeft()
{

	nMotorEncoder[motorB] = 0;
	while(nMotorEncoder[motorB] < 160)
	{
		motor[motorC] = -50;
		motor[motorB] = 50;
	}

	motor[motorC] = 0;
	motor[motorB] = 0;

}

void turnRight()
{

	nMotorEncoder[motorC] = 0;
	while(nMotorEncoder[motorC] < 160)
	{
		motor[motorC] = 50;
		motor[motorB] = -50;
	}

	motor[motorC] = 0;
	motor[motorB] = 0;

}

task main()
{

	turnLeft();
	wait1Msec(1000);
	turnRight();

}
