#pragma config(StandardModel, "VEX IQ Clawbot")
#pragma config(RenamedStdModelSensor, port3, lineDetector)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
 This program instructs the robot to move until the the color sensor detects a dark color, and
 then come to a stop by ending the program.

 Note: Lighting conditions change from place to place, so the value '600' may need to be changed
       to better suit your environment. Grayscale Values can range from 0 to 2000 (possibly even higher)

                            ROBOT CONFIGURATION: VEX IQ Clawbot
    MOTORS & SENSORS:
    [I/O Port]          [Name]              [Type]                			[Location]
    Port 1        			leftMotor           VEX IQ Motor		      			Left side motor
    Port 6       				rightMotor          VEX IQ Motor		      			Right side motor (reversed)
		Port 5       				lineDetector       	VEX IQ Color		      			Color Detector (Grayscale Mode)
------------------------------------------------------------------------------------------------*/

task main()
{
	while(getColorValue(lineDetector) < 600) // While the Color sensor in 'grayscale' mode reads a value less than 600
	{
		setMotorSpeed(leftMotor, 50);		//Set the leftMotor (motor1) to half power (50)
		setMotorSpeed(rightMotor, 50);  //Set the rightMotor (motor6) to half power (50)
	}
}
