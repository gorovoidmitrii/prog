/*
This program creates a digital clock that you can set and run on your NXT LCD screen.
*/


//
// Declare variables to hold the time and initialize them to zero
//
int second  = 0;
int minute  = 0;
int hour    = 0;


void displayTime()
{
  string sTime;
  string sSecond;
  //
  // Build time string in format "hh:mm:ss"
  //
  stringFormat(sTime, "%2d:%02d", hour, minute);
  stringFormat(sSecond, ":%02d", second);
  sTime = sTime + sSecond; // concatenate the two strings;
  //
  // Now display it on the LCD
  //
  displayBigStringAt(2, 16, sTime);
  return;
}

void runClock()
{
  while (true)
  {
    //
    // Loop forever incrementing second, minute, hour
    //
    displayTime();
    wait1Msec(1000); // Waits one second
    second = second + 1;
    if (second >= 60)
    {
      second = 0;
      minute = minute + 1;
      if (minute >= 60)
      {
        minute = 0;
        hour = hour + 1;
        if (hour >= 12)
          hour = 0;
      }
    }
  }
}

//
// Use right / left / enter keys to adjust minute and hour
//
void setTimeBeforeStartingClock()
{
  nNxtButtonTask = -2;   // Tell NXT OS that your program will use the buttons

  // Display some help info on the LCD display

  displayCenteredTextLine(0, "Left/Right to");   // Text line 0 on screen
  displayCenteredTextLine(1, "Set Minute");      // Text line 1
  displayCenteredTextLine(3, "Enter sets hour"); // Text line 2
  displayTime();
  while (true)    // Repeat a block of code many times
  {
    //
    // Loop until the 'enter' key is pushed.
    //
    if (nNxtButtonPressed == kLeftButton)
    {
      if (minute < 59)
        ++minute; // "++" will increment the minute variable by '1'
      else
        minute = 0;
      displayTime();
    }
    else if (nNxtButtonPressed == kRightButton)
    {
      if (minute > 0)
        --minute; // decrease minute by one
      else
        minute = 59;
      displayTime();

    }
    wait1Msec(250);
    if (nNxtButtonPressed == kEnterButton)
      break; // exit or "break out" of the loop
  }
  //
  // Wait for the 'enter' key to be released.
  //
  while(nNxtButtonPressed == kEnterButton)
  {}

  displayCenteredTextLine(0, "Left/Right to");
  displayCenteredTextLine(1, "Set Hour");
  displayCenteredTextLine(3, "Enter runs clock");
  while (true)
  {
    if (nNxtButtonPressed == kLeftButton)
    {
      if (hour < 11)
        ++hour;
      else
        hour = 0;
      displayTime();

    }
    else if (nNxtButtonPressed == kRightButton)
    {
      if (hour > 0)
        --hour;
      else
        hour = 11;
      displayTime();
    }
    wait1Msec(250);
    if (nNxtButtonPressed == kEnterButton)
      break;
  }
  while(nNxtButtonPressed == kEnterButton)
  {}

  eraseDisplay(); // Clear the LCD screen
}

task main()
{
  setTimeBeforeStartingClock();
  runClock();
  return;
}
