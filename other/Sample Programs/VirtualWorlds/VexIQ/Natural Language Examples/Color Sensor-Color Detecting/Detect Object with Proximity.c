#pragma config(StandardModel, "VEX IQ Clawbot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


task main()
{
	setMultipleMotors(50, leftMotor, rightMotor, rightMotor, rightMotor);
	waitUntil (getColorProximity(colorDetector) < 100);
	backward(1.5, rotations, 50);
	setMotorTarget(armMotor, 150, 50);
	wait(1, seconds);
	setMotorTarget(clawMotor, 75, 50);
	wait(1, seconds);
	stopAllMotors();
}
