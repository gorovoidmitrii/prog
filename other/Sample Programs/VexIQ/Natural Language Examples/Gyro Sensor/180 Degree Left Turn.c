#pragma config(StandardModel, "VEX IQ Clawbot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


task main()
{
	resetGyro(port4);
	setMotor(leftMotor, -50);
	setMotor(rightMotor, 50);
	waitUntil (getGyroDegrees(gyroSensor) >= 180);
	setMultipleMotors(50, leftMotor, rightMotor, rightMotor, rightMotor);
}
