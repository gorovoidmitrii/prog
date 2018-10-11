#pragma config(Motor,  motorA,          mSshat,        tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          mGnil,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mDver,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	nMotorEncoder[mGnil]=0;
	nMotorEncoder[mSshat]=0;
	nMotorEncoder[mDver]=0;

	// iiaaoaee iiea ia oaeaaee oaao

	nMotorEncoder[mSshat]=0;
	motor[mSshat]=30;
	wait1Msec(2000);


	int Sshat = nMotorEncoder[mSshat];

	nMotorEncoder[mSshat]=0;
	motor[mSshat]=-30;
	wait1Msec(2000);

	nMotorEncoder[mSshat]=0;
	if (Sshat > 160)
	{
		while (nMotorEncoder[mGnil] < 50)
		{
			motor[mGnil]=30;
		}

		while (nMotorEncoder[mSshat] < 140)
		{
			motor[mSshat]=30;
		}
		nMotorEncoder[mGnil]=0;
		nMotorEncoder[mSshat]=0;
		nMotorEncoder[mDver]=0;

		while (nMotorEncoder[mGnil] > -45)
		{
			motor[mGnil]=-30;
		}

		while (nMotorEncoder[mSshat] > -140)
		{
			motor[mSshat]=-30;
		}
	}
}
