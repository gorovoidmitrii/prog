/*-----------------------------------------------------------------------------*/
/*    Description:                                                             */
/*                                                                             */
/*    This sample program will receive user messages containing GPS and app    */
/*    button data and display the parsed message data on the VEX IQ LCD.       */
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

	// Array to hold the received data
char usrMsg[41]; //extra byte for null char

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

/*-----------------------------------------------------------------------------*/
/*   This function displays a warning on the LCD screen indicating that the    */
/*   received message was not a valid format for this program.                 */
/*-----------------------------------------------------------------------------*/
void invalidMsg()
{
	displayString(0, "msg INVALID @ %07d", nPgmTime);
}

/*-----------------------------------------------------------------------------*/
/*   This function processes a GPS data message and displays the parsed        */
/*   data from the message on the LCD screen.                                  */
/*-----------------------------------------------------------------------------*/
void decodeGPSLatLon()
{
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

	// Parse the data in the user message.
	// Example string: GPS+90.123456,+180.123456,12345.00
	if (sscanf(usrMsg, "GPS%d.%d,%d.%d,%d.%d",
						 &nLatWhole, &nLatFraction,
						 &nLonWhole, &nLonFraction,
						 &nAccWhole, &nAccFraction) != 6)
	{
    displayTextLine(1, "ERROR PARSING DATA  ");
    displayTextLine(2, "                    ");
	}
	else
	{
		// Convert the whole and fractional values into normal floats
		fLat = floatFrom2Ints(nLatWhole, nLatFraction);
		fLon = floatFrom2Ints(nLonWhole, nLonFraction);
		fAcc = floatFrom2Ints(nAccWhole, nAccFraction);

		// Select the correct N/S/E/W characters based on if the lat/long values
		// are positive or negative.
		cLatDir = fLat > 0.0 ? 'N' : 'S';
		cLonDir = fLon > 0.0 ? 'W' : 'E';

		string sLat = "";
		string sLon = "";
		string sAcc = "";
		string sTime = "";

		// Format the program time into a string to be displayed
		sprintf(sTime, "%07d", nPgmTime);

		// Convert the floats containing the GPS data into strings with
		// the desired formating for display on the LCD screen.
		stringFormat(sLat, "%8.5f%c", fabs(fLat), cLatDir);
		stringFormat(sLon, "%9.5f%c", fabs(fLon), cLonDir);
		stringFormat(sAcc, "%7.1fm", fabs(fAcc));

		// Display the decoded location
		displayTextLine(1, "%s %s", sLat, sLon);
		displayTextLine(2, "+/-%s @ %s", sAcc, sTime);
	}
}

/*-----------------------------------------------------------------------------*/
/*   This function processes a App Button message and displays the result      */
/*   with a timestamp on the LCD screen                                        */
/*-----------------------------------------------------------------------------*/
void decodeUserBtn()
{
	unsigned int nBtnNumber = 0;
	if (sscanf(usrMsg, "AppBtn%1u", &nBtnNumber) == 1 && nBtnNumber >= 1 && nBtnNumber <= 4)
		displayString(0, "msg AppBtn%d @ %07d", nBtnNumber, nPgmTime);
	else
		invalidMsg();
}


task main()
{
	// Create a placeholder display
	displayString(0, "msg		 NONE @ 0000000");
	displayString(1, "   NONE      NONE   ");
	displayString(2, "+/-NONE     @ 0000000");

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

			// Read the user message into a string
			readUserMessage(usrMsg);

			// Check if the message is a known format and attempt to parse the message
			if (strncmp("AppBtn", usrMsg, 6) == 0)
			{
				// The message appears to be a App Button message
				decodeUserBtn();
			}
			else if (strncmp("GPS", usrMsg, 3) == 0)
			{
				// The message appears to be a GPS data message
				decodeGPSLatLon();
			}
			else
			{
				// Unknown message format
				invalidMsg();
			}

		}

		// Don't hog the cpu
		wait1Msec(50);
	}
}

#endif // End Smart Radio features enabled check
#endif // End platform check
