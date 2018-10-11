#include "JoystickDriver.c"
#pragma DebuggerWindows("joystickSimple")

task main()
{
  while(1 == 1)
  {
    getJoystickSettings(joystick);
    motor[motorC] = joystick.joy1_y1;
    motor[motorB] = joystick.joy1_y2;
  }
}
