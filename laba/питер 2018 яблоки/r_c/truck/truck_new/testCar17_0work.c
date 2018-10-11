#pragma config(Sensor, S1,     sLeft,    sensorEV3_GenericI2C)
#pragma config(Sensor, S2,     sIr1,           sensorEV3_IRSensor)
#pragma config(Sensor, S3,     sDis,           sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     sIr2,           sensorEV3_IRSensor)
#pragma config(Motor,  motorA,          mA,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          mB,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          mOut,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          mDoor,         tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "mindsensors-irdist.h"

int a1 = 0;
int a2 = 0;
int a3 = 0;
int a4 = 0;
int a5 = 0;
int dv;
int errDist;
int table = 0;
int GoodDist;//...
int isFarFromTheWall = 0;
int isTransporterNearLeshaAppleLoader = 0;
int appleCheckFlag = 0; //apple check: 0-no apple, 1- apple
int DISTANCE_FROM_SENSOR_sDis = 0;
int distance2CollectorCheckFlag = 0 ;
float howManyDegWeNeed2Turn = 0;

int const DISTANCE_TO_CONVEYER_MIN = 22;
int const DISTANCE_TO_LEFT_WALL_MIN = 30;
int const DISTANCE_TO_APPLE_LOADER_MIN = 5;//distance to collector min
int const DISTANCE_TO_APPLE_LOADER_MAX = 8;//distance to collector max
int const DISTANCE_TO_APPLE_MIN = 8;
int const DISTANCE_TO_THE_WALL = 15;//15 = 38-12(centre) 24 = 38 cm;
int const ENCODERS_360 = 1238;//1193;//1188;//1210;//1040;
int const TEST_LENGHT = 241;
// int const TEST_LENGHT_BIG = 0;//...

task apples();
void driveTransporter2LeshasAppleLoader();
void followLeshasAppleLoader2LetHimLoadApplesInTransporter();
void transportApples2Conveyer();
void driveTransporter2StartingPlace();
void turnRight();
void turnHelp(float degrees);
void sleepSec(int sec);
void takeError();
void goFoward();
int sort ();
int min();


