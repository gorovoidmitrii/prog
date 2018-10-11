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
int const SORTER_DOOR_SPEED = -30;
int const SORTER_DOOR_MOTOR_ANGLE = -68;//-53;
int const DISTANCE_TO_COURIER = 20;
int const DISTANCE_TO_TRANSPORTER = 20;
float const DISTANCE_WITHOUT_APPLE = 22.5//21.5;//25
float const MAX_DISTANCE_2_BIG_APPLE = 20.5;//21.5
int const MIN_RED_VALUE_FOR_RED_COLOUR = 10;//18;
int const MAX_GREEN_VALUE_FOR_RED_COLOUR = 11;//13;
int const MAX_RED_VALUE_FOR_GREEN_COLOUR = 25;//18;
int const MIN_GREEN_VALUE_FOR_GREEN_COLOUR = 20;//13;
int const UNDEFIND = 2;
int const GREEN = 0;
int const RED = 1;
int const SMALL = 0;
int const BIG = 1;
int const APPLE_LOADER_HEIGHT = -500;//-450;//-400// -350; //in encoders
int const WAIT_BEFORE_CLOSING_DOOR_TO_CONVEYER = 1000; //2000
// The SMUX can have up to 3 sensors attached to it.
tMSEV3 muxedSensor[1];
tEV3SensorTypeMode typeMode[1] = {infraRedProximity};
int appleColorNow = GREEN;
int appleSizeNow = SMALL;
int isAppleLoaderLoading = 0;
long lastAppleNearConveyerTime = 0;
long redValue;
long greenValue;
long blueValue;
bool isAppleReady4Conveyer = 0;
bool isCourierHere = 0;
bool isAppleLoaderUp = 0;
bool isTransporterHere = 0;
bool determineByColor = 1;
float currentDistance2Apple = 0;

task Conveyer();
task checkShouldPutLoaderDown();
task checkCouriers();
//task colour();
task isAppleNearConveyer();
task checkTrasportrerHere();
void putAppleLoaderUpIfTransporterWasHere();
void sortAppleBasedOnSize();
void appToConBig();
void appToConBackBig();
void openSmallApplesSorterDoor();
void closeSmallApplesSorterDoor();
int getSize();
int getColour();


//---------------------------------------------------------------------------------------------------------------------------------------------
task main()
{
	initSensor(&muxedSensor[0], msensor_S1_1, typeMode[0]);
	startTask(checkShouldPutLoaderDown);
	startTask(checkCouriers);
	//startTask(colour);
	startTask(isAppleNearConveyer);
	startTask(checkTrasportrerHere);
	while(true)
	{
		displayTextLine(4,"S = %d",appleSizeNow);
		displayTextLine(5,"C = %d",appleColorNow);
		putAppleLoaderUpIfTransporterWasHere();
		if (isAppleLoaderUp)
		{
			if(isCourierHere)
			{
				if (determineByColor == 0)
				{
					sortAppleBasedOnSize();
					sleep(1);
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
								if(!(appleColorNow == UNDEFIND))
								{
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
										openSmallApplesSorterDoor();
										sleep(7000);
										closeSmallApplesSorterDoor();

									}
								}
								playSound(soundException);
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
	}
}
	//*********************************************************************************************************************************************
	task Conveyer()
	{
		while (true)
		{
			if (isCourierHere == 1)
			{
				motor[mCon]= 20;
			}
			else
			{
				motor[mCon]= 0;
			}
		}
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	void openSmallApplesSorterDoor()
	{
		nMotorEncoder[mSort]=0;
		while (nMotorEncoder[mSort] > SORTER_DOOR_MOTOR_ANGLE)
		{
			motor[mSort]=SORTER_DOOR_SPEED;
		}
		motor[mSort]=0;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	void closeSmallApplesSorterDoor()
	{
		nMotorEncoder[mSort]=0;
		while (nMotorEncoder[mSort] < SORTER_DOOR_MOTOR_ANGLE*-1)
		{
			motor[mSort]=SORTER_DOOR_SPEED*-1;
		}
		motor[mSort]=0;
	}
	//-----------------------------------------------------------
	void putAppleLoaderDown()
	{
		nMotorEncoder[mDoor] = 0;
		while (nMotorEncoder[mDoor]< APPLE_LOADER_HEIGHT*-1)//-350)//body up
		{
			motor[mDoor]=15;
		}
		isAppleLoaderUp = 0;
		motor[mDoor]=0;
		isAppleLoaderLoading = 0;
	}
	//-----------------------------------------------------------
	task checkShouldPutLoaderDown()
	{
		while(true)
		{
			if (isAppleLoaderUp && (!isAppleReady4Conveyer) && (!isTransporterHere))
			{

				if ((nSysTime - lastAppleNearConveyerTime) > 10000 )putAppleLoaderDown();
			}
			sleep(500);
		}
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
			//if (SensorValue[sApple]>-255)
			//{
			currentDistance2Apple = SensorValue[sApple];
			if (currentDistance2Apple < DISTANCE_WITHOUT_APPLE)
			{
				isAppleReady4Conveyer = 1;
				lastAppleNearConveyerTime = nSysTime;
			}
			else
			{
				isAppleReady4Conveyer = 0;
			}
			//}
			/*else
			{
			isAppleReady4Conveyer = 0;
			}*/
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
	//---------------------------------------------------------------------------------------------------------------------------------------------
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
	//---------------------------------------------------------------------------------------------------------------------------------------------
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
		displayTextLine(6, "%f", redValue);
		displayTextLine(7, "%f", greenValue);
		displayTextLine(8, "%f", blueValue);
		int col = GREEN;
		if ((redValue >= MIN_RED_VALUE_FOR_RED_COLOUR)&&(greenValue <= MAX_GREEN_VALUE_FOR_RED_COLOUR))
		{
			col = RED;
		}
		else if ((redValue < MAX_RED_VALUE_FOR_GREEN_COLOUR)&&(greenValue > MIN_GREEN_VALUE_FOR_GREEN_COLOUR))
		{
			col = GREEN;
		}
		else
		{
			col = UNDEFIND;
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
		sleep(1000);
		openSmallApplesSorterDoor();
		sleep(4000);
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
	void putAppleLoaderUpIfTransporterWasHere()
	{
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
				lastAppleNearConveyerTime = nSysTime;
				isAppleLoaderUp = 1;
				motor[mDoor]=0;
				isAppleLoaderLoading = 1;
				startTask(Conveyer);
			}
		}
	}
	void sortAppleBasedOnSize()
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
					sleep(1000);
					if (appleSizeNow == SMALL)
					{
						moveAppleToBascet();
					}
				}
			}
		}
	}
	/*task colour()
	{
	getColorRGB(sColour, redValue, greenValue, blueValue);
	setSensorMode(sColour,modeEV3Color_Color);
	while(true)
	{
	getColorRGB(sColour, redValue, greenValue, blueValue);
	displayTextLine(6, "%f", redValue);
	displayTextLine(7, "%f", greenValue);
	displayTextLine(8, "%f", blueValue);
	sleep(100);
	}
	}
	*/
