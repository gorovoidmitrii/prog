#pragma config(StandardModel, "VEX IQ Clawbot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
  This program will have your robot make a right point turn for one (1) second and then make a
  left point turn afterwards. At the end of the program, all motors will shut down automatically
  and turn off.

                            ROBOT CONFIGURATION: VEX IQ Clawbot
    MOTORS & SENSORS:
    [I/O Port]          [Name]              [Type]                			[Location]
    Port 1        			leftMotor           VEX IQ Motor		      Left side motor
    Port 6       				rightMotor          VEX IQ Motor		      Right side motor (reversed)
------------------------------------------------------------------------------------------------*/

task main()
{
	setMotorSpeed(leftMotor, -127);		//Set the leftMotor (motor1) to full power reverse (-127)
	setMotorSpeed(rightMotor, 127);  	//Set the rightMotor (motor6) to full power forward (127)
	sleep(1000);											//Wait for 1 second before continuing on in the program.

	setMotorSpeed(leftMotor, 127);		//Set the leftMotor (motor1) to full power forward (127)
	setMotorSpeed(rightMotor, -127);  //Set the rightMotor (motor6) to full power reverse (-127)
	sleep(1000);											//Wait for 1 second before continuing on in the program.
}
