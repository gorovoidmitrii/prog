#pragma config(StandardModel, "VEX IQ Clawbot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


task main()
{
	repeat (forever) {
		lineTrackLeft(colorDetector, 50, 50, 0);
	}
}
