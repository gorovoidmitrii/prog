/* This is a simple Bluetooth sample program to be used with the BluetoothBasic1 program.
   It is designed to receive a simple message (in this case, the value of the variables x, y, and z), format
   and display the values on the NXT screen, and then wait 300 milliseconds before repeating the process.
   The program also clears the screen in between readings.
   */

task main()
{
  long x, y, z;
  string displayx, displayy, displayz;

while(true)
  {
  	//Receive variable values x, y, and z. Note that the messageParm array starts at 0 and not 1
    x = messageParm[0];
    y = messageParm[1];
    z = messageParm[2];

    //Formats the variables into a 'Value x: ' format and displays each on a seperate line
    stringFormat(displayx, "Value x: %d", x);
    stringFormat(displayy, "Value y: %d", y);
    stringFormat(displayz, "Value z: %d", z);

    displayCenteredTextLine(0, displayx);
    displayCenteredTextLine(2, displayy);
    displayCenteredTextLine(4, displayz);

    //Waits 300 milliseconds, clears the screen, and loops again
    wait1Msec(300);
    ClearMessage();
  }
}
