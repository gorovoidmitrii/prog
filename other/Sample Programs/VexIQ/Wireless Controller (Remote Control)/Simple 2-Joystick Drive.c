#pragma config(Motor,  motor1,          leftMotor,     tmotorVexIQ, openLoop, encoder)
#pragma config(Motor,  motor6,          rightMotor,    tmotorVexIQ, openLoop, reversed, encoder)
#pragma config(Motor,  motor10,         armMotor,      tmotorVexIQ, openLoop, encoder)
#pragma config(Motor,  motor11,         clawMotor,     tmotorVexIQ, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
  This program will use the VEX IQ Wirless Controller to drive your Clawbot. This program will use
  "Tank Mode" to enable two joysticks to drive the two main motors of the Clawbot.

  The 4 joystick axis on the VEX IQ Wireless Controller return values from -127 to +127.

  Note: You will have to set ROBOTC to enable "Wireless Control" to use the VEX IQ joystick.

                            ROBOT CONFIGURATION: VEX IQ Clawbot
    MOTORS & SENSORS:
    [I/O Port]          [Name]              [Type]                			[Location]
    Port 1        			leftMotor           VEX IQ Motor (Reversed)		  Left side motor
		Port 6       				rightMotor          VEX IQ Motor 							  Right side motor
		Port 10							armMotor						VEX IQ Motor								Arm Up/Down motor
		Port 11							clawMotor						VEX IQ Motor								Claw Open/Close motor
------------------------------------------------------------------------------------------------*/

task main()
{
	repeat(forever)
	{
		setMotorSpeed(leftMotor, getJoystickValue(ChA));
		setMotorSpeed(rightMotor, getJoystickValue(ChD));
	}
}
