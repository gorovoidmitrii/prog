#pragma config(StandardModel, "RVW SQUAREBOT")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Point Turns

This program instructs your robot to make a point turn right for 0.75 seconds, wait for 1 second and then
make a point turn left for 0.75 seconds.  There is a two second pause at the beginning of the program.

Robot Model(s): Squarebot & Swervebot

[I/O Port]          [Name]              [Type]                [Description]
Motor Port 2        rightMotor          VEX Motor             Right side motor
Motor Port 3        leftMotor           VEX Motor             Left side motor

*To run this sample program on Swervebot, be sure to Reverse Motor Port 3 in the Motors and Sensors
 Setup, and to make sure that Motor Port 2 is NOT Reversed.
----------------------------------------------------------------------------------------------------*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	wait1Msec(2000);						// Robot waits for 2000 milliseconds before executing program

	// Turn Right at full power for 0.75 seconds
	motor[rightMotor] = -127;		  // Motor on port2 is run at full (-127) power reverse
	motor[leftMotor]  = 127;			// Motor on port3 is run at full (127) power forward
	wait1Msec(750);					      // Robot runs previous code for 750 milliseconds before moving on

  motor[rightMotor] = 0;		    // Motor on port2 is turned off
	motor[leftMotor]  = 0;			  // Motor on port3 is turned off
	wait1Msec(1000);					    // Robot stops for 1 second

	// Turn Left at full power for 0.75 seconds
	motor[rightMotor] = 127;			// Motor on port2 is run at full (127) power forward
	motor[leftMotor]  = -127;		  // Motor on port3 is run at full (-127) power reverse
	wait1Msec(750);					      // Robot runs previous code for 750 milliseconds before moving on
}													      // Program ends, and the robot stops
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
