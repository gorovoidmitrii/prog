////////////////////////////////////////////////////////////////////////////////////////////////
//
//                            Simple Line Follow and Obstacle Avoidance
//
// Program is used in Syngress Press book on programming NXT with ROBOTC
//
//
////////////////////////////////////////////////////////////////////////////////////////////////

int Floor;
int line;


void Initialize()
{
  SensorType[S1] = sensorTouch;
  SensorType[S2] = sensorLightActive;
}

void WaitBumperPress()
{
  playSound(soundBeepBeep);
  while (SensorValue[S1] == 0){}  // wait for bumper press
  while (SensorValue[S1] == 1){} // wait for bumper release
}

void Calibrate()
{
  WaitBumperPress();
  Floor = SensorValue[S2];
  WaitBumperPress();
  line = SensorValue[S2];
  WaitBumperPress();
}

void Go_Straight()
{
  motor[motorA] = 50;   // motor forward at 50% of full power
  motor[motorC] = 50;   // motor forward at 50% of full power
}

void Stop()
{
  motor[motorA] =  0;   // Turn motor off
  motor[motorC] =  0;   // Turn motor off
}

void Turn_Left()
{
  motor[motorA] =  0;   // Turn motor off
  motor[motorC] = 50;   // motor forward at 50% of full power
}

void Turn_Right()
{
  motor[motorA] = 50;   // motor forward at 50% of full power
  motor[motorC] =  0;   // Turn motor off
}

void Remove_Obstacle()
{
  motor[motorB] =  50;  // motor forward at 50% of full power
  wait1Msec(2000);      // Wait 2000 milliseconds or 2 seconds.
  motor[motorB] = -50;  // Negative value reverse motor at 50% of full power.
  wait1Msec(2000);
  motor[motorB] =   0;  // Turn motor off
}

void Check_Bumper()
{
  if (SensorValue[S1] == 1)
  {
    Stop();
    Remove_Obstacle();
    Go_Straight();
  }
}

void Follow_Line()
{
  const int SENSITIVITY = 5;

  if (SensorValue[S2] <= (Floor + SENSITIVITY))
    Turn_Right();
  else if (SensorValue[S2] >= (line - SENSITIVITY))
    Turn_Left();
  else
    Go_Straight();
}

task main()
{
  Initialize();
  Calibrate();
  Go_Straight();

  while(true)
  {
    Check_Bumper();
    Follow_Line();
  }
}
