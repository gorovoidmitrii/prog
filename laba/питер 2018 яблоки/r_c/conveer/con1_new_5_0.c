#pragma config(Sensor, S1,     sCheck2,        sensorTouch)
#pragma config(Motor,  motorA,          mOut,             tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mCheck2,       tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int encod = 0;
int apple_quality = 0;

void Go_out ()

{
	nMotorEncoder[mOut]=0;
	nMotorEncoder[mCheck2]=0;
	while (nMotorEncoder[mOut] < 100)
	{
		motor[mOut]=30;
	}
	playSound(soundLowBuzz);
	motor[mOut]=0 ;
	nMotorEncoder[mOut]=0;
	nMotorEncoder[mCheck2]=0;

	while (nMotorEncoder[mCheck2] < 140)
	{
		motor[mCheck2]=30;
	}

	playSound(soundLowBuzz);
	wait1Msec(1000);
	nMotorEncoder[mOut]=0;
	nMotorEncoder[mCheck2]=0;
	while (nMotorEncoder[mCheck2] > -140)
	{
		motor[mCheck2]=-30;

	}
	playSound(soundBeepBeep);
	wait1Msec(1000);
	nMotorEncoder[mOut]=0;
	nMotorEncoder[mCheck2]=0;

	while (nMotorEncoder[mOut] > -95)
	{
		motor[mOut]=-30;
	}
	motor[mOut]=0;
	nMotorEncoder[mOut]=0;
	nMotorEncoder[mCheck2]=0;

}

void Check_apple ()
{
	nMotorEncoder[mCheck2]=0;
	motor[mCheck2]=30;
	wait1Msec(2000);


	encod = nMotorEncoder[mCheck2];

	nMotorEncoder[mCheck2]=0;
	motor[mCheck2]=-30;
	wait1Msec(2000);
}
task main()
{

	while (SensorValue[sCheck2]<=0)// dlya testa
	{
		wait1Msec(10);
	}
	Check_apple();
	if (encod > 160 )
	{
		apple_quality=0 ;
		playSound(soundBeepBeep);
		wait1Msec(1000);
	}
	else
	{
		apple_quality = 1;
		playSound(soundDownwardTones);
		wait1Msec(1000);

	}
Go_out();



}
