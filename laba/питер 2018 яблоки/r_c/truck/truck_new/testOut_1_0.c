#pragma config(Sensor, S1,     sIr1,           sensorEV3_IRSensor, modeEV3IR_Seeker)
#pragma config(Sensor, S2,     sDis,           sensorEV3_GenericI2C)
#pragma config(Sensor, S3,     sApple,         sensorSONAR)
#pragma config(Sensor, S4,     sIr2,           sensorEV3_IRSensor, modeEV3IR_Seeker)
#pragma config(Motor,  motorA,          mA,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          mB,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          mOut,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          mDoor,         tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int nForOut=0;
task out()
{
	while (nForOut == 0)
	{
		while (nMotorEncoder[mOut]>-10)
		{
			motor[mOut]= -100;

			sleep(1);
		}
		sleep(10);
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------
task main()
{
	nForOut=1;
	startTask(out);
	nMotorEncoder[mOut]=0;
	motor[mB]=0;
	motor[mA]=0;
	while (nMotorEncoder[mOut]>-550)
	{
		motor[mOut]= -100;

		sleep(1);
	}
	nForOut=0;
	motor[mOut]=0;
}
