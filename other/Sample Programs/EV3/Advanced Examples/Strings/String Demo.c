

/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                           - String Demo -                                              *|
|*                                            ROBOTC on NXT                                               *|
|*                                                                                                        *|
|*  This program demos the basic string manipulation functions in ROBOTC which behave similarly to those  *|
|*  found in the standard C libraries.  Looking that the Global Variables screen on the Debugger is a     *|
|*  great way to see how the variables are being manipulated.                                             *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:                                                                                              *|
|*    1)  Only the NXT brick is required, no motors, no sensors.                                          *|
|*    2)  "strcat()" takes 2 strings.  It concatinates the 2nd string to the end of the 1st, overwriting  *|
|*        the 1st string.                                                                                 *|
|*    3)  "strcmp()" takes 2 strings.  It compares the strings and returns an integer value.              *|
|*        0 = the strings are the same. >0 = the 1st string is greater than the 2nd.                      *|
|*        <0 = the 1st string is less than the 2nd string.  (ascii value)                                 *|
|*    4)  "strcpy()" takes 2 strings.  It copies the 2nd string onto the 1st string, overwriting the 1st. *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
\*---------------------------------------------------------------------------------------------------4246-*/

task main()
{
  string strCat1 = "ROBOT";   // Create string, 'strCat1', "ROBOT" to be used with the strcat function.
  string strCat2 = "C";       // Create string, 'strCat2', "C" to be used with the strcat function.

  string strCmp1 = "Fett";    // Create string, 'strCmp1', "Fett" to be used with the strcmp function.
  string strCmp2 = "Fett";    // Create string, 'strCmp2', "Fett" to be used with the strcmp function.

  string strCpy1 = "<>";      // Create string, 'strCpy1', "<>" to be used with the strcpy function.
  string strCpy2 = "DNA";     // Create string, 'strCpy2', "DNA" to be used with the strcpy function.



  displayTextLine(0, "%s cat %s:", strCat1, strCat2);    // Display strings, 'strCat1' and 'strCat2'.
  wait1Msec(4000);                                          // Wait 4 seconds (look at global vars now!)
  strcat(strCat1, strCat2);                                 // Concatinate 'strCat2' to the end of 'strCat1'.
  displayTextLine(1, "s1 = %s", strCat1);

  displayTextLine(3, "%s cmp %s:", strCmp1, strCmp2);    // Display strings, 'strCmp1' and 'strCmp2'.
  wait1Msec(4000);                                          // Wait 4 seconds (look at global vars now!)
  displayTextLine(4, "%d", strcmp(strCmp1, strCmp2));    // Compare strings, 'strCmp1' and 'strCmp2'.

  displayTextLine(6, "%s cpy %s:", strCpy1, strCpy2);    // Display strings, 'strCpy1' and 'strCpy2'.
  wait1Msec(4000);                                          // Wait 4 seconds (look at global vars now!)
  strcpy(strCpy1, strCpy2);                                 // Copy 'strCpy2' to 'strCpy1'.
  displayTextLine(7, "s1 = %s", strCpy1);                // Display the new 'strCpy1'.


  while(true)   // Infinite loop to keep display on the screen until you stop program.
  {
    sleep(1); // DO NOT CONTINUE
  }
}
