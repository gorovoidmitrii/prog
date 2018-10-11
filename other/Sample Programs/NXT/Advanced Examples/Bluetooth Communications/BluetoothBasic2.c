/* This is a simple Bluetooth sample program to be used with the BluetoothBasic1 program.
   It is designed to receive a simple message (in this case, the value of the variable y), format
   and display the value on the NXT screen, and then wait 300 milliseconds before repeating the process.
   The program also clears the screen in between readings.
   */

task main()
{
  long y=0;
  string display;

while(true)
  {
  	//Receives message and formats into a 'Value: y' format for display
    y=message;
    stringFormat(display, "Value: %d", y);

    //Displays the 'display' string, waits 300 milliseconds, clears the screen, and repeats code
    displayCenteredTextLine(3, display);
    wait1Msec(300);
    ClearMessage();
  }
}
