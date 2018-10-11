////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                          Test  LCD Display Drawing Execution Speed
//
// This program is used to test the execution speed of the LCD display
// drawing cababilities of the  brick.
//
// The basic methodology is to:
//  [1] measure the time to loop 1,000 times through an empty 'for' loop.
//  [2] measure the time to loop 1,000 times through an 'for' loop containing
//      210 identical statements.
//  [3] Take the time difference between the two loops to find the time to
//      execute 10,000 statements.
//  [4] Interpret to determine the number of microseconds per statement.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT)

const int kNumberOfLoops = 1000; // 1K x 10 instructions per loop = 10K instructions

const TTimers  executionTimer = T1;

//
// Types of tests that can be performed.
//
typedef enum TInstructions
{
	typeIdleLoop,

	typesetPixel,
	typeclearPixel,

	typeDrawText,
	typeFormatAndDrawText,

	typeEraseScreen,

	typedrawRect,
	typeFillRect,
	typeEraseRect,

	typeDrawEllipse,
	typeFillEllipse,
	typeEraseEllipse,

	typeDrawVertLine,
	typeDrawHorizLine,
	typeDrawDiagonalLine,


	typeLast,
} TInstructions;

int index;

long idleLoopTime = 0;
float fElapsedTime[(TInstructions) (typeLast)];
long loopTime;
long elapsed;

