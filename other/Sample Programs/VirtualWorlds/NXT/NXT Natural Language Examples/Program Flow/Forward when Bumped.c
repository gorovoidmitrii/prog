#pragma config(StandardModel, "RVW REMBOT")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


task main()
{
	waitUntil (SensorValue[touch] == 1);
	waitUntil (SensorValue[touch] == 0);
	forward(3, rotations, 50);
}
