
/* This is a simple Bluetooth sample program to be used with the BluetoothBasic2 program.
   It is designed to send a simple message (in this case, the values of the variable x, y, and z),
   increment the variables by their initial values, and then wait 300 milliseconds before repeating the process.
   There is a ten second delay at the start of the program.*/

task main()
{
	//Waits 10 seconds to ensure Bluetooth connection is valid
  wait1Msec(10000);

  //Creates and initializes three integer variables (x, y, and z) with values of 1, 2, and 3, respectively.
  int x=1;
  int y=2;
  int z=3;
  while (true)
    {
  /*Sends all three varibles over Bluetooth, then increments them by their initial values. The program then
    waits 300 milliseconds and then repeats the process. */
    sendMessageWithParm(x, y, z);
    x=x+1;
    y=y+2;
    z=z+3;
    wait1Msec(300);
    }
 }