void measureTime(const TInstructions nInstructionType)
{
	int x  = 50;
	int y  = 32;
	int x1 = 18;
	int y1 =  0;
	int x2 = 81;
	int y2 = 63;

	time1[executionTimer] = 0;
  for (index = 1; index <= kNumberOfLoops; ++index)
	{
    //
		// to measure a different instruction type, simply change the
		// definition of the following constant.
		//
		switch (nInstructionType)
		{
			//
			// Since 'nInstructionType' is a constant, code optimizer will eliminate
			// the 'switch' instruction and the 'dead code' for the unreachable
			// cases.
			//
			case typeIdleLoop:
				break;

			case typesetPixel:
		    {
		    	setPixel(x, y); setPixel(x, y); setPixel(x, y); setPixel(x, y); setPixel(x, y);
		    	setPixel(x, y); setPixel(x, y); setPixel(x, y); setPixel(x, y); setPixel(x, y);
				}
				break;

			case typeclearPixel:
		    {
		    	clearPixel(x, y); clearPixel(x, y); clearPixel(x, y); clearPixel(x, y); clearPixel(x, y);
		    	clearPixel(x, y); clearPixel(x, y); clearPixel(x, y); clearPixel(x, y); clearPixel(x, y);
				}
				break;

			case typeDrawText:
		    {
		    	displayStringAt( 7,  7, "Mindstorms ");
		    	displayStringAt( 7,  7, "Mindstorms ");
		    	displayStringAt( 7,  7, "Mindstorms ");
		    	displayStringAt( 7,  7, "Mindstorms ");
		    	displayStringAt( 7,  7, "Mindstorms ");

		    	displayStringAt( 7,  7, "Mindstorms ");
		    	displayStringAt( 7,  7, "Mindstorms ");
		    	displayStringAt( 7,  7, "Mindstorms ");
		    	displayStringAt( 7,  7, "Mindstorms ");
		    	displayStringAt( 7,  7, "Mindstorms ");
				}
				break;

				case typeFormatAndDrawText:
		    {
		    	displayStringAt( 7,  7, "Number is %d", x);
		    	displayStringAt( 7,  7, "Number is %d", x);
		    	displayStringAt( 7,  7, "Number is %d", x);
		    	displayStringAt( 7,  7, "Number is %d", x);
		    	displayStringAt( 7,  7, "Number is %d", x);

		    	displayStringAt( 7,  7, "Number is %d", x);
		    	displayStringAt( 7,  7, "Number is %d", x);
		    	displayStringAt( 7,  7, "Number is %d", x);
		    	displayStringAt( 7,  7, "Number is %d", x);
		    	displayStringAt( 7,  7, "Number is %d", x);
				}
				break;


			case typeEraseScreen:
		    {
		    	eraseDisplay(); eraseDisplay(); eraseDisplay(); eraseDisplay(); eraseDisplay();
		    	eraseDisplay(); eraseDisplay(); eraseDisplay(); eraseDisplay(); eraseDisplay();
				}
				break;

			case typedrawRect:
		    {
		    	drawRect(x1, y1, x2, y2); drawRect(x1, y1, x2, y2); drawRect(x1, y1, x2, y2); drawRect(x1, y1, x2, y2); drawRect(x1, y1, x2, y2);
		    	drawRect(x1, y1, x2, y2); drawRect(x1, y1, x2, y2); drawRect(x1, y1, x2, y2); drawRect(x1, y1, x2, y2); drawRect(x1, y1, x2, y2);
				}
				break;

			case typeFillRect:
		    {
		    	fillRect(x1, y1, x2, y2); fillRect(x1, y1, x2, y2); fillRect(x1, y1, x2, y2); fillRect(x1, y1, x2, y2); fillRect(x1, y1, x2, y2);
		    	fillRect(x1, y1, x2, y2); fillRect(x1, y1, x2, y2); fillRect(x1, y1, x2, y2); fillRect(x1, y1, x2, y2); fillRect(x1, y1, x2, y2);
				}
				break;

			case typeEraseRect:
		    {
		    	eraseRect(x1, y1, x2, y2); eraseRect(x1, y1, x2, y2); eraseRect(x1, y1, x2, y2); eraseRect(x1, y1, x2, y2); eraseRect(x1, y1, x2, y2);
		    	eraseRect(x1, y1, x2, y2); eraseRect(x1, y1, x2, y2); eraseRect(x1, y1, x2, y2); eraseRect(x1, y1, x2, y2); eraseRect(x1, y1, x2, y2);
				}
				break;

			case typeDrawEllipse:
		    {
		    	drawEllipse(x1, y1, x2, y2); drawEllipse(x1, y1, x2, y2);
		    	drawEllipse(x1, y1, x2, y2); drawEllipse(x1, y1, x2, y2);
		    	drawEllipse(x1, y1, x2, y2); drawEllipse(x1, y1, x2, y2);
		    	drawEllipse(x1, y1, x2, y2); drawEllipse(x1, y1, x2, y2);
		    	drawEllipse(x1, y1, x2, y2); drawEllipse(x1, y1, x2, y2);
		    	drawEllipse(x1, y1, x2, y2); drawEllipse(x1, y1, x2, y2);
				}
				break;

			case typeFillEllipse:
		    {
		    	fillEllipse(x1, y1, x2, y2); fillEllipse(x1, y1, x2, y2);
		    	fillEllipse(x1, y1, x2, y2); fillEllipse(x1, y1, x2, y2);
		    	fillEllipse(x1, y1, x2, y2); fillEllipse(x1, y1, x2, y2);
		    	fillEllipse(x1, y1, x2, y2); fillEllipse(x1, y1, x2, y2);
		    	fillEllipse(x1, y1, x2, y2); fillEllipse(x1, y1, x2, y2);
				}
				break;

			case typeEraseEllipse:
		    {
		    	eraseEllipse(x1, y1, x2, y2); eraseEllipse(x1, y1, x2, y2);
		    	eraseEllipse(x1, y1, x2, y2); eraseEllipse(x1, y1, x2, y2);
		    	eraseEllipse(x1, y1, x2, y2); eraseEllipse(x1, y1, x2, y2);
		    	eraseEllipse(x1, y1, x2, y2); eraseEllipse(x1, y1, x2, y2);
		    	eraseEllipse(x1, y1, x2, y2); eraseEllipse(x1, y1, x2, y2);
				}
				break;

			case typeDrawVertLine:
		    {
		    	drawLine(x1, y1, x1, y2); drawLine(x1, y1, x1, y2);
		    	drawLine(x1, y1, x1, y2); drawLine(x1, y1, x1, y2);
		    	drawLine(x1, y1, x1, y2); drawLine(x1, y1, x1, y2);
		    	drawLine(x1, y1, x1, y2); drawLine(x1, y1, x1, y2);
		    	drawLine(x1, y1, x1, y2); drawLine(x1, y1, x1, y2);
				}
				break;

			case typeDrawHorizLine:
		    {
		    	drawLine(x1, y1, x2, y1); drawLine(x1, y1, x2, y1);
		    	drawLine(x1, y1, x2, y1); drawLine(x1, y1, x2, y1);
		    	drawLine(x1, y1, x2, y1); drawLine(x1, y1, x2, y1);
		    	drawLine(x1, y1, x2, y1); drawLine(x1, y1, x2, y1);
		    	drawLine(x1, y1, x2, y1); drawLine(x1, y1, x2, y1);
				}
				break;

			case typeDrawDiagonalLine:
		    {
		    	drawLine(x1, y1, x2, y2); drawLine(x1, y1, x2, y2);
		    	drawLine(x1, y1, x2, y2); drawLine(x1, y1, x2, y2);
		    	drawLine(x1, y1, x2, y2); drawLine(x1, y1, x2, y2);
		    	drawLine(x1, y1, x2, y2); drawLine(x1, y1, x2, y2);
		    	drawLine(x1, y1, x2, y2); drawLine(x1, y1, x2, y2);
				}
				break;

		}
	}

	loopTime = time1[executionTimer];
  elapsed = loopTime - idleLoopTime;
	fElapsedTime[nInstructionType] = ((float) elapsed) / (float) 10.0;
	if (nInstructionType == typeIdleLoop)
		idleLoopTime = loopTime;

	// 'elapsed' contains the number of 1 msec 'ticks' to execute 10,000 (1,000 loops
	// each with 10) statements. Thus if 'elapsed' is 146, a single statement took
	// 14.6 microseconds:
	//   - 146 millisecons total 'adjusted' time in loop (146 ticks x 1 milliseconds)
	//   - 146 milliseconds is same as 146,000 microseconds
	//   - divide by 10,000 to get 14.6 microseconds

	playSound(soundBlip);
	return;
}

task main()
{

	for (index = (short) typeIdleLoop; index < (short) typeLast; ++index)
	  fElapsedTime[index] = 0;

	measureTime(typeIdleLoop);

	measureTime(typesetPixel);
	measureTime(typeclearPixel);

	measureTime(typedrawRect);
	measureTime(typeFillRect);
	measureTime(typeEraseRect);

	measureTime(typeDrawText);
	measureTime(typeFormatAndDrawText);

	measureTime(typeDrawEllipse);
	measureTime(typeFillEllipse);
	measureTime(typeEraseEllipse);

	measureTime(typeDrawVertLine);
	measureTime(typeDrawHorizLine);
	measureTime(typeDrawDiagonalLine);

	measureTime(typeEraseScreen);

	playSound(soundBeepBeep);
	while (bSoundActive)
	{}
	return;
}
