#pragma config(Sensor, S1,     sColour,          sensorEV3_Touch)
#pragma config(Motor,  motorA,          mCon,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mSort,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mDoor,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task con()
{
	while (true)
	{
		motor[mCon]= 20;
	}
}
void door2_open()
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
void door_open()
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


task main()
{
	startTask (con);

	int colour = 0;
	while (SensorValue[sColour]<=0)// dlya testa
	{
		wait1Msec(10);
	}
	wait1Msec(1000);
	if (SensorValue[sColour] > 0)//red
	{
		colour = 1	; //red

		door2_open ();
		door_open ();

		wait1Msec(5000);

		door_close ();
		wait1Msec(5000);
		door2_close();

	}
	else //  colour =0 yellow
	{
		door_open ();
		wait1Msec(5000);
		playSound(soundBeepBeep);
		door_close ();

	}

	displayTextLine(4, "%d", colour);




}
