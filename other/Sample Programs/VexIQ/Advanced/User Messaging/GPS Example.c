/*-----------------------------------------------------------------------------*/
/*    Description:                                                             */
/*                                                                             */
/*    This sample program will display GPS information received from the       */
/*    Robomatter VEX IQ Dashboard iOS app on the VEX IQ LCD.                   */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

// Check platform
#ifndef VexIQ
#error "This program is designed for the VexIQ platform"
#else

// Check if Smart Radio features are enabled
#ifndef VexIQ_SR
#error "This sample needs to have the smart radio features enabled"
#else

/*-----------------------------------------------------------------------------*/
/*   This function takes two integers that represent the whole and fractional  */
/*   part of a floating point value and combines them into a float variable.   */
/*-----------------------------------------------------------------------------*/
float floatFrom2Ints(int nWhole, int nFraction)
{
  float fFraction = nFraction;

  while( fFraction > 1.0 )
    fFraction = fFraction/10.0;

  return((float)nWhole + fFraction);
}


task main()
{
	// We want to never stop looking for messages.
	while (true)
	{
		// Check if there is a new user message to process
		if (userMessageAvailable())
		{

			/*-----------------------------------------------------------------------*/
			/*   There is a message, so now we need to load the message into a       */
			/*   variable and then process the message.                              */
			/*-----------------------------------------------------------------------*/

	    // Array to hold the received data
			char usrMsg[41]; // extra byte for null char

	    // Arrays used to display raw data
			char DisplayLine1[21];
			char DisplayLine2[21];

	    // Chars used store the N/S and E/W characters for the location strings
			char cLatDir = '?';
			char cLonDir = '?';

	    // Floats used to store the whole and fractional parts of the
			// latitude, longitude, and accuracy values
			long nLatWhole, nLatFraction;
			long nLonWhole, nLonFraction;
			long nAccWhole, nAccFraction;

	    // Floats used to store the actual latitude, longitude, and accuracy values
			float fLat = 0.0;
			float fLon = 0.0;
			float fAcc = 0.0;

			// Read the user message into a string
			readUserMessage(usrMsg);

			// Parse the data in the user message.
			// Example string: GPS+90.123456,+180.123456,12345.00
			if (sscanf(usrMsg, "GPS%d.%d,%d.%d,%d.%d",
								 &nLatWhole, &nLatFraction,
								 &nLonWhole, &nLonFraction,
								 &nAccWhole, &nAccFraction) != 6)
			{
        displayTextLine(0, "ERROR PARSING DATA  ");
        displayTextLine(1, "                    ");
			}
			else
			{
				// Convert the whole and fractional values into normal floats
				fLat = floatFrom2Ints(nLatWhole, nLatFraction);
				fLon = floatFrom2Ints(nLonWhole, nLonFraction);
				fAcc = floatFrom2Ints(nAccWhole, nAccFraction);

				// Select the correct N/S/E/W characters based on if the lat/long values
				// are positive or negative
				cLatDir = fLat > 0.0 ? 'N' : 'S';
				cLonDir = fLon > 0.0 ? 'W' : 'E';

				// Display the decoded location
				displayTextLine(0, "%8.5f%c", abs(fLat), cLatDir);
				displayTextLine(1, "%9.5f%c", abs(fLon), cLonDir);
			}

			/*-----------------------------------------------------------------------*/
			/*   Display the raw message on the screen                               */
			/*-----------------------------------------------------------------------*/

			// Clear old line data
			memset(DisplayLine1, 0, 21);
			memset(DisplayLine2, 0, 21);

			// Copy over the new message data
			memcpy(DisplayLine1, &usrMsg[00], 20);
			memcpy(DisplayLine2, &usrMsg[20], 20);

			// Clear the old data from the screen
			displayString(2, "                    ");
			displayString(3, "                    ");

			// Display the new raw data on the screen
			displayString(2, DisplayLine1);
			displayString(3, DisplayLine2);

		}

		// Don't hog the cpu
		wait1Msec(10);
	}
}

#endif // End Smart Radio features enabled check
#endif // End platform check
