#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     rightMotor,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftMotor,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     armMotor,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     intakeMotor,   tmotorTetrix, openLoop, encoder)

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Conveyorbot Gyro - Autonomous Score Routine

This program is designed for the the Virtual World 'FTC Block Party!'
It is designed to score the preload block in the blue box with a Conveyorbot
at start point B1.

Start at B1 with Conveyorbot
1) Move forward for 4000 encoder counts (using encoders)
2) Turn to the right until gyro reads 45 degrees (using gyroscope)
3) Line track onto the ramp for 3000 encoder counts (using light sensor and encoders)
4) Raise arm for 600 encoder counts (using the arm's encoder)
5) Turn to the right until gyro reads 140 degrees (using gyroscope)
6) Move forward until close enough to side wall (using sonar)
7) Lower arm for -200 encoder counts (using the arm's encoder)
8) Turn on intake (reversed) and score the preload object

Robot Model(s): TETRIX Conveyorbot (Gyro) (Virtual Worlds)

[I/O Port]          [Name]              [Type]                [Description]
Motor Port D        rightMotor          TETRIX Motor          Right side motor
Motor Port E				leftMotor						TETRIX Motor					Left side motor
Motor Port F 				armMotor						TETRIX Motor					Arm motor
Motor Port G 				intakeMotor					TETRIX Motor 					Intake motor

Sensor Port 2				gyro								HiTechnic Gyro				HiTechnic Gyro
Sensor Port 3				light   						Light Sensor					NXT Light Sensor (Active)
Sensor Port 4				sonar 							Sonar Sensor					NXT Sonar Sensor

----------------------------------------------------------------------------------------------------*/


task main()
{
	//Threshold for line tracking
	int threshold = 85;

	//Step 1
	//Clear the encoders
	nMotorEncoder(rightMotor) = 0;
	nMotorEncoder(leftMotor)  = 0;

	//While the right motor's encoder is less than 4000 counts
	while(nMotorEncoder(rightMotor) < 4000)
	{
		//Move the robot forward
		motor[rightMotor] = 75;
		motor[leftMotor]  = 75;
	}

	//Stop the robot
	motor[rightMotor]= 0;
	motor[leftMotor] = 0;

	//Step 2
	//While the gyro reads less than 35 degrees (350 counts)
	while(SensorValue[gyro] < 350)
	{
		//Quickly turn to the right
		motor[rightMotor] =	-75;
		motor[leftMotor]  =  75;
	}

	//Stop the robot
	motor[rightMotor] = 0;
	motor[leftMotor]  = 0;

	//While the gyro read less than 45 degrees (450 counts)
	while(SensorValue[gyro] < 450)
	{
		//Slowly turn to the right
		motor[rightMotor] = -30;
		motor[leftMotor] = 30;
	}

	//Stop the robot
	motor[rightMotor] = 0;
	motor[leftMotor]  = 0;

	//Step 3
	//Clear the encoders
	nMotorEncoder(rightMotor) = 0;
	nMotorEncoder(leftMotor)  = 0;

	//While the right motor's encoder reads less than 3800 counts
	while(nMotorEncoder(rightMotor) < 3000)
	{
		//Line track forward
		if(SensorValue[light] < threshold) //If the robot sees a tile
		{
			//Turn to the left
			motor[rightMotor] = 60;
			motor[leftMotor] = 40;
		}

		else //If the robot sees the line
		{
			//Turn to the right
			motor[rightMotor] = 40;
			motor[leftMotor] = 60;
		}
	}

	//Stop the robot
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;

	wait1Msec(500);

	//Step 4
	//Clear the arm motor's encoder
	nMotorEncoder(armMotor) = 0;

	//While the arm motor's encoder reads less than 600 counts
	while(nMotorEncoder(armMotor) < 600)
	{
		//Raise the arm
		motor[armMotor] = 100;
	}
	//Stop raising the arm
	motor[armMotor] = 0;

	wait1Msec(500);
	//Step 5
	//While the gyro reads less than 125 degrees (1250 counts)
	while(SensorValue[gyro] < 1250)
	{
		//Quickly turn to the right
		motor[rightMotor] =	-75;
		motor[leftMotor]  =  75;
	}

	//Stop the robot
	motor[rightMotor] = 0;
	motor[leftMotor]  = 0;

	//While the gyro reads less than 140 degrees (1400 counts)
	while(SensorValue[gyro] < 1400)
	{
		//Slowly turn to the right
		motor[rightMotor] = -30;
		motor[leftMotor] = 30;
	}

	//Stop the motors
	motor[rightMotor] = 0;
	motor[leftMotor]  = 0;

	wait1Msec(250);
	//Step 6
	//Clear the arm motor's encoder
	nMotorEncoder(armMotor) = 0;

	//While the arm motor's encoder reads greater than -200
	while(nMotorEncoder(armMotor) > -200)
	{
		//Lower the arm
		motor[armMotor] = -100;
	}
	//Stop lowering the arm
	motor[armMotor] = 0;

	//Step 7
	//While the sonar reads greater than 14
	while(SensorValue(sonar) > 14)
	{
		//Slowly move forward
		motor[rightMotor] = 30;
		motor[leftMotor] = 30;
	}

	//Stop the robot
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
	wait1Msec(250);
	//Step 8
	//Turn on the intake (reversed) for 1.5 seconds and score the object
	motor[intakeMotor] = -50;
	wait1Msec(1500);
	//Turn off the intake
	motor[intakeMotor] = 0;
}