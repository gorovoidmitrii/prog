#pragma config(Sensor, S1,     sIr1,           sensorEV3_IRSensor, modeEV3IR_Seeker)
#pragma config(Sensor, S2,     sDis,           sensorEV3_GenericI2C)
#pragma config(Sensor, S3,     sApple,         sensorSONAR)
#pragma config(Sensor, S4,     sIr2,           sensorEV3_IRSensor, modeEV3IR_Seeker)
#pragma config(Motor,  motorA,          mA,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          mB,            tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma config(Motor,  motorC,          mOut,          tmotorEV3_Large, PIDControl, encoder)
//#pragma config(Motor,  motorD,          mDoor,         tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "mindsensors-ev3smux.h"
tMSEV3 muxedSensor[2];
tEV3SensorTypeMode typeMode[1] = {infraRedProximity};
int e = 0;
int u = 0;
int const k1 = -1;
int it = 0;
int const distocon = 20;
int apple = 0; //apple check: 0-no apple, 1- apple
//int disS = 0;
int disS2 = 0;
int n = 0;//distance check flag: 0- stop, 1 - go, 2 - go back
int const v1 = 50; // speed main
//int	const v2 = 30; // speed slow
int const dis2 = 10 ;//distance to collector min
int const dis1 = 20;//distance to collector max
int const disA = 10;
float const k = 0.35;//slow speed value

int getDistancefront ()
{
	displayTextLine(12, "n=%d", n);
	readSensor(&muxedSensor[0]);
	sleep(50);
	int y = muxedSensor[0].distance;
	int n = 0;
	if(y<dis1)
	{
		if (y<dis2)
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

		n = 1;
	}
	return n;
}

task apples()
{

	while(true)
	{
		disS2 = SensorValue[sApple];
		displayTextLine(6, "apple =%d",apple);
		displayTextLine(7,"dis to app =%d",disS2);
		if (SensorValue[sApple]<disA)
		{
			sleep(2000);
			if (SensorValue[sApple]<disA)
			{
				apple = 1;
			}
		}
		else
		{
			apple = 0;
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------
task main()
{
	startTask(apples);
	initSensor(&muxedSensor[0], msensor_S2_1, typeMode[0]);
	sleep(100);
	initSensor(&muxedSensor[1], msensor_S2_2, typeMode[0]);

	while (true)
	{
		readSensor(&muxedSensor[0]);
		sleep(50);
		readSensor(&muxedSensor[1]);
		sleep(50);
		//if (apple ==0)
		//{
		if(getDistancefront()!=2)
		{
			e =	getIRBeaconChannelDirection(sIr1, 0);
			u = 6*e;
			displayTextLine(4, "e = %d",e);
			displayTextLine(5, " distance = %d",muxedSensor[0].distance);
			motor[mB]= (v1-u)/**n*/*k;
			motor[mA]= (v1+u)/**n*/*k;
			sleep(50);
			readSensor(&muxedSensor[0]);
		}
		else
		{
			motor[mB]= -20;
			motor[mA]= -20;
		}
		//}
		/*else
		{
		sleep(50);
		readSensor(&muxedSensor[1]);
		while (muxedSensor[1].distance > distocon)
		{
		e =	getIRBeaconChannelDirection(sIr2, 1);
		u = 6*e;
		displayTextLine(4, ":%d", e);
		motor[mA]= k1*(v1-u)*k;
		motor[mB]= k1*(v1+u)*k;
		sleep(100);
		readSensor(&muxedSensor[1]);
		}
		sleep(50);
		}*/
	}
}
