#pragma config(Sensor, port5,  colorDetector,  sensorVexIQ_Color12Color)
#pragma config(Sensor, port12, touchLED,       sensorVexIQ_LED)
#pragma config(Motor,  motor1,          leftMotor,     tmotorVexIQ, openLoop, encoder)
#pragma config(Motor,  motor6,          rightMotor,    tmotorVexIQ, openLoop, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	setTouchLEDRGB(touchLED, 0, 0, 0);
	sleep(3000);

	while(getColorName(colorDetector) != colorBlueGreen)
	{
		setTouchLEDColor(touchLED, getColorName(colorDetector));
		setMotorSpeed(leftMotor, 50);
		setMotorSpeed(rightMotor, 50);
	}

	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);
	setTouchLEDColor(touchLED, colorGreen);
	wait1Msec(2000);
}
