#pragma config(Sensor, S1,     touch,          sensorTouch)
#pragma config(Sensor, S2,     sound,          sensorSoundDB)
#pragma config(Sensor, S3,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorB,          rightMotor,    tmotorNXT, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorC,          leftMotor,     tmotorNXT, PIDControl, driveLeft, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


task main()
{
	turnLeft(2, seconds, 50);
	wait(1, seconds);
	turnRight(3500, milliseconds, 75);
	wait(1, seconds);
}
