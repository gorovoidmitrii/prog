#pragma config(StandardModel, "RVW Clampbot IQ")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Function Declarations (full Function Definitions are below task main)
//Functions to control how far and fast the robot should move forward and backward
void moveForward(int nDegrees, int nSpeed);
void moveBackward(int nDegrees, int nSpeed);

//Functions to control how far and fast the robot should turn right and left
void turnRight(int nDegrees, int nSpeed);
void turnLeft(int nDegrees, int nSpeed);

//Functions to rotate the arm and wrist
void moveArm(int nDegrees, int nSpeed);
void moveWrist(int nDegrees, int nSpeed);

//Functions to open and close the claw
void openClaw();
void closeClaw();

//Functions to manually control the rotation of the belt
void spinBeltClockWise();
void spinBeltCounterClockWise();
void stopBelt();

task main()
{
	sleep(2000);
	//---Test Code for Belt Control---
	//spinBeltClockWise();
	//sleep(5000);
	//spinBeltCounterClockWise();
	//sleep(5000);
	//stopBelt();
	//sleep(5000);

	//---Test Code for Arm, Wrist, and Claw Control---
	//moveArm(2000, 100);
	//moveArm(-2000, 100);
	//moveWrist(2000, 100);
	//moveWrist(-2000, 100);
	//openClaw();
	//closeClaw();

	//---Test Code for Basic Movement Control---
	//moveForward(720, 75);
	//moveBackward(720, 75);
	//turnRight(720, 75);
	//turnLeft(720, 75);
}

//Function Definitions
void moveForward(int nDegrees, int nSpeed)
{
	//Make sure the speed and distance to move are positive values
	nSpeed = abs(nSpeed);
	nDegrees = abs(nDegrees);

	//Move both motors the desired distance at the desired speed
	moveMotorTarget(leftMotor, nDegrees, nSpeed);
	moveMotorTarget(rightMotor, nDegrees, nSpeed);

	//Wait for motors to finish moving
	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);
}

void moveBackward(int nDegrees, int nSpeed)
{
	//Make sure the speed and distance to move are negative values
	nSpeed = abs(nSpeed)*-1;
	nDegrees = abs(nDegrees)*-1;

	//Move both motors the desired distance at the desired speed
	moveMotorTarget(leftMotor, nDegrees, nSpeed);
	moveMotorTarget(rightMotor, nDegrees, nSpeed);

	//Wait for motors to finish moving
	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);
}

void turnRight(int nDegrees, int nSpeed)
{
	//Make sure the speed and distance to move are positive values
	nSpeed = abs(nSpeed);
	nDegrees = abs(nDegrees);

	//Move both motors the desired distance at the desired speed
	moveMotorTarget(leftMotor, nDegrees, nSpeed);
	moveMotorTarget(rightMotor, -nDegrees, -nSpeed);

	//Wait for motors to finish moving
	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);
}

void turnLeft(int nDegrees, int nSpeed)
{
	//Make sure the speed and distance to move are positive values
	nSpeed = abs(nSpeed);
	nDegrees = abs(nDegrees);

	//Move both motors the desired distance at the desired speed
	moveMotorTarget(leftMotor, -nDegrees, -nSpeed);
	moveMotorTarget(rightMotor, nDegrees, nSpeed);

	//Wait for motors to finish moving
	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);
}

void moveArm(int nDegrees, int nSpeed)
{
	//Reset the timer that will be used to prevent the program getting stuck
	clearTimer(T4);

	//Move motor the desired number of degrees at the desired speed
	moveMotorTarget(armMotor, nDegrees, nSpeed);

	//Wait for motor to finish moving, or for the move to time out
	repeatUntil(!getMotorMoveComplete(armMotor) || time1[T4] > 3000)
	{
		sleep(5);
	}
	setMotorSpeed(armMotor, 0);
}

void moveWrist(int nDegrees, int nSpeed)
{
	//Reset the timer that will be used to prevent the program getting stuck
	clearTimer(T3);

	//Move motor the desired number of degrees at the desired speed
	moveMotorTarget(wristMotor, nDegrees, nSpeed);

	//Wait for motor to finish moving, or for the move to time out
	repeatUntil(!getMotorMoveComplete(wristMotor) || time1[T3] > 3000)
	{
		sleep(5);
	}
	setMotorSpeed(wristMotor, 0);
}

void openClaw()
{
	//Open the claw for 1.5 seconds
	setMotorSpeed(clawMotor, -75);
	sleep(1500);
	setMotorSpeed(clawMotor, 0);
}

void closeClaw()
{
	//Close the claw for 1.5 seconds
	setMotorSpeed(clawMotor, 75);
	sleep(1500);
	setMotorSpeed(clawMotor, 0);
}

void spinBeltClockWise()
{
	//Violet spins the belt CW
	setTouchLEDColor(touchLED, colorViolet);
}

void spinBeltCounterClockWise()
{
	//Yellow spins the belt CCW
	setTouchLEDColor(touchLED, colorYellow);
}

void stopBelt()
{
	//No color turns the belt off
	setTouchLEDColor(touchLED, colorNone);
}
