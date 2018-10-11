
/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                        - StringFormat Demo -                                           *|
|*                                            ROBOTC on NXT                                               *|
|*                                                                                                        *|
|*  This program demos the "StringFormat()" function.  This function is passed a destination string, a    *|
|*  a format string, and some parameters (variables).  In this demo, we will be taking a floating point   *|
|*  number and sending it to a string.  (The string will display the floating point number.)              *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:                                                                                              *|
|*    1)  Only the NXT brick is required, no motors, no sensors.                                          *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
\*---------------------------------------------------------------------------------------------------4246-*/

task main()
{
  string dest = "";                           // Create string 'dest', to be the destination of the "StringFormat()" function.

  float number = 3.14159;                     // Create float 'number'.

  displayTextLine(0, "Float number:");     /* Display the main string  */
  displayTextLine(1, "%1.5f", number);     /* onto the NXT LCD screen. */

  wait1Msec(4000);                            // Wait for 4 seconds (look at global variables now!)

  stringFormat(dest, "%1.2f", number);        // Format 'dest' with the float, 'number' (add a number onto a string).

  displayTextLine(5, "String formatted");  /* Display the updated 'dest'    */
  displayTextLine(6, "to 2 decimals:");    /*                               */
  displayTextLine(7, "%s", dest);          /* string to the NXT LCD screen. */

  while(true)   // Infinite loop to keep the debugger open and the program running until you exit it.
  {
    // DO NOT CONTINUE
  }
}
