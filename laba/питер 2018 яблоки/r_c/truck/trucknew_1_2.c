#pragma config(Sensor, S1,     sIr,            sensorEV3_IRSensor, modeEV3IR_Seeker)
#pragma config(Sensor, S2,     sDis,           sensorEV3_IRSensor)
#pragma config(Motor,  motorA,          mA,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          mB,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          mC,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          mD,            tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int v1 = 0;
int	v2 = 0;
task distance()
{
	while (true)
	{
		if(SensorValue[sDis]<15)
		{
			v1 = 0;
			v2 = 0;

		}
		else
		{
			v1 = 20;
			v2 = 50;
		}
	}
}


task main()
{
	startTask(distance);
	int e;
	while(true)
	{

		e = getIRBeaconDirection(sIr);
		displayBigTextLine(4, "%d",e);
		if ( e > 2)
		{
			motor[mB]= -1 * v1;
			motor[mA]= v1;
			sleep(1);
		}
		else if ( e < -2)
		{
			motor[mB]=v1;
			motor[mA]= -1 * v1;
			sleep(1);
		}
		else
		{
			motor[mA]=v2;
			motor[mB]=v2;
			sleep(1);
		}
	}
}
