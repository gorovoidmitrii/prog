#pragma config(Sensor, dgtl6,  touchSensor,         sensorTouch)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                        - Wait for Release -                                        *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs the robot to move forward at half speed until the bumper sensor is         *|
|*  released.  There is a two second pause at the beginning of the program.                           *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor Port 2        rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor Port 3        leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital Port 6      touchSensor         VEX Bumper Switch     Front mounted, facing forward.    *|
\*-----------------------------------------------------------------------------------------------4246-*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	wait1Msec(2000);						            // Robot waits for 2000 milliseconds before executing program

	while(SensorValue(touchSensor) == 0)		// Instructs robot to do nothing while the touch sensor isn't pressed
	{
	}

	wait1Msec(250);                         // Wait just a bit before moving on (to help touch sensor remain consistant

	while(SensorValue(touchSensor) == 1)		// Loop while robot's bumper/touch sensor IS pressed in
	{
		motor[rightMotor] = 63;			          // Motor on port2 is run at half (63) power forward
		motor[leftMotor]  = 63;			          // Motor on port3 is run at half (63) power forward
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
