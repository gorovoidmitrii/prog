#pragma config(Sensor, S1,     sDisBack,       sensorNone)
#pragma config(Sensor, S2,     sIr1,           sensorEV3_IRSensor)
#pragma config(Sensor, S3,     sDis,           sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     sIr2,           sensorEV3_IRSensor)
#pragma config(Motor,  motorA,          mA,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          mB,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          mOut,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          mDoor,         tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma config(Motor,  motorC,          mOut,          tmotorEV3_Large, PIDControl, encoder)
//#pragma config(Motor,  motorD,          mDoor,         tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//#//include "mindsensors-ev3smux.h"
//tMSEV3 muxedSensor[2];
//tEV3SensorTypeMode typeMode[2] = {infraRedProximity, sonarCM};
int e = 0;
int u = 0;
void sleepSec(int sec);
int const k1 = -1;
int it = 0;
int const distocon = 20;
int apple = 0; //apple check: 0-no apple, 1- apple
//int disS = 0;
int disS2 = 0;
int n = 0;//distance check flag: 0- stop, 1 - go, 2 - go back
int const v1 = 50; // speed main
//int	const v2 = 30; // speed slow
int const dis2 = 5 ;//distance to collector min
int const dis1 = 8;//distance to collector max
int const disA = 7;
float const k = 0.3;//slow speed value
//int nForOut=0;

//TSemaphore lock;
//---------------------------------------------------------------------------------------------------------------------------------------------



int getDistancefront ()
{
	//semaphoreLock( lock );
	//readSensor(&muxedSensor[0]);
	//sleep(50);
	int y = sensorValue[sIr1];
	sleep(10);
	y += sensorValue[sIr1];
	sleep(10);
	y += sensorValue[sIr1];
	y=y/3;
	//if (bDoesTaskOwnSemaphore(lock)) semaphoreUnlock(lock);
	if ( y > dis1) return 1;
	if((y < dis1) && (y < dis2)) return 2;
	return 0;
	/*
	int n = 0;
	if(y < dis1)
	{
		if (y < dis2)
		{
			n = 2;
		}
		else
		{
			n = 0;
		}
	}
	else
	{
		//playSound(soundBeepBeep);
		n = 1;
	}
	displayTextLine(12, "n=%d", n);
	return n;
	*/
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*task out()
{
while (nForOut == 0)
{
while (nMotorEncoder[mOut]>-10)
{
motor[mOut]= -10;//##

sleep(1);
}
sleep(10);
}
}
*/
//---------------------------------------------------------------------------------------------------------------------------------------------

task apples()
{

	while(true)
	{
		//semaphoreLock( lock );
		//readSensor(&muxedSensor[1]);
		sleep(100);
		disS2 = sensorValue[sdis] ; //SensorValue[sApple];
		//if (bDoesTaskOwnSemaphore(lock)) semaphoreUnlock(lock);
		displayTextLine(6, "apple =%d",apple);
		displayTextLine(13,"dis to app =%d",disS2);
		if (disS2<disA)
		{
			sleepSec(2);
			//semaphoreLock( lock );
			//readSensor(&muxedSensor[1]);
			sleep(100);
			disS2 = SensorValue[sDis] ;
			//if (bDoesTaskOwnSemaphore(lock)) semaphoreUnlock(lock);
			if (disS2<disA) // SensorValue[sApple]
			{
				apple = 1; //*******
			}
			else
			{
				apple = 0;
			}
		}
		else
		{
			apple = 0;
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
//---------------------------------------------------------------------------------------------------------------------------------------------
task main()
{

	sleepSec(20);


	startTask(apples);
	sleep(100);

	while (true)
	{
		if (apple ==0)
		{
			n = getDistancefront();
			if(n != 2)
			{

				motor[mA]=20*n;
				motor[mB]=20*n;
			}
			else
			{
				motor[mB]= -20;
				motor[mA]= -20;
			}
		}
		//=========================================================================================================================================
		else
		{
			int backCount = 0 ;
			sleep(50);
			while (backCount < 2)
			{
				if (SensorValue[sIr2] < distocon)
					backCount++;
				else
					backCount =0;
				motor[mB]=-20;
				motor[mA]=-20;
			}
			sleep(50);
			//motor[mB]=-20;
			//motor[mA]=-20;
			//sleepSec(1);


			motor[mB]=0;
			motor[mA]=0;
			down();
			//nForOut=0;
			sleep(500);
			//************
			doorOp();
			sleep(100);
			doorClo();
			sleepSec(7);
			//************
			doorOp();
			sleep(75);
			doorClo();
			sleepSec(7);
			//*************
			doorOp();
			sleep(200);
			doorClo();

			//nForOut=1;
			up();
		}
	}
}
