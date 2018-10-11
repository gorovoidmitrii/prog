#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     , sensorI2CMuxController)
#pragma config(Sensor, S2,     gyro, sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorA,          gripperMotor,  tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          wristMotor,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     frontRightMotor, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     frontLeftMotor, tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     rearRightMotor, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     rearLeftMotor, tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     rightScissor,  tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     leftScissor,   tmotorTetrix, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Scissorbot Gyro - Autonomous Score Routine

This program is designed for the the Virtual World 'FTC Block Party!'
It is designed to score the preload block in the blue box with a Scissorbot
at start point B4.

Start at B4 with Scissorbot
1) Move forward for 1800 encoder counts (using encoders)
2) Turn to the left until gyro reads -55 degrees (using gyroscope)
3) Raise scissor lift for 1600 encoder counts (using the lift's encoder)
4) Move forward for 2200 encoder counts (using encoders)
5) Flip the gripper's wrist up for 100 encoder counts (using encoders)
6) Move forward until close enough to pendulum (using encoders)
7) Open gripper and score the preload object

Robot Model(s): TETRIX Scissorbot Gyro (Virtual Worlds)
[I/O Port]          [Name]              [Type]                [Description]
Motor Port A 				gripperMotor				NXT Motor 						NXT Gripper Motor
Motor Port B				wristMotor					NXT Motor 						NXT Wrist Motor
Motor Port D        frontRightMotor     TETRIX Motor          Front Right side motor
Motor Port E				frontLeftMotor			TETRIX Motor					Front Left side motor (encoder)
Motor Port F        rearRightMotor      TETRIX Motor          Rear Right side motor
Motor Port G				rearLeftMotor				TETRIX Motor					Rear Left side motor
Motor Port H 				rightScissorMotor		TETRIX Motor					Right Scissor Lift motor
Motor Port I 				leftScissorMotor		TETRIX Motor 					Left Scissor Lift motor (encoder)

Sensor Port 2				gyro						    Gyroscope							Gyroscopic Sensor
Sensor Port 3				lightSensor  				Light Sensor					NXT Light Sensor (Active)
Sensor Port 4				sonarSensor 				Sonar Sensor					NXT Sonar Sensor
----------------------------------------------------------------------------------------------------*/

task main()
{

	//Step 1
	//Clear the encoders
	nMotorEncoder(rearRightMotor) = 0;
	nMotorEncoder(rearLeftMotor)  = 0;

	//While the right motor's encoder is greater than -1800 counts
	while(nMotorEncoder[rearLeftMotor] > -1800)
	{
		//Move the robot forward
		motor[frontRightMotor] = 75;
		motor[frontLeftMotor]  = 75;
		motor[rearRightMotor] = 75;
		motor[rearLeftMotor]  = 75;
	}

	//Stop the robot
	motor[frontRightMotor]= 0;
	motor[frontLeftMotor] = 0;
	motor[rearRightMotor] = 0;
	motor[rearLeftMotor]  = 0;

	//Step 2
	//While the gyro reads greater than -35 degrees (-350 counts)
	while(SensorValue[gyro] > -350)
	{
		//Quickly turn to the left
		motor[frontRightMotor] =    75;
		motor[frontLeftMotor]  =   -75;
		motor[rearRightMotor] =     75;
		motor[rearLeftMotor]  =    -75;
	}

	//Stop the robot
	motor[frontRightMotor] = 0;
	motor[frontLeftMotor]  = 0;
	motor[rearRightMotor] =  0;
	motor[rearLeftMotor]  =  0;

	//While the gyro reads greater than -55 degrees (-550 counts)
	while(SensorValue[gyro] > -550)
	{
		//Slowly turn to the left
		motor[frontRightMotor] =   30;
		motor[frontLeftMotor] =   -30;
		motor[rearRightMotor] =    30;
		motor[rearLeftMotor]  =   -30;
	}

	//Stop the robot
	motor[frontRightMotor] = 0;
	motor[frontLeftMotor]  = 0;
	motor[rearRightMotor] =  0;
	motor[rearLeftMotor]  =  0;

	//Step 3
	//Clear the lift motor's encoder
	nMotorEncoder(leftScissor) = 0;

	//While the scissor lift's encoder reads less than 1600 counts
	while(nMotorEncoder(leftScissor) < 1600)
	{
		//Raise the lift
		motor[rightScissor] = 100;
		motor[leftScissor] = 100;
	}
	//Stop raising the lift
	motor[rightScissor] = 0;
	motor[leftScissor] = 0;

	wait1Msec(500);

	//Step 4
	//Clear the encoders
	nMotorEncoder(rearRightMotor) = 0;
	nMotorEncoder(rearLeftMotor)  = 0;

	//While the left motor's encoder is greater than -2200 counts
	while(nMotorEncoder[rearLeftMotor] > -2200)
	{
		//Move the robot forward
		motor[frontRightMotor] = 75;
		motor[frontLeftMotor]  = 75;
		motor[rearRightMotor] = 75;
		motor[rearLeftMotor]  = 75;
	}

	//Stop the robot
	motor[frontRightMotor]= 0;
	motor[frontLeftMotor] = 0;
	motor[rearRightMotor] = 0;
	motor[rearLeftMotor]  = 0;

	//Step 5
	//Clear the wrist's encoder value
	nMotorEncoder[motorB] = 0;

	//While the wrist's encoder is less than 100
	while(nMotorEncoder[motorB] < 100)
		{
			//Flip the wrist
			motor[wristMotor] = 50;
  	}

	//Turn off the intake
	motor[wristMotor] = 0;

	//Step 6
	//Clear the encoders
	nMotorEncoder(rearRightMotor) = 0;
	nMotorEncoder(rearLeftMotor)  = 0;

	//While the left motor's encoder is greater than -600 counts
	while(nMotorEncoder[rearLeftMotor] > -600)
	{
		//Move the robot forward
		motor[frontRightMotor] = 75;
		motor[frontLeftMotor]  = 75;
		motor[rearRightMotor] = 75;
		motor[rearLeftMotor]  = 75;
	}

	//Stop the robot
	motor[frontRightMotor]= 0;
	motor[frontLeftMotor] = 0;
	motor[rearRightMotor] = 0;
	motor[rearLeftMotor]  = 0;

	//Step 7
	//Open the gripper for 1.5 seconds and score the object
	motor[gripperMotor] = -50;
	wait1Msec(1500);
	//Turn off the intake
	motor[gripperMotor] = 0;
}