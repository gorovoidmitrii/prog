task main()
{

	motor[motorC] = 50;
	motor[motorB] = 50;
	wait1Msec(4000);

	motor[motorC] = -50;
	motor[motorB] = 50;
	wait1Msec(800);

}