//---------------------------------------------------------------------------------------------------------------------------------------------
task main()
{

		sleepSec(20);
	startTask(apples);
	table = MSDISTreadDist(sLeft);
	sleep(100);
	while (true)
	{
		displayTextLine(5, "dv=%d", SensorValue[sIr2]);
		if(isTransporterNearLeshaAppleLoader  == 0)
		{
			driveTransporter2LeshasAppleLoader();
		}
		if (appleCheckFlag ==0)
		{
			followLeshasAppleLoader2LetHimLoadApplesInTransporter();
		}
		else	//===================================================================================================================================
		{
			transportApples2Conveyer();
			driveTransporter2StartingPlace();
			turnRight();
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------
int getDistancefront ()
{
	//semaphoreLock( lock );
	//readSensor(&muxedSensor[0]);
	//sleep(50);
	int y = SensorValue[sIr1];
	sleep(10);
	y += SensorValue[sIr1];
	sleep(10);
	y += SensorValue[sIr1];
	y=y/3;
	//if (bDoesTaskOwnSemaphore(lock)) semaphoreUnlock(lock);
	if ( y > DISTANCE_TO_APPLE_LOADER_MAX) return 1;
	if((y < DISTANCE_TO_APPLE_LOADER_MAX) && (y < DISTANCE_TO_APPLE_LOADER_MIN)) return 2;
	return 0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------
void turn ()
{
	nMotorEncoder[mB]=0;
	while(nMotorEncoder[mB]<ENCODERS_360/4)
	{
		motor[mA]=-20;
		motor[mB]=20;
		sleep(1);
	}
	motor[mA]=0;
	motor[mB]=0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
task apples()
{

	while(true)
	{

		sleep(100);
		DISTANCE_FROM_SENSOR_sDis = SensorValue[sDis]; //SensorValue[sApple];
		displayTextLine(6, "apple =%d",appleCheckFlag);
		displayTextLine(13,"dis to app =%d",DISTANCE_FROM_SENSOR_sDis);
		if (DISTANCE_FROM_SENSOR_sDis<DISTANCE_TO_APPLE_MIN)
		{
			sleepSec(2);
			DISTANCE_FROM_SENSOR_sDis = SensorValue[sDis] ;
			if (DISTANCE_FROM_SENSOR_sDis<DISTANCE_TO_APPLE_MIN) // SensorValue[sApple]
			{
				appleCheckFlag = 1; //*******
			}
			else
			{
				appleCheckFlag = 0;
			}
		}
		else
		{
			appleCheckFlag = 0;
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------
void down ()
{
	nMotorEncoder[mOut]=0;
	while (nMotorEncoder[mOut]>-550)
	{
		motor[mOut]= -50;
		sleep(10);
	}
	motor[mOut]=0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------
void up ()
{
	nMotorEncoder[mOut]=0;
	while (nMotorEncoder[mOut]<550)
	{
		motor[mOut]= 50;
		sleep(10);
	}
	motor[mOut]=0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------
void doorOp()
{
	nMotorEncoder[mDoor]=0;
	while(nMotorEncoder[mDoor]<50)
	{
		motor[mDoor]=20;
		sleep(10);
	}
	motor[mDoor]=0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------
void doorClo()
{
	nMotorEncoder[mDoor]=0;
	while(nMotorEncoder[mDoor]>-50)
	{
		motor[mDoor]=-20;
		sleep(10);
	}
	motor[mDoor]=0;
}

void sleepSec(int sec)
{
	for (int i = 0; i < sec; i++)
	{
		sleep(1000);
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------
void driveTransporter2LeshasAppleLoader()
{
	distance2CollectorCheckFlag= getDistancefront();
	while(distance2CollectorCheckFlag== 1)
	{
		motor[mA]=20;
		motor[mB]=20;
		distance2CollectorCheckFlag= getDistancefront();
	}
	motor[mA]=0;
	motor[mB]=0;
	isTransporterNearLeshaAppleLoader = 1;
}
//--------------------------------------------------------------------------------------------------------------------------------
void followLeshasAppleLoader2LetHimLoadApplesInTransporter()
{
	distance2CollectorCheckFlag= getDistancefront();
	if(distance2CollectorCheckFlag!= 2)
	{

		motor[mA]=20 * distance2CollectorCheckFlag;
		motor[mB]=20 * distance2CollectorCheckFlag;
	}
	else
	{
		motor[mB]= -20;
		motor[mA]= -20;
	}
}
//------------------------------------------------------
void loadApples2ConveyerAppleLoader()
{
	doorOp();
	down();
	sleep(500);
	sleepSec(5);
	sleep(500);
	up();
	doorClo();
}
//-----------------------------------------------------
void transportApples2Conveyer()
{
	int backCount = 0 ;
	sleep(50);
	while (backCount < 2)
	{
		if (SensorValue[sIr2] < DISTANCE_TO_LEFT_WALL_MIN)
			backCount++;
		else
			backCount =0;
		motor[mB]=-20;
		motor[mA]=-20;
	}
	motor[mB]=0;
	motor[mA]=0;
	playSound(soundBeepBeep);
	sleep(50);
	turn();
	backCount =0;

	while (backCount < 2)
	{
		if (SensorValue[sIr2] < DISTANCE_TO_CONVEYER_MIN)
			backCount++;
		else
			backCount =0;
		motor[mB]=-20;
		motor[mA]=-20;
	}
	sleep(50);
	playSound(soundBeepBeep);
	motor[mB]=0;
	motor[mA]=0;
	//sleepSec(5);

	motor[mB]=0;
	motor[mA]=0;
	loadApples2ConveyerAppleLoader();
	isTransporterNearLeshaAppleLoader = 0;
}
//-------------------------------------------------------------------------------------
int getDistanceFrontWhenWeDriveToTheWall()
{
	int y = SensorValue[sIr1];
	sleep(10);
	y += SensorValue[sIr1];
	sleep(10);
	y += SensorValue[sIr1];
	y=y/3;
	if ( y > DISTANCE_TO_THE_WALL) return 1;
	return 0;
}
//--------------------------------------------------------------------------------------------------------------------
void driveTransporter2StartingPlace()
{
	GoodDist= MSDISTreadDist(sLeft);
	sleep(100);
	goFoward();
	takeError();
	howManyDegWeNeed2Turn = radiansToDegrees( atan2(errDist, TEST_LENGHT));
	turnHelp(howManyDegWeNeed2Turn);
	sleep(3000);

	isFarFromTheWall = getDistanceFrontWhenWeDriveToTheWall();
	while(isFarFromTheWall == 1)
	{
		motor[mA]=20;
		motor[mB]=20;
		isFarFromTheWall = getDistanceFrontWhenWeDriveToTheWall();
	}

	motor[mA]=0;
	motor[mB]=0;
}
//-----------------------------------------------------------------------------------------------------------------------------
void turnRight()
{
	nMotorEncoder[mB]=0;
	while(nMotorEncoder[mB]>-ENCODERS_360/4)
	{
		motor[mA]=20;
		motor[mB]=-20;
		sleep(1);
	}
	motor[mA]=0;
	motor[mB]=0;
}
void goFoward()
{
	nMotorEncoder[mA] = 0;
	while (nMotorEncoder[mA]<500)//241
	{
		motor[mA]=20;
		motor[mB]=20;
	}
	motor[mA]=0;
	motor[mB]=0;
}
//-----------------------------------
void takeError()
{
	a1 = MSDISTreadDist(sLeft);
	sleep(100);
	a2 = MSDISTreadDist(sLeft);
	sleep(100);
	a3 = MSDISTreadDist(sLeft);
	sleep(100);
	a4 = MSDISTreadDist(sLeft);
	sleep(100);
	a5 = MSDISTreadDist(sLeft);
	sleep(100);
	dv = MSDISTreadDist(sLeft);
	errDist = abs(sort()-GoodDist);
}
//-----------------------------------
void turnHelp(float degrees)
{
	float encoders = ENCODERS_360/360*degrees*-1;
	displayTextLine(0,"e = %d", encoders);
	nMotorEncoder[mA] = 0;
	if (GoodDist-dv>=0)
	{
		while (nMotorEncoder[mA] < encoders*-1)
		{
			motor[mA]=20;
			motor[mB]=-20;
		}
		motor[mA]=0;
		motor[mB]=0;
	}
	else
	{
		while (nMotorEncoder[mA]>encoders)
		{
			motor[mA]=-20;
			motor[mB]=20;
		}
	}
	motor[mA]=0;
	motor[mB]=0;
}
//--------------------------------------------------------
int sort ()
{
	int b1,b2,b3;
	b1 = min();
	sleep(100);
	b2 = min();
	sleep(100);
	b3 = min();
	return b3;
	displayTextLine(1, "%d", b3);
}
//----------------------------------------------------------
int min()
{
	int index = 1;
	int minimum = a1;
	//+++++
	if (minimum > a2)
	{
		index = 2;
		minimum = a2;
	}
	//****
	if (minimum > a3)
	{
		index = 3;
		minimum = a3;
	}
	//****
	if (minimum > a4)
	{
		index = 4;
		minimum = a4;
	}
	//****
	if (minimum > a5)
	{
		index = 5;
		minimum = a5;
	}
	//+++++++++++++++++++++++++++++++++++++
	if (index == 1)a1 = 10000;
	//****
	if (index == 2)a2 = 10000;
	//****
	if (index == 3)a3 = 10000;
	//****
	if (index == 4)a4 = 10000;
	//****
	if (index == 5)a5 = 10000;

	return minimum;
}
