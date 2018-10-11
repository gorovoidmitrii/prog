/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                           - ROBOTC MATH -                                              *|
|*                                            ROBOTC on NXT                                               *|
|*                                                                                                        *|
|*  This program requires nothing but an NXT Brick.                                                       *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:                                                                                              *|
|*    1)  This program just demo's the 4 math functions included thus far in ROBOTC.                      *|
|*    2)  abs(x) returns the absolute value of x.                                                         *|
|*    3)  exp(x) returns e ^ x.                                                                           *|
|*    4)  sgn(x) returns a negative number if x is negative, or a positive number if x is positive.       *|
|*    5)  sqrt(x) returns the square root of x.                                                           *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
\*---------------------------------------------------------------------------------------------------4246-*/


task main()
{

  int nAbsNum = -4246;                  // 'nAbsNum' is set to -4246, a number we will use for the "abs()" function.
  int nAbsResult = abs(nAbsNum);        // 'nAbsResult' is set to the absolute value of 'nAbsNum'.

  float lExpNum = 8.3538;               // 'lExpNum' is set to 8.3538, an interesting number which we will use for the "exp()" function.
  float lExpResult = exp(lExpNum);      // 'lExpResult' is set to (e ^ 'lExpNum').

  int nSgnNum = -46;                    // 'nSgnNum' is set to -46, a number we will use for the "sgn()" function.
  int nSgnResult = sgn(nSgnNum);        // 'nSgnResult' is set to < 0 if 'nSgnNum' is negative and > 0 if 'nSgnNum' is positive.

  float fSqrtNum = 1802.8516;           // 'fSqrtNum' is set to -46, a number we will use for the "sgn()" function.
  float fSqrtResult = sqrt(fSqrtNum);   // 'fSqrtResult' is set to < 0 if 'nSgnNum' is negative and > 0 if 'nSgnNum' is positive.

  displayTextLine(0, "%d", nAbsResult);      // Display 'nAbsResult'.
  displayTextLine(2, "%4.0f", lExpResult);   // Display 'lExpResult'.
  displayTextLine(4, "%d", nSgnResult);      // Display 'nSgnResult'.
  displayTextLine(6, "%2.2f", fSqrtResult);  // Display 'fSqrtResult'.

  while(true)
  {
    // Infinite loop (used to keep the program alive so you can view the display as long as you want).
  }

}
