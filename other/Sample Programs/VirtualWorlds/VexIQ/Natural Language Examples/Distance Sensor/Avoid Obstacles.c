#pragma config(StandardModel, "VEX IQ Clawbot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


task main()
{
	repeat (forever) {
		if (getDistanceValue(distanceMM) > 75) {
			setMotor(motor1, 50);
			setMotor(motor6, 50);
		} else {
			stopAllMotors();
			wait(1, seconds);
			backward(2, seconds, 50);
			turnLeft(1, seconds, 50);
		}
	}
}
