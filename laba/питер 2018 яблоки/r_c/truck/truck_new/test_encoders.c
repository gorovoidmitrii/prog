#pragma config(Sensor, S1,     sLeft,    sensorEV3_GenericI2C)
#pragma config(Sensor, S2,     sIr1,           sensorEV3_IRSensor)
#pragma config(Sensor, S3,     sDis,           sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     sIr2,           sensorEV3_IRSensor)
#pragma config(Motor,  motorA,          mA,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          mB,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          mOut,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          mDoor,         tmotorEV3_Medium, PIDControl, encoder)

int const ENCODERS_360 = 1100;//1050;//1000;//1150;//1100;//1238;//1193;//1188;//1210;//1040;
task main()
{
	/*	nMotorEncoder[mA] = 0;
	while (SensorValue[sIr1]>20)
	{
	motor[mA]=20;
	motor[mB]=-20;
	displayTextLine(1,"%d",nMotorEncoder[mA]);
	}
	motor[mA]=0;
	motor[mB]=0;*/
	sleep(5000);
	nMotorEncoder[mA] = 0;
	while (nMotorEncoder[mA]<ENCODERS_360)
	{
		motor[mA]=20;
		motor[mB]=-20;
		displayTextLine(1,"%d",nMotorEncoder[mA]);
	}
	motor[mA]=0;
	motor[mB]=0;
	sleep(5000);
	//sleep(5000);
	nMotorEncoder[mA] = 0;
	while (nMotorEncoder[mA]>-1 * ENCODERS_360)
	{
		motor[mA]=-20;
		motor[mB]=20;
		displayTextLine(1,"%d",nMotorEncoder[mA]);
	}
	motor[mA]=0;
	motor[mB]=0;
	sleep(5000);

}
