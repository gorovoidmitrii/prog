#pragma config(StandardModel, "VEX IQ Clawbot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	//Keep looping forever
	repeat(forever)
	{
		//Control the robot with Tank Control style driving
		tankControl(ChD, ChA, 10);

		//While button FUp is pressed AND the Distance Sensor is greater than or equal to 200mm
		while(getJoystickValue(BtnFUp) == 1 && getDistanceValue(distanceMM) >= 200)
		{
			//Move the robot backward
			setMotor(leftMotor, -50);
			setMotor(rightMotor, -50);
		}
	}
}
