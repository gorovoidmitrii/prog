#pragma config(Sensor, S1,     sM_cour,        sensorEV3_GenericI2C)
#pragma config(Sensor, S2,     sTrans,         sensorSONAR)
#pragma config(Sensor, S3,     sApple,         sensorEV3_IRSensor)
#pragma config(Sensor, S4,     sColour,        sensorEV3_Color)
#pragma config(Motor,  motorA,          mPush,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mSort,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mDoor,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorD,          mCon,          tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "mindsensors-ev3smux.h"


// The SMUX can have up to 3 sensors attached to it.
tMSEV3 muxedSensor[1];
tEV3SensorTypeMode typeMode[1] = {infraRedProximity};
// int color = 0;

int flagT = 0;//0-no transporter, 1- transporter arrived conv start
int colOrDis = 1;//dis=0,col=1
long greenValue;
long blueValue;
long redValue;
float const disA2 = 23.5;//min dis to big apple
//int const min_for_green=8; //max for red 7, min for green 12 -green value
int colorflag = 0;// green =1, red = 0
int const disA = 27;//distance without apple
float disValue = 0;//value from sensor to check that apple appear near RGB
int disflag = 0;//0- no apple near RGB, 1 - apple arrived
int cour = 0;//0- 1 or 2 courier go out, 1- both couriers stands
int const courdis = 20;//dis to courier
int const transdis = 20;//dist no transporter
task Con()
{
	while (true)
	{
		if (cour == 1)
		{
			motor[mCon]= 20; //run conveer
		}
		else
		{
			motor[mCon]= 0;
		}
	}
}

task colour()
{
	getColorRGB(sColour, redValue, greenValue, blueValue);
	setSensorMode(sColour,modeEV3Color_Color);
	while(true)
	{
		getColorRGB(sColour, redValue, greenValue, blueValue);
		displayTextLine(4, "%f", redValue);
		displayTextLine(5, "%f", greenValue);
		displayTextLine(6, "%f", blueValue);
		sleep(100);
	}
}
void door2_open() //red or green
{
	nMotorEncoder[mSort]=0;
	while (nMotorEncoder[mSort] > -53)
	{
		motor[mSort]=-30;
	}
	motor[mSort]=0;
}

void door2_close()
{
	nMotorEncoder[mSort]=0;
	while (nMotorEncoder[mSort] < 53)
	{
		motor[mSort]=30;
	}
	motor[mSort]=0;
}
/*void door_open()
{
while (nMotorEncoder[mDoor] < 100)
{
motor[mDoor]=30;

}
motor[mDoor]=0 ;
nMotorEncoder[mDoor]=0;

}
void door_close()
{
nMotorEncoder[mDoor]=0;
while (nMotorEncoder[mDoor] > -100)
{
motor[mDoor]=-30;

}
motor[mDoor]=0 ;
nMotorEncoder[mDoor]=0;
}
*/
task dis_col() //check apple near RGB
{
	while(true)
	{
		//readSensor(&muxedSensor[1]);
		disValue = SensorValue[sApple];
		displayTextLine(9,"dv = %d",disValue);
		displayTextLine(10," df = %d",disflag);
		if (SensorValue[sApple]>-255)
		{
			if (disValue < disA)
			{
				disflag = 1;
			}
			else
			{
				disflag = 0;
			}
		}
		else
		{
			disflag = 0;
		}
		sleep(100);
	}
}
task trans()//check trasportrer near
{
	while(true)
	{
		int a = 0;
		a = SensorValue[sTrans];
		displayTextLine(13, "a = %d", a);
		displayTextLine(0,"ft= %d",flagT);
		if (SensorValue[sTrans] <transdis)
		{
			sleep(1000);
			if (SensorValue[sTrans]<transdis)
			{
				flagT = 1;
			}
			else
			{
				flagT = 0;
			}
		}
		else
		{
			flagT = 0;
		}
	}
}
task cours()//check courier is near
{
	while(true)
	{

		readSensor(&muxedSensor[0]);
		//		readSensor(&muxedSensor[1]);
		displayTextLine(12, "Distance: %d", muxedSensor[0].distance);
		//	displayTextLine(13, "Distance: %d", muxedSensor[1].distance);
		sleep(200);
		if (muxedSensor[0].distance >courdis)
		{
			cour = 0;
		}
		else
		{
			cour = 1;
		}

	}
}
void appToConBack()//close pusher
{
	//displayTextLine(1,"p = %d", nMotorEncoder[mPush])
	nMotorEncoder[mPush]=0;
	while ( nMotorEncoder[mPush]<370)
	{
		motor[mPush]=50;
		sleep(1);
	}
	motor[mPush]=0;
}
void appToCon()//open pusher
{
	nMotorEncoder[mPush]=0;
	while ( nMotorEncoder[mPush]>-370)
	{
		//displayTextLine(1,"p = %d", nMotorEncoder[mPush])
		motor[mPush]=-50;
		sleep(1);
	}
	motor[mPush]=0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------
task main()
{
	//initSensor(&muxedSensor[1], msensor_S1_2, typeMode[0]);
	initSensor(&muxedSensor[0], msensor_S1_1, typeMode[0]);

	startTask(cours);
	startTask(colour);
	startTask(dis_col);
	int r = 0;//variable for check is body open or no
	startTask(trans);
	while(true)
	{
		if(flagT == 1)
		{
			while (flagT == 1)//is there transporter or no
			{
				sleep(100);
			}
			nMotorEncoder[mDoor]=0;
			while (nMotorEncoder[mDoor]>-215)//body up
			{
				motor[mDoor]=-15;
			}
			motor[mDoor]=0;
			r = 1;
			startTask(Con);
		}
		if (colOrDis == 0)
		{
			if (r == 1)
			{
				if(disflag==1)
				{

					if (SensorValue[sApple] < disA2) //if apple is big
					{
						appToConBack();
						sleep(2000);
						appToCon();
						colorflag = 0;
						//door_open();
						//sleep(4000);
						//door_close();
					}
					else
					{
						sleep(3000);
						if (SensorValue[sApple] > disA2)
						{
							appToConBack();
							sleep(2000);
							appToCon();

							colorflag=1;
							door2_open();
							//door_open();
							//sleep(4000);
							//door_close();
							sleep(7000);
							door2_close();
						}
					}
				}
				displayTextLine(8, "%d",colorflag);
				sleep(1);
			}
		}
		else // comparing by COLOUR
		{
			if(disflag==1) // apple exist
			{
				if (SensorValue[sApple] < disA2) // apple is big
				{
					playSound(soundDownwardTones);
					sleep(1000);
					//playSound(soundDownwardTones);
					if(redValue>13) // apple is red
					{
						playSound(soundDownwardTones);
						appToConBack();
						sleep(2000);
						appToCon();
						colorflag = 0;
					}
					else
					{
						appToConBack();
						sleep(2000);
						appToCon();
						colorflag = 0;
						door2_open();
						sleep(7000);
						door2_close();

					}
				}
				else // apple is small (and so it is red)
				{
					sleep(3000);
					if (SensorValue[sApple]>disA2)//double check that apple is really small
					{
						playSound(soundBeepBeep);
						appToConBack();
						sleep(2000);
						appToCon();

					}

				}
			}
		}
	}
}
