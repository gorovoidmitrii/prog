#pragma config(StandardModel, "RVW REMBOT")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	repeat (forever) {
		if (SensorValue[sonar] < 20) {
			backward(2, rotations, 50);
		}
		stopAllMotors();
	}
}
