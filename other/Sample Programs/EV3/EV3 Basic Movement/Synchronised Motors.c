#pragma config(Motor,  motorA,          claw,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	// setMotorSyncEncoder(nMotorOne, nMotorTwo, nTurnRatio, nEncoderCount, nSignedPower);

	// This makes it go straight (both get equal amount of power)
	setMotorSyncTime(left, right, 0, 1000, 50);
	sleep(1500);

	// This makes it go right (all power to left)
	setMotorSyncTime(left, right, 100, 1000, 50);
	sleep(1500);

	// This makes it go left (all power to right)
	setMotorSyncTime(left, right, -100, 1000, 50);
	sleep(1500);

	// This makes it go slow right (right motor turning at 50% of left one)
	setMotorSyncTime(left, right, 50, 1000, 50);
	sleep(1500);

	// This makes it go slow left (left motor turning at 50% of right one)
	setMotorSyncTime(left, right, -50, 1000, 50);
	sleep(1500);

}
