#pragma config(Motor,  motorA,          mRunleft,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          mRunright,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          mOut,          tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	nMotorEncoder[mRunright]=0;
	nMotorEncoder[mRunleft]=0;
	while (nMotorEncoder[mRunleft]< 500)
	{
		motor[mRunleft]=50;
		motor[mRunright]=50;
	}
	motor[mRunleft]=0;
	motor[mRunright]=0;
	nMotorEncoder[mOut]=0;
	while (nMotorEncoder[mOut]> -9800)
	{
		motor[mOut]= -100;
	}
	motor[mOut]=0;
	nMotorEncoder[mOut]=0;
	while (nMotorEncoder[mOut]< 9800)
	{
		motor[mOut]=100;
	}
	motor[mOut]=0;
}
