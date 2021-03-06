#pragma config(Sensor, S1,     sColour,        sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     sDis,           sensorSONAR)
#pragma config(Motor,  motorA,          mCon,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mSort,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mDoor,         tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int color = 0;

long redValue;
long greenValue;
long blueValue;
int const min_for_green=10 //max for red 7, min for green 12 -green value
int colorflag = 0;// green =1, red = 0
int const dis = 11;
int disS = 0;
int disflag = 0;
/*
task Con()
{
while (true)
{
motor[mCon]= 20; //run transporter
}
}
*/
task colour()
{
	getColorRGB(sColour, redValue, greenValue, blueValue);
	setSensorMode(sColour,modeEV3Color_Color);
	while(true)
	{
		getColorRGB(sColour, redValue, greenValue, blueValue);
		displayBigTextLine(2, "%f", redValue);
		displayBigTextLine(4, "%f", greenValue);
		displayBigTextLine(6, "%f", blueValue);
		sleep(100);
	}
}

task dis_col()
{
	while(true)
	{
		disS = SensorValue[sDis];
		displayTextLine(9,"%d",disS);
		displayTextLine(10,"%d",disflag)
		if (disS < dis)
		{
			disflag = 1;
		}
		else
		{
			disflag = 0;
		}
	}
}

task main()
{

	startTask(colour);
	startTask(dis_col);
	while(true)
	{
		if(disflag==1)
		{
			if (greenValue < 10)
			{
				colorflag = 0;
			}
			else
			{
				colorflag=1;
			}
			displayTextLine(8, "%d",colorflag);
			sleep(1);
		}
	}
}
