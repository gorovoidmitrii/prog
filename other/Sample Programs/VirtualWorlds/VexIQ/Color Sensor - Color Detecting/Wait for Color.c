#pragma config(StandardModel, "VEX IQ Clawbot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(getColorName(colorDetector) != colorGreen)
	{
		setMotorSpeed(leftMotor, 50);
		setMotorSpeed(rightMotor, 50);
	}
}
