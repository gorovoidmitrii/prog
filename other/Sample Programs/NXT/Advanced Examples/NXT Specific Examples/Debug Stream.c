/*
This program is a simple example of the use of the debug stream. Adding writeDebugStream commands to programs allows you to track
the progress of the program more closely in the debugger by sending messages to the debug stream whenever your
program reaches a certain point.
*/


task main()
{
	//Turn the motors on and write to the debug stream
  motor[motorB] = 50;
  motor[motorC] = 50;
  writeDebugStream("Motors On"); //Writes a notification that the motors have been turned on in the debug stream window
  wait1Msec(3000);

  //Turn the motors off and write to the debug stream
  motor[motorB] = 0;
  motor[motorC] = 0;
  writeDebugStream("Motors Off"); //Writes a notification that the motors have been turned on in the debug stream window
  wait1Msec(3000);
}
