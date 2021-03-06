#pragma config(Sensor, S1,     sIr1,            sensorEV3_IRSensor, modeEV3IR_Seeker)
#pragma config(Sensor, S2,     sDis,           sensorNone)
#pragma config(Sensor, S4,     sIr2,           sensorEV3_IRSensor, modeEV3IR_Seeker)
#pragma config(Motor,  motorA,          mA,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          mB,            tmotorEV3_Large, PIDControl, encoder)
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
/*int o = 0;
task t ()
{
while (true)
{
o = o+1
sleep(500);
displayTextLine(5,"o=: %d", o);
}
}*/
task main()
{
	initSensor(&muxedSensor[0], msensor_S2_1, typeMode[0]);
	initSensor(&muxedSensor[1], msensor_S2_2, typeMode[0]);
	readSensor(&muxedSensor[0]);
	while (muxedSensor[0].distance > 10)
	{
		e =	getIRBeaconChannelDirection(sIr2, 1);
		u = 6*e;
		displayTextLine(4, "%d",e);
		displayTextLine(5, "%d",muxedSensor[0].distance);
		motor[mB]= -1 * (v1-u)*k;
		motor[mA]= -1 * (v1+u)*k;
		sleep(100);
		readSensor(&muxedSensor[0]);
	}
	readSensor(&muxedSensor[1]);
	while (muxedSensor[1].distance >10)
	{

		e =	getIRBeaconChannelDirection(sIr1, 0);
		u = 6*e;
		displayTextLine(4, ":%d", e);

		motor[mA]= (v1-u)*k;
		motor[mB]= (v1+u)*k;
		sleep(10);
		readSensor(&muxedSensor[1]);
	}
}
