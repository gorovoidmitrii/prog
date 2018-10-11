/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                           - Swing  Turn -                                              *|
|*                                            ROBOTC on NXT                                               *|
|*                                                                                                        *|
|*  This program turns your taskbot on an arch.                                                           *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:                                                                                              *|
|*    1)  You may need to change the wait times used to achieve a 90 degree turn.  Experiment to find     *|
|*        the perfect values.                                                                             *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
|*    Port C                  motorC              NXT                 Right motor                         *|
|*    Port B                  motorB              NXT                 Left motor                          *|
\*---------------------------------------------------------------------------------------------------4246-*/

task main()
{
	int i = 0;                   // The variable 'i' is declared as an integer, and initialized to equal zero.

	while(i < 3)                // While 'i' is less than 20:
	{
		motor[motorC] = 75;             // Motor C is run at a 75 power level.
		motor[motorB] = 0;              // Motor B is stopped.
		wait1Msec(750);                 // The robot turns for 750 milliseconds before running further code.

		motor[motorC] = -75;             // Motor C is run at a -75 power level.
		motor[motorB] = 0;              // Motor B is stopped.
		wait1Msec(750);                 // The robot turns for 750 milliseconds before running further code.

    motor[motorC] = 0;              // Motor C is stopped.
		motor[motorB] = 75;             // Motor B is run at a 75 power level.
		wait1Msec(750);                 // The robot turns for 750 milliseconds before running further code.

		motor[motorC] = 0;              // Motor C is stopped.
		motor[motorB] = -75;             // Motor B is run at a -75 power level.
		wait1Msec(750);                 // The robot turns for 750 milliseconds before running further code.

    i++;                            // The variable "i" is incremented (increased) by 1.
  }
}
