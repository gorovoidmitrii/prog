

/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                            - FOR  Loop -                                               *|
|*                                            ROBOTC on NXT                                               *|
|*                                                                                                        *|
|*  This program runs your robot in a square five times.                                                  *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:                                                                                              *|
|*    1)  You may need to change the wait times used to achieve a 90 degree turn.  Experiment to find     *|
|*        the perfect values and your robot should end facing the same direction that it started.         *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
|*    Port C                  motorC              NXT                 Right motor                         *|
|*    Port B                  motorB              NXT                 Left motor                          *|
\*---------------------------------------------------------------------------------------------------4246-*/


task main()
{
   int i;                    //the variable "i" is declared as an integer

   //a for loop is declared that: intializes i equal to zero
   //continues to run under the condition i is less than 20
   //and increments i by one after each iteration
   for(i = 0; i< 20; i++)
   {
      motor[motorB] = 75;    // Motor C is run at a 75 power level.
      motor[motorC] = 75;    // Motor B is run at a 75 power level.
      wait1Msec(4000);       // The program waits 4000 milliseconds before running further code.

      motor[motorB] = 75;    // Motor C is run at a 75 power level.
      motor[motorC] = -75;   // Motor B is run at a -75 power level.
      wait1Msec(750);        // The program waits 750 milliseconds before running further code.
   }
}
