#pragma config(StandardModel, "VEX IQ Clawbot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


task main()
{
	waitUntil (getBumperValue(bumpSwitch) == 1);
	forward(3, rotations, 100);
}
