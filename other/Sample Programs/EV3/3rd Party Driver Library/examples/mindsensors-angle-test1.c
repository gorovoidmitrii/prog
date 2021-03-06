#pragma config(Sensor, S1,     MSANG,               sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * mindsensors-angle.h provides an API for the Mindsensors Angle Sensor.  This program
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
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * date 31 November 2012
 * version 0.1
 */

#include "mindsensors-angle.h"

task main () {
  nNxtButtonTask  = -2;
  displayCenteredTextLine(0, "Mindsensors");
  displayCenteredBigTextLine(1, "Angle");
  displayCenteredTextLine(3, "Test 1");
  displayCenteredTextLine(5, "Connect sensor");
  displayCenteredTextLine(6, "to S1");
  sleep(2000);

  eraseDisplay();
  displayCenteredTextLine(0, "GlideWheel-AS");
  displayTextLine(1, "-------------------");
  displayTextLine(5, "-------------------");
  while (true) {
    // Reset the angle to 0
    if (nNxtButtonPressed == kEnterButton)
    {
      MSANGresetAngle(MSANG);
      while (nNxtButtonPressed != kNoButton) sleep(1);
    }

    // Read the current angle, accumulated angle and RPM and display them
    displayTextLine(2, "Ang: %7d deg", MSANGreadAngle(MSANG));
    displayTextLine(3, "Raw: %7d", MSANGreadRaw(MSANG));
    displayTextLine(4, "RPM: %7d", MSANGreadRPM(MSANG));
    displayTextLine(7, "   Reset angle");
    sleep(50);
  }
}
