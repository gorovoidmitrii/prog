long motorEncoderValues[4];
int nMotorSpeedSetting = 50;

task main()
{
	while(true)
	{
		motor[motorA] = nMotorSpeedSetting;
		motor[motorB] = nMotorSpeedSetting;
		motor[motorC] = nMotorSpeedSetting;
		motor[motorD] = nMotorSpeedSetting;
		motorEncoderValues[0] = nMotorEncoder[motorA];
		motorEncoderValues[1] = nMotorEncoder[motorB];
		motorEncoderValues[2] = nMotorEncoder[motorC];
		motorEncoderValues[3] = nMotorEncoder[motorD];
		sleep(10);
	}
}
