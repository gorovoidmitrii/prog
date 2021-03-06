#pragma config(Sensor, S1,     sIr,            sensorEV3_IRSensor, modeEV3IR_Seeker)
#pragma config(Sensor, S2,     sDis,           sensorEV3_GenericI2C)
#pragma config(Sensor, S3,     sApple,         sensorNone)
#pragma config(Sensor, S4,     sIr2,           sensorEV3_IRSensor, modeEV3IR_Seeker)
#pragma config(Motor,  motorA,          mA,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          mB,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          mOut,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          mDoor,         tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "mindsensors-ev3smux.h"
int e = 0;
int u = 0;
int const k1 = -1;
int it = 0;
int const distocon = 10;
int apple = 0; //apple check: 0-no apple, 1- apple
//int disS = 0;
int disS2 = 0;
int n = 0;//distance check flag: 0- stop, 1 - go, 2 - go back
int const v1 = 50; // speed main
//int	const v2 = 30; // speed slow
int const dis2 = 10 ;//distance to collector min
int const dis1 = 20;//distance to collector max
int const disA = 10;
float const k = 0.3;//slow speed value
tMSEV3 muxedSensor[2];
tEV3SensorTypeMode typeMode[1] = {infraRedProximity};




task distance()
{
	while (true)
	{
		readSensor(&muxedSensor[0]);
		displayTextLine(5,"%d",muxedSensor[0].distance);
		if(muxedSensor[0].distance<dis1)
		{
			if (muxedSensor[0].distance<dis2)
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
		sleep(10);
	}
}

task apples()
{

	while(true)
	{
		disS2 = SensorValue[sApple];
		displayTextLine(6,"%d",apple);
		displayTextLine(7,"%d",disS2);
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
	//initSensor(&muxedSensor[0], msensor_S2_1, typeMode[0]);
	//initSensor(&muxedSensor[1], msensor_S2_2, typeMode[0]);
	//startTask(distance);
	//startTask(apples);
	while (true)
	{

		//if ( apple == 0)
		//{
		/*if ( n != 2 )
		{




			/*e =	getIRBeaconChannelDirection(sIr, 0);
			u = 6*e;
			displayTextLine(4, "%d",e);
			motor[mB]= (v1-u)*n*k;
			motor[mA]= (v1+u)*n*k;
			sleep(1);


		/*else
		{// distance too short - go back
			motor[mB]=0;
			motor[mA]=0;
			sleep(1);
			nMotorEncoder[mB]=0;
			motor[mB]=-20;
			motor[mA]=-20;
			sleep(1);

		}
		//}
		/*else
		{
		*/
		motor[mB]=0;
		motor[mA]=0;
		sleep(1);
		readSensor(&muxedSensor[1]);
		while (/*muxedSensor[1].distance>distocon*/true)
		{

			e =	getIRBeaconChannelDirection(sIr2, 1);
			u = 6*e;
			displayTextLine(4, "%d",e);

			motor[mB]= -1 * (v1-u)*k;
			motor[mA]= -1 * (v1+u)*k;
			sleep(10);
			//readSensor(&muxedSensor[0]);
		}

		motor[mB]=0;
		motor[mA]=0;
		while (nMotorEncoder[mOut]<45)
		{
			motor[mOut]= 100;

			sleep(1);
		}
		motor[mOut]=0;
		///////////////////////////////////////////////////////////////////////////////
		nMotorEncoder[mDoor]=0;
		while(it < 3)
		{
			nMotorEncoder[mDoor]=0;
			while(nMotorEncoder[mDoor]<50)
			{
				motor[mDoor]=20;
				sleep(1);
			}
			motor[mDoor]=0;
			sleep(100);

			nMotorEncoder[mDoor]=0;
			while(nMotorEncoder[mDoor]>-50)
			{
				motor[mDoor]=-20;
				sleep(1);
			}
			it ++;
			motor[mDoor]=0;
			sleep(4000);
		}
		it = 0;
		//////////////////////////////////////////////////////////////////////////////////////
		nMotorEncoder[mOut]=0;
		while (nMotorEncoder[mOut]>-45)
		{
			motor[mOut]= -100;

			sleep(1);
		}
		motor[mOut]=0;
	}
}
//}
