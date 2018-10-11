
int xPos;
int yPos;

void testSinglePixels()
{
	for (yPos = 0; yPos < 45; ++yPos)
	{
		for (xPos = 0; xPos < 128; ++xPos)
		{
			setPixel(xPos, yPos);
		}
		sleep(25);
	}
	for (yPos = 0; yPos < 45; ++yPos)
	{
		for (xPos = yPos; xPos < 128; ++xPos)
		{
			clearPixel(xPos, yPos);
		}
		sleep(25);
	}
  return;
}

void testVerticalLines()
{
	for (xPos = 0; xPos < 128; ++xPos)
	{
		drawLine(xPos, 0, xPos, 45);
		sleep(10);
	}
	for (xPos = 0; xPos < 128; ++xPos)
	{
		eraseLine(xPos, 0, xPos, 45);
		sleep(10);
	}
  return;
}

void testHorizontalLines()
{
	for (yPos = 0; yPos <= 45; ++yPos)
	{
		drawLine(0, yPos, xPos, yPos);
		sleep(10);
	}
	for (yPos = 0; yPos <= 45; ++yPos)
	{
		eraseLine(0, yPos, 127, yPos);
		sleep(10);
	}
	for (yPos = 0; yPos <= 45; ++yPos)
	{
		if (yPos > 0)
			invertLine(0, yPos - 1, 127, yPos - 1);

		invertLine(0, yPos, 127, yPos);
		sleep(200);
	}
	for (yPos = 0; yPos <= 45; ++yPos)
	{
		drawLine(0, yPos, xPos, yPos);
		sleep(10);
	}
  return;
}

void testDrawRect()
{
	eraseDisplay();
	for (yPos = 0; yPos < 45; yPos += 4)
	{
		xPos = 5 + yPos * 3 / 2;
		fillRect(xPos,      yPos,   xPos + 10, yPos + 10);
		//DrawInvertRect(xPos,yPos,   xPos + 10, yPos + 10);
		sleep(300);
		eraseRect(xPos,      yPos,   xPos + 10, yPos + 10);
		sleep(300);
	}
	sleep(200);
  return;
}

void testDrawCircle()
{
	for (yPos = 0; yPos < 45; yPos += 4)
	{
		xPos = 5 + yPos * 3 / 2;
		drawEllipse(xPos,      yPos,   xPos + 10, yPos + 10);
		fillEllipse(xPos,      yPos,   xPos + 10, yPos + 10);
		//DrawInvertRect(xPos,yPos,   xPos + 10, yPos + 10);
		sleep(300);
		eraseEllipse(xPos,      yPos,   xPos + 10, yPos + 10);
		sleep(300);
	}
	sleep(200);
	eraseDisplay();
  return;
}


void testDrawText()
{
	for (yPos = 19; yPos < 29; ++yPos)
	{
		xPos = 5 + (yPos - 19) * 12;
		displayStringAt(0, 7, "      ");
		displayStringAt(0, 7, "AaBbCc");
		displayInverseStringAt(0, 7, "AaBbCcDdEeFfGg");
		displayBigStringAt(0, 30, "AaBbCc");
		displayTextLine(0, "Text Line 0");
    displayTextLine(1, "Text Line 1");
    displayTextLine(2, "Text Line 2");
    displayTextLine(3, "Text Line 3");
    displayTextLine(4, "Text Line 4");
    displayTextLine(5, "Text Line 5");
    displayInverseBigStringAt(0, 30, "AaBbCcDdEeFfGg");
		displayStringAt(0, 16, "      ");
    sleep(200);
    break;
	}
	sleep(200);
	eraseDisplay();
  return;
}


task main()
{
	setUserDebugWindow(true);
  while (true)
	{
		eraseDisplay();
		//testDrawRect();
		//testDrawCircle();
		//testDrawText();
		testSinglePixels();
		//testHorizontalLines();
		//testVerticalLines();
	}
  return;
}
