
/* This is a simple Bluetooth sample program to be used with the BluetoothBasic2 program.
   It is designed to send a simple message (in this case, the value of the variable x), increment
   x, and then wait 300 milliseconds before repeating the process. There is a ten second delay at
   the start of the program.*/

task main()
{
	//Waits 10 seconds to ensure Bluetooth connection is valid
  wait1Msec(10000);

  //Creates and initializes integer x with a value of 2
  int x=2;
  while (true)
    {
  //Sends x over Bluetooth, increments its value, and waits 300 milliseconds before repeating process
    sendMessage(x);
    x=x+1;
    wait1Msec(300);
    }
 }
