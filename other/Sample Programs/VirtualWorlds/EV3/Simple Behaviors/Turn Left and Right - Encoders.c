#pragma config(StandardModel, "EV3_REMBOT")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	moveMotorTarget(rightMotor, 720, 55);
	while(getMotorRunning(rightMotor))
	{
		sleep(1);
	}
	sleep(1000);

	moveMotorTarget(leftMotor, 720, 55);
	while(getMotorRunning(leftMotor))
	{
		sleep(1);
	}
	sleep(1000);
}