#pragma config(Sensor, S1,     MAGICWAND,      sensorI2CCustomFastSkipStates)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * mindsensors-magicwand.h provides additional functionality on top of the PCF8574 driver for
 * the Mindsensors Magic Wand. This program demonstrates how to use that API to
 * control the LEDs for fun and profit!
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Magic Wand driver originally written by Mike Partain a.k.a. Spiked3 (http://www.spiked3.com/)
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * 29 July 2012
 * version 0.1
 */

#include "mindsensors-magicwand.h"

task main () {

  MSMWclearALL(MAGICWAND);

  while (true)
  {

    // Blink LED 0 5 times
    for (short i = 0; i < 5; i++)
    {
      MSMWsetLED(MAGICWAND, 0, true);
      sleep(150);
      MSMWsetLED(MAGICWAND, 0, false);
      sleep(50);
    }

    // Do the same as above, only use the toggle function
    // Toggle LED 4
    for (short i = 0; i < 10; i++)
    {
      MSMWtoggleLED(MAGICWAND, 4);
      sleep(200);
    }

    // Flash pulse all of the LEDs quickly
    for (short i = 0; i < 3; i++)
    {
      MSMWsetALL(MAGICWAND);
      sleep(50);
      MSMWclearALL(MAGICWAND);
      sleep(150);
    }

    // Use a cool flash effect and clear them all
    MSMWflashAndClear(MAGICWAND, 4);

    for (short j = 1; j < 10; j++)
    {
      short r = random(7);
      MSMWsetLED(MAGICWAND, r, true);
      for (short i = 0; i < 10; i++)
      {
        MSMWtoggleLED(MAGICWAND, 4);
        sleep(100);
      }
      MSMWsetLED(MAGICWAND, r, false);
    }
    sleep(500);
    MSMWclearALL(MAGICWAND);

  }

}
