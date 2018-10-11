
/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                         - StringFind Demo -                                            *|
|*                                            ROBOTC on NXT                                               *|
|*                                                                                                        *|
|*  This program demos the "StringFind()" function.  This function is passed a 2 strings.  The 1st string *|
|*  is the source which you will search in, and the 2nd is the search string you are trying to find.      *|
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
  string str_msg = "meshiddensage";                     // Create string 'str_msg', "meshiddensage".
  string str_secret = "hidden";                         // Create string 'str_secret', "hidden".
  int search_location;                                  // Create int 'search_location'.

  displayTextLine(0, "String:");                     /* Display the main string  */
  displayTextLine(1, "%s", str_msg);                 /* onto the NXT LCD screen. */

  displayTextLine(3, "Message to find:");            /* Display the secret you wish  */
  displayTextLine(4, "%s", str_secret);              /* to find to the NXT LCD.      */

  search_location = stringFind(str_msg, str_secret);    // Search for the hidden message!

  displayTextLine(6, "Starts at index:");            /* Display to the NXT LCD, the index */
  displayTextLine(7, "%d", search_location);         /* of the secret hidden message.     */

  while(true)   // Infinite loop to keep the debugger open and the program running until you exit it.
  {
    sleep(1); // DO NOT CONTINUE
  }
}
