#pragma config(Motor,  motorA,          mRunleft,      tmotorNXT, openLoop)
#pragma config(Motor,  motorB,          mRunright,     tmotorNXT, openLoop)
#pragma config(Motor,  motorC,          mOut,          tmotorNXT, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{

	motor[mRunleft]=0;
	motor[mRunright]=0;
	nMotorEncoder[mOut]=0;
	while (nMotorEncoder[mOut]<3100)
	{
		motor[mOut]= 100;

		wait1Msec(1);
	}
	motor[mOut]=0;

}
