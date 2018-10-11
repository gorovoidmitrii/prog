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

int const DISTANCE_TO_COURIER = 20;
int const DISTANCE_TO_TRANSPORTER = 20;
int const DISTANCE_WITHOUT_APPLE = 25;
int const MAX_DISTANCE_2_BIG_APPLE = 21;
int const GREEN = 0;
int const RED = 1;
int const SMALL = 0;
int const BIG = 1;
int const APPLE_LOADER_HEIGHT = -450;//-400// -350; //in encoders
int const WAIT_BEFORE_CLOSING_DOOR_TO_CONVEYER = 1000; //2000
// The SMUX can have up to 3 sensors attached to it.
tMSEV3 muxedSensor[1];
tEV3SensorTypeMode typeMode[1] = {infraRedProximity};
// int color = 0;
int appleColorNow = GREEN;
int appleSizeNow = SMALL;
int isAppleLoaderLoading = 0;
bool isAppleReady4Conveyer = 0;//0- no apple near RGB, 1 - apple arrived
bool isCourierHere = 0;
bool isAppleLoaderUp = 0;
bool isTransporterHere = 0;
bool determineByColor = 0;
float currentDistance2Apple = 0;//value from sensor to check that apple appear near RGB
//********************************************************************************************************************************************
task Conveyer()
{
	while (true)
	{
		if (isCourierHere == 1)
		{
			motor[mCon]= 20; //run conveer
		}
		else
		{
			motor[mCon]= 0;
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------
void openSmallApplesSorterDoor() //red or green
{
	nMotorEncoder[mSort]=0;
	while (nMotorEncoder[mSort] > -53)
	{
		motor[mSort]=-30;
	}
	motor[mSort]=0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------
void closeSmallApplesSorterDoor()
{
	nMotorEncoder[mSort]=0;
	while (nMotorEncoder[mSort] < 53)
	{
		motor[mSort]=30;
	}
	motor[mSort]=0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------
task isAppleNearConveyer() //check apple near RGB
{
	while(true)
	{
		//readSensor(&muxedSensor[1]);
		currentDistance2Apple = SensorValue[sApple];
		displayTextLine(9,"dv = %d",currentDistance2Apple);
		displayTextLine(10," df = %d",isAppleReady4Conveyer);
		if (SensorValue[sApple]>-255)
		{
			if (currentDistance2Apple < DISTANCE_WITHOUT_APPLE)
			{
				isAppleReady4Conveyer = 1;
			}
			else
			{
				isAppleReady4Conveyer = 0;
			}
		}
		else
		{
			isAppleReady4Conveyer = 0;
		}
		sleep(100);
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------
task checkTrasportrerHere()//check trasportrer near
{
	while(true)
	{
		int a = 0;
		a = SensorValue[sTrans];
		displayTextLine(13, "a = %d", a);
		displayTextLine(0,"ft= %d",isTransporterHere);
		if (SensorValue[sTrans] <DISTANCE_TO_TRANSPORTER)
		{
			sleep(1000);
			if (SensorValue[sTrans]<DISTANCE_TO_TRANSPORTER)
			{
				isTransporterHere = 1;
			}
			else
			{
				isTransporterHere = 0;
			}
		}
		else
		{
			isTransporterHere = 0;
		}
	}
}
int getSize()
{
	int a1 = SensorValue[sApple];
	sleep(1000);
	int a2 = SensorValue[sApple];
	sleep(1000);
	int a3 = SensorValue[sApple];
	float dist =(a1+a2+a3)/3;
	int appleSize = 0;
	if (dist < MAX_DISTANCE_2_BIG_APPLE)
	{
		appleSize = BIG;
	}
	else
	{
		appleSize = SMALL;
	}
	return appleSize;
}
int getColour()
{
	long greenValue1;
	long blueValue1;
	long redValue1;
	long greenValue2;
	long blueValue2;
	long redValue2;
	long greenValue3;
	long blueValue3;
	long redValue3;
	getColorRGB(sColour, redValue1, greenValue1, blueValue1);
	sleep(1000);
	getColorRGB(sColour, redValue2, greenValue2, blueValue2);
	sleep(1000);
	getColorRGB(sColour, redValue3, greenValue3, blueValue3);
	float redValue = (redValue1+redValue2+redValue3)/3;
	float greenValue = (greenValue1+greenValue2+greenValue3)/3;
	float blueValue = (blueValue1+blueValue2+blueValue3)/3;
	int col = GREEN;
	if ((redValue > 5)&&(greenValue<5 ))//****
	{
		col = RED;
	}
	else
	{
		col = GREEN;
	}
	return col;
}
task checkCouriers()//check courier is near
{
	while(true)
	{

		readSensor(&muxedSensor[0]);
		//		readSensor(&muxedSensor[1]);
		displayTextLine(12, "Distance: %d", muxedSensor[0].distance);
		//	displayTextLine(13, "Distance: %d", muxedSensor[1].distance);
		sleep(200);
		if (muxedSensor[0].distance >DISTANCE_TO_COURIER)
		{
			isCourierHere = 0;
		}
		else
		{
			isCourierHere = 1;
		}

	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------
void appToConBackBig()//close pusher
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
//---------------------------------------------------------------------------------------------------------------------------------------------
void appToConBig()//open pusher
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
void appToConBackSmall()//close pusher
{
	//displayTextLine(1,"p = %d", nMotorEncoder[mPush])
	nMotorEncoder[mPush]=0;
	while ( nMotorEncoder[mPush]<250)
	{
		motor[mPush]=50;
		sleep(1);
	}
	motor[mPush]=0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------
void appToConSmall()//open pusher
{
	nMotorEncoder[mPush]=0;
	while ( nMotorEncoder[mPush]>-250)
	{
		//displayTextLine(1,"p = %d", nMotorEncoder[mPush])
		motor[mPush]=-100;
		sleep(1);
	}
	motor[mPush]=0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------
void moveAppleToBascet()
{
	appToConBackSmall();
	sleep(WAIT_BEFORE_CLOSING_DOOR_TO_CONVEYER); //2000
	appToConSmall();
	sleep(2000);
	openSmallApplesSorterDoor();
	sleep(5000);
	closeSmallApplesSorterDoor();
}
//---------------------------------------------------------------------------------------------------------------------------------------------
void moveAppleToCourier()
{
	appToConBackBig();
	sleep(WAIT_BEFORE_CLOSING_DOOR_TO_CONVEYER);
	appToConBig();
}
//---------------------------------------------------------------------------------------------------------------------------------------------
task main()
{
	initSensor(&muxedSensor[0], msensor_S1_1, typeMode[0]);

	startTask(checkCouriers);
	startTask(isAppleNearConveyer);
	startTask(checkTrasportrerHere);
	while(true)
	{
		displayTextLine(4,"S = %d",appleSizeNow);
		displayTextLine(5,"C = %d",appleColorNow);
		if (isAppleLoaderUp == 0)
		{
		if(isTransporterHere == 1)
		{
			while (isTransporterHere == 1)//is there transporter or no
			{
				sleep(100);
			}
			nMotorEncoder[mDoor]=0;
			while (nMotorEncoder[mDoor]> APPLE_LOADER_HEIGHT)//-350)//body up
			{
				motor[mDoor]=-15;

			}
			isAppleLoaderUp = 1;
			motor[mDoor]=0;
			isAppleLoaderLoading = 1;
			startTask(Conveyer);
		}
	}
		if (determineByColor == 0)
		{
			if (isAppleLoaderLoading == 1)
			{
				if(isAppleReady4Conveyer==1)
				{
					appleSizeNow = getSize();
					if (appleSizeNow == BIG)
					{
						moveAppleToCourier();
					}
					else
					{
						sleep(3000);
						if (appleSizeNow == SMALL)
						{
							moveAppleToBascet();
						}
					}
				}
				sleep(1);
			}
		}
		else //====================================================================================================================================
		{
			if (isAppleLoaderLoading == 1)
			{
				if(isAppleReady4Conveyer==1) // apple exist
				{
					appleSizeNow = getSize();
					if (appleSizeNow == BIG) // apple is big
					{
						appleColorNow=getColour();
						playSound(soundDownwardTones);
						sleep(1000);
						//playSound(soundDownwardTones);
						if(appleColorNow == RED) // apple is red
						{
							playSound(soundDownwardTones);
							appToConBackBig();
							sleep(2000);
							appToConBig();
							//colorflag = 0;
							sleep(2000);
						}
						else
						{
							appToConBackBig();
							sleep(2000);
							appToConBig();
							//colorflag = 0;
							openSmallApplesSorterDoor();
							sleep(7000);
							closeSmallApplesSorterDoor();

						}
					}
					else // apple is small (and so it is red)
					{
						sleep(3000);
						if (appleSizeNow == SMALL)//double check that apple is really small
						{
							playSound(soundBeepBeep);
							appToConBackBig();
							sleep(2000);
							appToConBig();
							sleep(2000);
						}
					}
				}
			}
		}
	}
}
