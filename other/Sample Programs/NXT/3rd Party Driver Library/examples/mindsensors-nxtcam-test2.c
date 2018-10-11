#pragma config(Sensor, S1,     cam,                 sensorI2CCustomFastSkipStates)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * mindsensors-nxtcam.h provides an API for the Mindsensors NXTCam.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * Credits:
 * - Gordon Wyeth for writing the original driver and cam_display program
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * 28 November 2009
 * version 0.2
 */

#include "mindsensors-nxtcam.h"

// short xscale(short x) - Scales x values from camera coordinates to screen coordinates.
short xscale(short x) {
  return ((x - 12) * 99) / 87;
}

// short yscale(short y) - Scales y values from camera coordinates to screen coordinates.
short yscale(short y) {
  return ((143 - y) * 63) / 143;
}

/*
 Main task
 */
task main () {
  blob_array _blobs;
  memset(_blobs, 0, sizeof(blob_array));

  // combine all colliding blobs into one
  bool _condensed = true;

  //blob_array _blobs;
  short _l, _t, _r, _b;
  short _x, _y;
  short _nblobs;
  eraseDisplay();

  // Initialise the camera
  NXTCAMinit(cam);
  while(true) {
    eraseDisplay();
    // Fetch all the blobs, have the driver combine all
    // the colliding blobs.
    _nblobs = NXTCAMgetBlobs(cam, _blobs, _condensed);
    for (short i = 0; i < _nblobs; i++) {
      // Draw the scaled blobs
      _l = xscale(_blobs[i].x1);
      _t = yscale(_blobs[i].y1);
      _r = xscale(_blobs[i].x2);
      _b = yscale(_blobs[i].y2);
      drawRect(_l, _t, _r, _b);

    }
    NXTCAMgetAverageCenter(_blobs, 3, 0, _x, _y);
    _x = xscale(_x);
    _y = yscale(_y);
    eraseRect(_x-4, _y-4, _x+4, _y+4);
    drawLine(_x, _y+2, _x, _y-2);
    drawLine(_x+2, _y, _x-2, _y);
    displayTextLine(1, "%d", _nblobs);
    sleep(100);
  }
}
