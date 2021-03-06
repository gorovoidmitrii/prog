#pragma config(StandardModel, "RVW REMBOT")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


/**************************************\
|*  ROBOTC Virtual World              *|
|*  Avoiding obstacles with the Sonar *|
\**************************************/

// This program uses the sonarSensor sensor to approach and object and maintain a set
// distance from it.  (if the object moves closer, the robot will back up)

task main()
{
  int speed = 0;          // will hold the speed of the motors
  int sonarValue = 0;     // will hold the values read in by the Sonar Sensor
  int distance = 35;      // specified distance to be at 35 centimeters

  while(true)
  {
    sonarValue = SensorValue(sonar);        // set 'sonarValue' to the current reading of the sonarSensor sensor

    if(sonarValue == -1)                    // if the object is out of range:
    {
      speed = 100;                          // set speed to 100
    }
    else                                    // otherwise, if we see and object:
    {
      speed = (sonarValue - distance) * 3;  // set 'speed' to the (sonarSensor reading - our desired distance) * 3 for speed
    }

    motor[rightMotor] = speed;               // set motorB is run at a power level equal to 'speed'
    motor[leftMotor]  = speed;               // set motorC is run at a power level equal to 'speed'
  }
}
