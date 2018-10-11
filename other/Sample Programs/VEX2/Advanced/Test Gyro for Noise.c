#pragma config(Sensor, in7,    gyro,                sensorGyro)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//////////////////////////////////////////////////////////////////////////////////////////////
//
//                                VEX LCD and Gyro Demo
//
// Short little program to demonstrate the VEX LCD and Gyro sensor.
//
// Gyro sensor is configured on Analog Port '7'. THe VEX LCD is used to display the various gyro
// parameters:
//    - Calculated angle.
//    - Dead band.
//    - Full Scale (for modulus function). In this case 3600 for 360 degrees.
//    - Scaling factor used to translate analog value to angular acceleration (in degrees)
//    - Dead band to eliminate noise measurements.
//    - Bias value which is calculated with 200 measurements at steady state.
//
// Using the "enter" (Center) button will zero the sensor. [But not recalculate the bias].
//
//////////////////////////////////////////////////////////////////////////////////////////////


int nMenuIndex = 0;

int nOffset;
int nBiasRough;
int nBias;
int nBiasSmall;
int nBiasSmaller;
int nSeconds = 0;
int nSampleSum;
int nCount;
int nCycles;
int nPlusMinus = 0;
int nPlusMinusWeighted = 0;

//const int kCentered = 25;
typedef enum TScale
{
  kCentered = 32,

  kMinus1   = kCentered - 1,
  kMinus2   = kCentered - 2,
  kMinus3   = kCentered - 3,
  kMinus4   = kCentered - 4,
  kMinus5   = kCentered - 5,
  kMinus6   = kCentered - 6,
  kMinus7   = kCentered - 7,
  kMinus8   = kCentered - 8,
  kMinus9   = kCentered - 9,
  kMinus10  = kCentered - 10,
  kMinus11  = kCentered - 11,
  kMinus12  = kCentered - 12,
  kMinus13  = kCentered - 13,
  kMinus14  = kCentered - 14,
  kMinus15  = kCentered - 15,
  kMinusRange = kCentered - 16,

  kPlus1   = kCentered + 1,
  kPlus2   = kCentered + 2,
  kPlus3   = kCentered + 3,
  kPlus4   = kCentered + 4,
  kPlus5   = kCentered + 5,
  kPlus6   = kCentered + 6,
  kPlus7   = kCentered + 7,
  kPlus8   = kCentered + 8,
  kPlus9   = kCentered + 9,
  kPlus10  = kCentered + 10,
  kPlus11  = kCentered + 11,
  kPlus12  = kCentered + 12,
  kPlus13  = kCentered + 13,
  kPlus14  = kCentered + 14,
  kPlus15  = kCentered + 15,
  kPlusRange = kCentered + 16,
} TScale;

int nDrift = 0;
unsigned int nTimeStamp;
int nLastCycles;
int nSampleHisogram[(TScale) 65];

task testMotorNoise();

task main()
{
  int i;
  const int kNumbOfMainSamples = 4000;

  bLCDBacklight = true;
  displayLCDPos(0, 0);
  displayNextLCDString("Gyro Noise Test ");
  memset(&nSampleHisogram[0], 0, sizeof(nSampleHisogram));
  wait1Msec(1000);

  // Calculate a rough mezsure of 'bias' sum that fits in 16-bit signed.
  nSampleSum = 0;

  const int kRoughBiasCounts = 30;
  for (i = 0; i < kRoughBiasCounts; ++i)
  {
    nSampleSum += SensorValue[gyro];
    wait1Msec(1);
  }
  nBiasRough = nSampleSum / kRoughBiasCounts;

  nSampleSum = 0;
  for (i = 0; i < kNumbOfMainSamples; ++i)
  {
    nOffset = SensorValue[gyro] - nBiasRough;
    nSampleSum += nOffset;
    wait1Msec(1);
  }
  nBias = nBiasRough + nSampleSum / kNumbOfMainSamples;
  nBiasSmall = nSampleSum / (kNumbOfMainSamples / 100)   - (nSampleSum / kNumbOfMainSamples) * 100;
  nBiasSmaller = nSampleSum / (kNumbOfMainSamples / 1000) - nBiasSmall * 10;

  startTask(testMotorNoise);
  nLastCycles = -1;

  bool bDisplayIt;
  bool bOverflow = false;
  for (nCycles = 0; true; ++nCycles)
  {
    //ASSERT(nCycles == (nLastCycles + 1));
    nLastCycles = nCycles;
    nTimeStamp = nPgmTime;
    nOffset = SensorValue[gyro] - nBias;
    nDrift += nOffset;
    if (nCycles >= 0)
    {
	    if ((nCycles % 100) == 50)
	      nDrift -= nBiasSmall;
	    if ((nCycles % 1000) == 500)
	    {
	      nDrift -= nBiasSmaller;
	      bDisplayIt = true;
	    }
	    else
	      bDisplayIt = false;
    }
    else
    {
	    if ((nCycles % 1000) == -50)
	      nDrift -= nBiasSmall;
	    if ((nCycles % 1000) == -500)
	    {
	      nDrift -= nBiasSmaller;
	      bDisplayIt = true;
	    }
	    else
	      bDisplayIt = false;
    }

    if (nOffset < -32)
      nOffset = -32;
    else if (nOffset > 32)
      nOffset = 32;

    nCount = nSampleHisogram[nOffset + 32];
    if (nCount >= 32767)
      bOverflow = true;
    if (!bOverflow)
      ++nSampleHisogram[nOffset + 32];
    if (true)
    {
      nPlusMinusWeighted += nOffset;
	    if (nOffset < 0)
	      --nPlusMinus;
	    else if (nOffset > 0)
	      ++nPlusMinus;
	  }
    if (bDisplayIt)
    {
      ++nSeconds;
      displayLCDPos(1, 0);
		  displayNextLCDNumber(nSeconds, 3);
	    displayNextLCDString("   : ");
	    if (nDrift > 0)
	    {
		    displayNextLCDNumber(nDrift / 1000);
		    displayNextLCDChar('.');
	      displayNextLCDNumber(nDrift % 1000, -3);
		  }
		  else
	    {
		    displayNextLCDChar('-');
		    displayNextLCDNumber(- nDrift / 1000);
		    displayNextLCDChar('.');
	      displayNextLCDNumber(- nDrift % 1000, -3);
	    }
	    displayNextLCDChar(' ');
	    displayNextLCDChar(' ');
	  }

    while (nTimeStamp == nPgmTime)
    {}
  }
  stopTask(testMotorNoise);
}

task testMotorNoise()
{
  while (true)
  {
    motor[port2] = 100;
    wait1Msec(7000);
    motor[port2] = -100;
    wait1Msec(7000);
  }
}
