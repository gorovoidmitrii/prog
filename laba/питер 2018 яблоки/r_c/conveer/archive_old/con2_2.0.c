#pragma config(Sensor, S1,     sSvet,          sensorEV3_Touch)
#pragma config(Motor,  motorA,          mCon,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mSort,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,           ,             tmotorEV3_Large, openLoop)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task con()
{
  while (true)
  {
  	motor[mCon]= 50;
  }
}


task main()
{
	startTask (con);
	int svet = 0;
	while (SensorValue[sSvet]<=0)// dlya testa
	{
		wait1Msec(10);
	}
	wait1Msec(1000);
	if (SensorValue[sSvet] > 0)
	{
	 svet = 1	;

	}
	displayTextLine(4, "%d", svet);


}
