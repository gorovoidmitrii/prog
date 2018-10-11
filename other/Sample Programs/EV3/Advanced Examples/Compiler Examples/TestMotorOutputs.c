long motorEncoderValues[4];

int nMotorSpeedSetting = 50;

task main()
{
	for(int i = -100; i < 100; i+=10)
	{
		motor[motorA] = i;
		sleep(1000);
	}

	while(false)
	{
		motor[motorA] = nMotorSpeedSetting;
		//motor[motorB] = nMotorSpeedSetting;
		//motor[motorC] = nMotorSpeedSetting;
		//motor[motorD] = nMotorSpeedSetting;
		motorEncoderValues[0] = nMotorEncoder[motorA];
		motorEncoderValues[1] = nMotorEncoder[motorB];
		motorEncoderValues[2] = nMotorEncoder[motorC];
		motorEncoderValues[3] = nMotorEncoder[motorD];
		sleep(10);
	}
}
