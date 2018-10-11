#pragma config(StandardModel, "VEX IQ Clawbot")
#pragma config(RenamedStdModelSensor, port3, lineDetector)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
	Using a Color sensor in "Grayscale" mode, you can create a loop to track the edge of a line.
	This program will run for 10 seconds, controlled by timer 'T1'. Before we begin line tracking,
	we must reset the time back to zero so we will run for the full 10 seconds.

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
	int threshold = 600;      /* found by taking a reading on both DARK and LIGHT    */
														/* surfaces, adding them together, then dividing by 2. */

	clearTimer(T1);						// Resets timer T1 to start counting at 0

	while(time1[T1] < 10000)  // Loops code while timer T1 has counted less than 10 seconds
	{
		if(getColorValue(lineDetector) < threshold)
		{
			// counter-steer right:
			setMotorSpeed(leftMotor, 50);		//Set the leftMotor (motor1) to half power (50)
			setMotorSpeed(rightMotor, 0);   //Set the rightMotor (motor6) to off (0)
		}
		else
		{
			// counter-steer left:
			setMotorSpeed(leftMotor, 0);		//Set the leftMotor (motor1) to off (0)
			setMotorSpeed(rightMotor, 50);  //Set the rightMotor (motor6) to half power (50)
		}
	}
}
