#pragma config(StandardModel, "RVW REMBOT")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


task main()
{
	repeat (forever) {
		if (SensorValue[touch] == 0) {
			setMultipleMotors(50, motorB, motorC, motorC);
		} else {
			backward(2, rotations, 50);
			turnLeft(1, rotations, 50);
		}
	}
}