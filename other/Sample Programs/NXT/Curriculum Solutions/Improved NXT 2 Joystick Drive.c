#include "JoystickDriver.c"

task main()
{
  while(1 == 1)
  {
    getJoystickSettings(joystick);

    if(joystick.joy1_y1 < 5 && joystick.joy1_y1 > -5)
    {
      motor[motorC] = 0;
    }
    else
    {
      motor[motorC] = joystick.joy1_y1/2;
    }

    if(joystick.joy1_y2 < 5 && joystick.joy1_y2 > -5)
    {
      motor[motorB] = 0;
    }
    else
    {
      motor[motorB] = joystick.joy1_y2/2;
    }
  }
}
