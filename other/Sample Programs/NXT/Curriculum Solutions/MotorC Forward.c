// Move motor C forward with 100% power

task main()
{

	/*
		Motor C forward with 100% power
		Do this for 3 seconds
	*/

	motor[motorC] = 100;
	wait1Msec(3000);

}
