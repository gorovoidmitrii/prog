
/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                        - StringDelete Demo -                                           *|
|*                                            ROBOTC on NXT                                               *|
|*                                                                                                        *|
|*  This program demos the "StringDelete()" function.  This function is passed a string and 2 integer     *|
|*  values.  The 1st value is the index of the 1st character you wish to delete, and the 2nd value is     *|
|*  the length of substring you wish to delete.                                                           *|
|*  Ex. "StringDelete("HELLO", 1, 3);" Takes the character 'E' since index 1 is the 2nd character because *|
|*  indexing starts with 0.  Then it takes the characters 'L' and 'L' since "ELL" is the 3 character long *|
|*  substring starting at index 1.                                                                        *|
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
  string str = "mesGARBAGEsage";                // Create string variable, 'str', "mesGARBAGEsage".

  displayTextLine(0, "Original String:");    /* Display the orginal string,  */
  displayTextLine(1, "%s", str);             /* 'str' to the NXT LCD.        */

  wait1Msec(4000);                              // Wait for 4 seconds (look at global variables now!)

  displayTextLine(2, "   ^^^^^^^");          /* Display the underlying '^' to show */
  displayTextLine(3, "Delete these (^)");    /* which characters will be deleted.  */

  wait1Msec(4000);                              // Wait for 4 seconds (look at global variables now!)

  stringDelete(str, 3, 7);                      // Delete the 7 character long substring in 'str' starting at the 3rd index (4th character).

  displayTextLine(5, "New String:");         /* Display the new string, str,       */
  displayTextLine(6, "%s", str);             /* after deleting a substring within. */

  while(true)   // Infinite loop, to keep the debugger open and running for you.  Just stop the program when finished.
  {
    // DO NOT CONTINUE
  }
}
