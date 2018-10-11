#pragma config(StandardModel, "RVW SQUAREBOT")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/********************************\
|*  ROBOTC Virtual World        *|
|*  forward (Natural Language)  *|
\********************************/

// This program drives forward for 2.5 seconds and speed 75.

task main()
{
  forward(75);    // move forward at speed 75
  wait(2.5);      // wait for 2.5 seconds
  stop();         // stop the robot
}