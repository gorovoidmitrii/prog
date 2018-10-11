#pragma config(StandardModel, "RVW REMBOT")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


/**************************\
|*  ROBOTC Virtual World  *|
|*  Forward until Sonar   *|
\**************************/

// This program goes forward until the sonarSensor sensor sees an object closer than our 'threshold'.

task main()
{
  int threshold = 40;   // create and set variable 'threshold' to 40 (will be distance for sonarSensor)

  while(SensorValue(sonar) > threshold || SensorValue(sonar) == -1)   // while the sonarSensor sensor is reading in values larger than our
  {                                                                   // threshold, or reading out of range (-1 = no object in sight)
                              // move forward:
    motor[rightMotor] = 75;   // set motorB to speed 75
    motor[leftMotor]  = 75;   // set motorC to speed 75
  }
                              // stop the robot:
  motor[rightMotor] = 0;      // set motorB to speed 0
  motor[leftMotor]  = 0;      // set motorC to speed 0
}
