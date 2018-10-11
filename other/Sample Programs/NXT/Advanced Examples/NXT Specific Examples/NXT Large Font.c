///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    Test Large FONT Drawing
//
// Characters in standard firmware use a 6W x 8H FONT.
//
// ROBOTC also supports a larger font of 12W x 16H pixels.
//
// This sample program shows how to use the larger font. It's very easy!
//
// 'displayStringAt'     This function formats and displays a string at the specified coordinates
//                          on the NXT LCD screen using the standard 6 x 8 font.
//
// 'displayBitStringAt'  Identical to the preceding function except it uses the large font!

///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT)   // Program applies only to the NXT platform

{
	int nIndex;

	for (nIndex = 0; nIndex < 10000; nIndex += 10)
	{
  	displayStringAt(0, 31, "Standard %d.", nIndex);
  	displayBigStringAt(0, 15, "Big %d.", nIndex);
		wait1Msec(100);
	}
	return;
}
