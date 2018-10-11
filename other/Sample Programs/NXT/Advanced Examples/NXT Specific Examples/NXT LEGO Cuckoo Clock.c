////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Program for LEGO Cuckoo Clock
//
// LEGO has provided a nice model of a working Cuckoo clock built with LEGO parts. It includes  a bird that "tweets"
// on the hour. The building instruction are on the LEGO web page along with a program in the NXT-G graphical
// programming language.
//
// This program written in ROBOTC, provides the same program logic as the LEGO supplied NXT-G program. It's a lot
// easier to understand than the NXT-G program.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

byte _seconds = 0;
byte _minutes = 0;
byte _hours   = 0;

void setTimeBeforeStartingClock();

task displayTimeOnLCD();
task playCuckooOnTheHour();
task moveSecondHand();

const int kMotorCountsPerMinute = 360;
bool bDisplaySeconds = true;

task main()
{
  nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg;
  nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg;

  nNxtButtonTask = -2;
  bDisplaySeconds = false;
  startTask(displayTimeOnLCD);
  setTimeBeforeStartingClock();
  bDisplaySeconds = true;
  while (true)
  {
    wait1Msec(1000);
    _seconds += 1;
    if ((_seconds % 15) == 0)
      startTask(moveSecondHand);
    if (_seconds >= 60)
    {
      _seconds = 0;
      _minutes += 1;
      if (_minutes >= 60)
      {
        _minutes = 0;
        startTask(playCuckooOnTheHour);
        _hours += 1;
        if (_hours >= 12)
          _hours = 0;
      }
    }
  }
}

void keyClick()
{
  playSoundFile("! Click.rso");
}

//
// Use right / left / enter keys to adjust _minutes and _hours
//
void setTimeBeforeStartingClock()
{
  displayCenteredTextLine(0, "Left/Right to");
  displayCenteredTextLine(1, "Set Minutes");
  displayCenteredTextLine(3, "Enter sets _hours");
  while (true)
  {
    if (nNxtButtonPressed == kLeftButton)
    {
      keyClick();
      if (_minutes < 59)
        ++_minutes;
      else
        _minutes = 0;
    }
    else if (nNxtButtonPressed == kRightButton)
    {
      keyClick();
      if (_minutes > 0)
        --_minutes;
      else
        _minutes = 59;
    }
    wait1Msec(250);
    if (nNxtButtonPressed == kEnterButton)
    {
      keyClick();
      break;
    }
  }
  while(nNxtButtonPressed == kEnterButton)
  {}

  displayCenteredTextLine(0, "Left/Right to");
  displayCenteredTextLine(1, "Set Hours");
  displayCenteredTextLine(3, "Enter runs clock");
  while (true)
  {
    if (nNxtButtonPressed == kLeftButton)
    {
      keyClick();
      if (_hours < 11)
        ++_hours;
      else
        _hours = 0;
    }
    else if (nNxtButtonPressed == kRightButton)
    {
      keyClick();
      if (_hours > 0)
        --_hours;
      else
        _hours = 11;
    }
    wait1Msec(250);
    if (nNxtButtonPressed == kEnterButton)
    {
      keyClick();
      break;
    }
  }
  while(nNxtButtonPressed == kEnterButton)
  {}

  eraseDisplay();
  nMotorEncoderTarget[motorC] = ((_hours % 12) * 60 + _minutes) * (long) kMotorCountsPerMinute;
  motor[motorC] = 100;
}

task displayTimeOnLCD()
{
  //
  // Refresh clock display every 100 msec.
  //
  string sTime;
  int nBlinker;
  int nLastSecond;


  while (true)
  {
    stringFormat(sTime, "%2d:%02d", (short) _hours, (short) _minutes);
    if (bDisplaySeconds)
    {
      string sTemp;

      if (_seconds != nLastSecond)
      {
        nLastSecond = _seconds;
        nBlinker = 0;
      }
      else
        ++nBlinker;

      if (nBlinker > 5)
        stringFormat(sTemp, "%s %02d", sTime, (short) _seconds);
      else
        stringFormat(sTemp, "%s:%02d", sTime, (short) _seconds);
      sTime = sTemp;
      displayBigStringAt(2, 20, "%s", sTime);
    }
    else
      displayBigStringAt(20, 20, "%s", sTime);
    wait1Msec(100);
  }
}

task moveSecondHand()
{
  nMotorEncoderTarget[motorC] = kMotorCountsPerMinute / 4;
  motor[motorC] = 100;
  while (nMotorRunState[motorC] != runStateIdle)
  {
    wait1Msec(1);
  }
}

task playCuckooOnTheHour()
{
  int nCounts;
  const int kCuckooMoveCounts = 562;

  for (nCounts = (_hours + 1) % 12; nCounts > 0; --nCounts)
  {
    nMotorEncoderTarget[motorA] = kCuckooMoveCounts;
    motor[motorA] = 100;
    while (nMotorRunState[motorA] != runStateIdle)
    {}
    playSoundFile("!Applause.rso");
    nMotorEncoderTarget[motorA] = kCuckooMoveCounts;
    motor[motorA] = -100;
    while (nMotorRunState[motorA] != runStateIdle)
    {}
  }
}
