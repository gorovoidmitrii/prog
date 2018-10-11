#pragma config(StandardModel, "RVW RANGER")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Forward until Close Proximity
This program instructs your robot to move forward until it detects an object within 20 cm, then stop.
There is a two second pause at the beginning of the program.

Robot Model(s): TETRIX Ranger

[I/O Port]          [Name]              [Type]                		[Description]
mtr_S1_C1_1        rightMotor          TETRIX Motor             Right side motor
mtr_S1_C1_2        leftMotor           TETRIX Motor             Left side motor, reversed
Sensor Port 4      sonarSensor         Ultrasonic        				Front mounted, facing forward

----------------------------------------------------------------------------------------------------*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	wait1Msec(2000);						// Robot waits for 2000 milliseconds before executing program

	while(SensorValue(sonar) > 20  || SensorValue(sonar) == -1)		// Loop while robot's Ultrasonic sensor is further than 20 inches away from an object
	{                                                                         // || (or) it is '-1'.  (-1 is the value returned when nothing is in it's visable range)
		motor[rightMotor] = 50;			// Motor on motorB is run at half (50) power forward
		motor[leftMotor]  = 50;			// Motor on motorC is run at half (50) power forward
	}

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
