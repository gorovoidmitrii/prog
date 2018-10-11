#pragma config(Sensor, port7, distanceSensor,     sensorVexIQ_Distance)
#pragma config(Motor,  motor1,          leftMotor,     tmotorVexIQ, openLoop, encoder)
#pragma config(Motor,  motor6,          rightMotor,    tmotorVexIQ, openLoop, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
The VEX IQ Distance Sensor is able to detect up to 3 different values -
Strongest Signal: Returns the strongest signal based on proximity to the sensor.

Second Strongest Signal: Returns the second strongest signal based on proximity to the sensor.

Most Reflective: Returns the distance to the most reflective (typically the largest) object detect.
								 This is the object that returns the most reflected sound.

The sensor may detect the Strongest and Most Reflective as the same object and return the same value.

Note: The VEX IQ Distance Sensor returns values in millimeters.

ROBOT CONFIGURATION: VEX IQ Clawbot
MOTORS & SENSORS:
[I/O Port]          [Name]              [Type]                			[Info]
Port 7        			distanceSensor      VEX IQ Distance		      		Distance Sensor (returns mm)
------------------------------------------------------------------------------------------------*/

task main()
{
	while(true)
	{
		//Display the 3 different values from the Distance Sensor to the VEX IQ LCD Screen
		displayTextLine(1, "Strong:  %d mm", getDistanceStrongest(distanceSensor));
		displayTextLine(2, "2ndStr:  %d mm", getDistanceSecondStrongest(distanceSensor));
		displayTextLine(3, "Reflect: %d mm", getDistanceMostReflective(distanceSensor));
		sleep(50);  //Delay 50ms to allow new data to appear.
	}
}
