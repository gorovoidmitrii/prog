#pragma config(StandardModel, "EV3_REMBOT")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	moveMotor(armMotor, 40, degrees, 50);
	wait(2, seconds);
	moveMotor(armMotor, 80, degrees, -35);
}