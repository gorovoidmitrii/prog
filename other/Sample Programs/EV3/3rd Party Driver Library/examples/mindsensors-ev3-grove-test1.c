#pragma config(Sensor, S1,     GROVE,          sensorEV3_GenericI2C)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * mindsensors-ev3-grove.h provides an API for the Mindsensors EV3-Grove Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.29 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 */

#include "mindsensors-ev3-grove.h"



// main task
task main ()
{
  displayCenteredTextLine(0, "Mindsensors");
  displayCenteredBigTextLine(1, "EV3-Grove");
  displayCenteredTextLine(3, "Test 1");
  sleep(2000);

  // Create struct to hold sensor data
  tGROVE groveSensor;

  // Initialise and configure struct, port and sensor type
  if (!initSensor(&groveSensor, S1, grove_AnalogLight))
  	writeDebugStreamLine("Init failed!");

  while(true)
  {
    // Read the sensor data.
    readSensor(&groveSensor);
    displayTextLine(1, "A:%4d", groveSensor.analog);
  }
}
