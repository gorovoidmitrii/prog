#pragma config(StandardModel, "VEX IQ Clawbot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
  This program will move the motors forward and backwards

                            ROBOT CONFIGURATION: VEX IQ Clawbot
    MOTORS & SENSORS:
    [I/O Port]          [Name]              [Type]                			[Location]
    Port 1        			leftMotor           VEX IQ Motor		      			Left side motor
    Port 6       				rightMotor          VEX IQ Motor		      			Right side motor (reversed)

------------------------------------------------------------------------------------------------*/

task main()
{
	//Reset the current position in the motor encoder to zero.
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	//Set motor to run 5000 counts at power level 75.
	moveMotorTarget(leftMotor, 5000, 75);
	moveMotorTarget(rightMotor, 5000, 75);
	//Blocking command prevents program from continuing until movement is complete.
	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);

	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	moveMotorTarget(leftMotor, -5000, -75);
	moveMotorTarget(rightMotor, -5000, -75);
	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);
}
