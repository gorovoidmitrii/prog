#pragma config(Motor,  motorA,          mRunright,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          mRunleft,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          mOut,          tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	nMotorEncoder[mOut]=0;
	while (nMotorEncoder[mOut]< 9800)
	{
		motor[mOut]=100;
	}
	motor[mOut]=0;
}
