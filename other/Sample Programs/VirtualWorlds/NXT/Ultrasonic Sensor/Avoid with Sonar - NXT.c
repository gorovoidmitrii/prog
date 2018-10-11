#pragma config(StandardModel, "RVW REMBOT")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


/**************************************\
|*  ROBOTC Virtual World              *|
|*  Avoiding obstacles with the Sonar *|
\**************************************/

// This program drives forward until the sonarSensor sensor sees an object closer than a
// set 'threshold' variable.  It then backs up and turns right until it sees some space.


int threshold = 40;   // threshold for sonarSensor sensor

task main()
{
  // run forever:
  while(true)
  {
    // go forward at speed 75:
    motor[rightMotor] = 75;
    motor[leftMotor]  = 75;

    // if an object is detected closer than our 'threshold':
    if(SensorValue(sonar) < threshold && SensorValue(sonar) != -1)
    {
      // HALT and back up!:
      motor[rightMotor] = -75;
      motor[leftMotor]  = -75;
      wait1Msec(1000);

      // turn until the path ahead seems clear:
      while(SensorValue(sonar) < (threshold * 2))
      {
        // turn right in place at speed 75:
        motor[rightMotor] = -75;
        motor[leftMotor]  = 75;
      }
    }
  }
}
