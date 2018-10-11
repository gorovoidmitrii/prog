long nEncoderValue = 0;
long nEncoderTargetValue = 0;
TMotorBrakeModes nBrakeMode;
bool motorReflection;
bool motorStatusFlag;
bool motorMovingFlag;

task pollVariables()
{
	while(true)
	{
		nEncoderTargetValue = getMotorTarget(motorA);
		nEncoderValue = getMotorEncoder(motorA);
		nBrakeMode = getMotorBrakeMode(motorA);
		motorReflection = getMotorReversed(motorA);
		motorStatusFlag = getMotorRunning(motorA);
		motorMovingFlag = getMotorMoving(motorA);
		sleep(100);
	}
}

task main()
{
	startTask(pollVariables);

	setMotorReversed(motorA, true);

	setMotorTarget(motorA, 360, 50);
	sleep(3000);

	setMotorTarget(motorA, 180, 50);
	sleep(3000);

	moveMotorTarget(motorA, 360, 50);
	sleep(3000);

	/*
	setMotorBrakeMode(motorA, motorCoast);
	bMotorReflected[motorA] = false;

	setMotorSpeed(motorA, 50);
	sleep(1000);
	setMotorSpeed(motorA, 0);
	sleep(2500);
	resetMotorEncoder(motorA);
	sleep(2500);

	setMotorBrakeMode(motorA, motorBrake);
	bMotorReflected[motorA] = true;

	setMotorSpeed(motorA, 50);
	sleep(1000);
	setMotorSpeed(motorA, 0);
	sleep(2500);
	resetMotorEncoder(motorA);
	sleep(2500);

	stopAllTasks();
	*/
}
