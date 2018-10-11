#pragma config(Sensor, S1,     touchSensor,    sensorTouch)
#pragma config(Sensor, S2,     compassSensor,  sensorVirtualCompass)
#pragma config(Sensor, S3,     lineFollower,   sensorLightActive)
#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)
#pragma config(Motor,  motorA,          gripperMotor,  tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          rightMotor,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          leftMotor,     tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Sector 3 - Back Road Insertion Point (Standard ROBOTC)
- This program will cause the robot to drive forward from Sector 1 into Sector 3, and turn toward
	the Charge Cube in that area.
- It will be up to you to add the ROBOTC code that causes the robot to pick up the Charge Cube
	and take it to the Communication Tower pad.
- Remember that you can press the "Reset" button in the lower-left corner of the Operation Reset
	window to return to the Insertion Point every time you modify your ROBOTC code.
*	Please note that the values in this program were written for Mammalbot using a high-end computer.
	You may need to adjust the values in this program for your computer.

Robot Model: Mammalbot

[I/O Port]          [Name]              [Type]                   [Description]
Motor Port B        rightMotor          Motor        		    		 Right side motor
Motor Port C        leftMotor           Motor          		   	   Left side motor
----------------------------------------------------------------------------------------------------*/

//Every program has a task main(). All commands that the robot follows go between the curly braces.
task main()
{	//The program begins.
	wait1Msec(2000);		//The robot will wait for 2 seconds before executing commands.

	//Reset the encoders to 0.
	nMotorEncoder[rightMotor] = 0;
	nMotorEncoder[leftMotor] = 0;

	while(nMotorEncoder[rightMotor] < 2520)	//while less than 2520 counts of the right motor encoder have passed...
	{
		//...move forward.
		motor[rightMotor] = 50;
		motor[leftMotor] = 50;
	}

	//Stop
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;

	wait1Msec(1000);		//The robot will wait for 1 second before executing other commands.

	//Reset the encoders to 0.
	nMotorEncoder[rightMotor] = 0;
	nMotorEncoder[leftMotor] = 0;

	while(nMotorEncoder[rightMotor] < 60)	//while less than 50 counts of the right motor encoder have passed...
	{
		//...turn left.
		motor[rightMotor] = 50;
		motor[leftMotor] = -50;
	}

	//Stop
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;

	wait1Msec(1000);		//The robot will wait for 1 second before executing other commands.

  //Enter the code for the robot to drive forward to the charge cube here:


  //Enter the code for the robot to turn right toward the Communication Tower here:


  //Enter the code for the robot to drive forward to the Communication Tower pad here:


}	//The program ends.