///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Random Number Generator Test
//
// Quick little program to calculate the efficiency (speed) and validity of the random number generator. You need
// to use the NXT debugger with this program and look at the histogram of random values and the execution time
// per cycle through the loop.
//
// The variable 'fTimePerLoopMicroSecs' will contain the time in microseconds to perform the statement
//            ++nHistogram[random(kSize - 1)];
//
// The array 'nHistogram' will contain the number of counts eachof the available random numbers (i.e. 0..30)
// were returned by the random function. You need to have the debugger open to see this variable.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int i;

const int kSize = 31;
const int kCounts = 31000;
int nElapsedTimeEmptyLoop;
int nElapsedTimeRandomLoop;
float fTimePerLoopMicroSecs;
int nHistogram[kSize];

task main()
{
  //
  // Zero out histogram array. This will collect peg counts of the random number distribution.
  //
  for (i = 0; i < kSize; ++i)
    nHistogram[i] = 0;

  //
  // Initialize the random number seed.
  //
  // The seed can be set to any valye from -32767 to +32767. It is used by the internal pseudo-random
  // number generator in the robot controller firmware.
  //
  srand(7659);

  //
  // Calculate time for an empty loop
  //
  time1[T1] = 0;
  for (i = 0; i < kCounts; ++i)
  {}
  nElapsedTimeEmptyLoop = time1[T1];

  //
  // Collect a bunch of samples
  //  -- the array 'nHistogram' will contain counts of the number of times each sample value was 'hit'
  //
  time1[T1] = 0;
  for (i = 0; i < kCounts; ++i)
  {
  	//int nRandomValue;

  	//nRandomValue = random(kSize - 1);
  	//++nHistogram[nRandomValue];
  	++nHistogram[random(kSize - 1)];
  }
  nElapsedTimeRandomLoop = time1[T1];

  //
  // Let's figure out the execution performane of the 'random' function.
  //    -- subtract the loop time from the empty loop time to get the time for
  //       the instructions within the loop.
  //    -- divide by total number of loops to get time for one cycle through the loop
  //    -- Convert milliseconds to microseconds in the result
  //
  fTimePerLoopMicroSecs = (nElapsedTimeRandomLoop - nElapsedTimeEmptyLoop) / (float) kCounts;
  fTimePerLoopMicroSecs *= 1000;  // Convert milliseconds to microseconds
  return;
}
