#pragma config(StandardModel, "VEX IQ Clawbot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


task main()
{
	resetTimer(T1);
	setMultipleMotors(50, leftMotor, rightMotor, rightMotor, rightMotor);
	waitUntil (getTimer(T1, seconds) >= 5);
	stopAllMotors();
}
