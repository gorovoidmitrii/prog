//////////////////////////////////////////////////////////////////////////////////////////
//
//                        Hitechnic Acceleration Sensor Example
//                        =====================================
//
// This file is a small application program that tests the NXT Acceleration Sensor from HiTechnic.
//
// The program:
//  1. Configures sensor port 'S2' as a HiTechnic acceleration sensor.
//  2. Displays the current acceleration components (X, Y, and Z axes) on the NXT LCD. Both
//     the raw values and "normalized" values are displayed. There's about 200 counts per 1G.
//
// The range of values is -400 to +400 (i.e. -2G to +2G) on each axis.
//
// To determine which axis is which, lay the sensor flat on a table. Two axes should show
// 0 acceleration and one axis (the Z-axis) should show a force of about 1.00 which is the
// force of gravity. Now rotate the sensor 90 degrees upwards and the Z-axis will change to
// value 0 and one of the other axis will have value approximately 1.00. Very neat!!
//
//////////////////////////////////////////////////////////////////////////////////////////

#pragma platform (NXT, TETRIX)
#pragma fileExtension("rtm")

#include "AdvancedSensors.c"    // include library files



task main()
{
  tSensors nAccelSensorPort;

	displayCenteredBigTextLine(0, "Accel");
	displayCenteredBigTextLine(2, "Test");

  displayCenteredTextLine(5, "Connect Accel");
  displayCenteredTextLine(6, "to any port");

	while (!findSensor(nAccelSensorPort, "HITECHNC", "Accel.  "))
	{
    wait1Msec(20);
  }
  SensorType[nAccelSensorPort] = sensorI2CHiTechnicAccel; // Configure the sensor

  eraseDisplay();
  while (true)
  {
    //
    // Get the acceleration from the sensor and display on the NXT LCD
    // Display both the raw sensor value and the normalized (G) value).
    // Note; 200 counts is approximately 1G.
    //
    int nXAxis;
    int nYAxis;
    int nZAxis;
    static float fXAxis = 0.0;
    static float fYAxis = 0.0;
    static float fZAxis = 0.0;
    const float kGravityConst = 200.0;
    const int kXCenter = 31;
    const int kYCenter = 31;
    const int kWidth   = 30;
    const int kWidthY  = 22;

    getAccel(nAccelSensorPort, nXAxis, nYAxis, nZAxis);

    invertLine(kXCenter, kYCenter,    kXCenter + (int) (fXAxis * kWidth),  kYCenter);
    invertLine(kXCenter, kYCenter,    kXCenter + (int) (fYAxis * kWidthY), kYCenter + (int) (fYAxis * kWidthY));
    invertLine(kXCenter, kYCenter,    kXCenter,                            kYCenter + (int) (fZAxis * kWidth));

    fXAxis = ((float) nXAxis) / kGravityConst;
    fYAxis = ((float) nYAxis) / kGravityConst;
    fZAxis = ((float) nZAxis) / kGravityConst;

    // Fudge to minimize very small values

    if (abs(fXAxis) <= 0.03)
      fXAxis = 0;
    if (abs(fYAxis) <= 0.03)
      fYAxis = 0;
    if (abs(fZAxis) <= 0.03)
      fZAxis = 0;

    invertLine(kXCenter, kYCenter,    kXCenter + (int) (fXAxis * kWidth),  kYCenter);
    invertLine(kXCenter, kYCenter,    kXCenter + (int) (fYAxis * kWidthY), kYCenter + (int) (fYAxis * kWidthY));
    invertLine(kXCenter, kYCenter,    kXCenter,                            kYCenter + (int) (fZAxis * kWidth));

    displayStringAt(58,  63, "    Raw");
    displayStringAt(58,  55, "X:%5d",    nXAxis);
    displayStringAt(58,  47, "Y:%5d",    nYAxis);
    displayStringAt(58,  39, "Z:%5d",    nZAxis);
    displayStringAt(58,  31, " Normlz");
    displayStringAt(58,  23, "X:%5.2f",  fXAxis);
    displayStringAt(58,  15, "Y:%5.2f",  fYAxis);
    displayStringAt(58,   7, "Z:%5.2f",  fZAxis);
    wait1Msec(100);
  }
  return;
}
