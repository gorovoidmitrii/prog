#pragma config(StandardModel, "RVW SQUAREBOT")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
2 Joystick Drive
- This program allows you to remotely control your robot using the USB Logitech Dual
  Action Joysticks.
- For USB values to be transmitted to the robot, you must follow several steps:
  - Use the "#include "JoystickDriver.c"" line at the beginning of your program
  - Call the "getJoystickSettings(joystick);" in a loop to repeatedly retrieve the latest values
  - Open the Robot > Debugger Windows > "Joystick Control - Basic" window after downloading your
    program to the virtual robot

Robot Model(s): Squarebot

[I/O Port]          [Name]              [Type]                [Description]
Motor Port 2        rightMotor          VEX Motor             Right side motor
Motor Port 3        leftMotor           VEX Motor             Left side motor

*To run this sample program on Swervebot, be sure to Reverse Motor Port 3 in the Motors and Sensors
 Setup, and to make sure that Motor Port 2 is NOT Reversed.
----------------------------------------------------------------------------------------------------*/

#pragma debuggerWindows("joystickSimple");
#include "JoystickDriver.c"

task main()
{
  //Loop Forever
  while(1 == 1)
  {
    //Get the Latest joystick values
    getJoystickSettings(joystick);
    //Set the driving motors equal to the Y-axis values of the joysticks
    motor[leftMotor] = joystick.joy1_y1;
    motor[rightMotor] = joystick.joy1_y2;
  }
}