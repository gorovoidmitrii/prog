#pragma config(StandardModel, "VEX IQ Clawbot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


task main()
{
	repeat (4) {
		forward(2, rotations, 50);
		turnRight(270, degrees, 50);
	}
}