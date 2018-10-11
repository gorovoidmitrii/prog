

/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                          - String N Demo -                                             *|
|*                                            ROBOTC on NXT                                               *|
|*                                                                                                        *|
|*  This program demos the basic string n manipulation functions in ROBOTC which behave similarly to      *|
|*  those found in the standard C libraries.  Looking that the Global Variables screen on the Debugger    *|
|*  is a great way to see how the variables are being manipulated.                                        *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:                                                                                              *|
|*    1)  Only the NXT brick is required, no motors, no sensors.                                          *|
|*    2)  "strncat()" takes 2 strings and an int.  It concatinates the 2nd string to the end of the 1st,  *|
|*        overwriting the 1st string.  The int determines from the first character in the 2nd string,     *|
|*        how many chars to concatinate onto the end of the 1st string.                                   *|
|*    3)  "strncmp()" takes 2 strings.  It compares the strings and returns an integer value.             *|
|*        0 = the strings are the same. >0 = the 1st string is greater than the 2nd.                      *|
|*        <0 = the 1st string is less than the 2nd string (ascii value).  The int determines from the     *|
|*        first character in the 2nd string, how many chars to compare with the 1st string.               *|
|*    4)  "strncpy()" takes 2 strings.  It copies the 2nd string onto the 1st string, overwriting         *|
|*        the 1st.  The int determines from the first character in the 2nd string, how many chars to      *|
|*        copy from the 2nd string to the 1st string.                                                     *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
\*---------------------------------------------------------------------------------------------------4246-*/

task main()
{
  string strNCat1 = "ROBOT";              // Create string, 'strNCat1', "ROBOT" to be used with the strcat function.
  string strNCat2 = "C";                  // Create string, 'strNCat2', "C" to be used with the strcat function.

  string strNCmp1 = "Fett";               // Create string, 'strNCmp1', "Fett" to be used with the strcmp function.
  string strNCmp2 = "Fetts";              // Create string, 'strNCmp2', "Fett" to be used with the strcmp function.

  int strNCat2_size = sizeof(strNCat2);   // Create integer 'strNCat2_size' to hold the size of 'strNCat2' (using the "sizeof()" function).

  int strNCmp_int = 4;                    // Create integer 'strNCmp_int' to determine how many characters we will compare per string in the "strncmp()" function.

  displayTextLine(0, "%s cat %s:", strNCat1, strNCat2);                    // Display strings, 'strNCat1' and 'strNCat2'.
  wait1Msec(4000);                                                            // Wait 4 seconds (look at global vars now!)
  strncat(strNCat1, strNCat2, strNCat2_size);                                 // Concatinate 'strNCat2' to the end of 'strNCat1'.
  displayTextLine(1, "s1 = %s", strNCat1);

  wait1Msec(4000);                                                            // Wait 4 seconds (look at global vars now!)

  displayTextLine(3, "%s cmp %s", strNCmp1, strNCmp2);                     // Display strings, 'strNCmp1' and 'strNCmp2'.
  displayTextLine(4, "up to the first");
  displayTextLine(5, "%d chars only:", strNCmp_int);
  wait1Msec(4000);                                                            // Wait 4 seconds (look at global vars now!)
  displayTextLine(6, "%d", strncmp(strNCmp1, strNCmp2, strNCmp_int));                // Compare strings, 'strNCmp1' and 'strNCmp2' up to the 4th value.


  while(true)   // Infinite loop to keep display on the screen until you stop program.
  {
    sleep(1); // DO NOT CONTINUE
  }
}
