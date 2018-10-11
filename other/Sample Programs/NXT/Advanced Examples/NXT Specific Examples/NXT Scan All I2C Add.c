/////////////////////////////////////////////////////////////////////////////////////////////
//
//   Program to test I2C Communications to PCF8574 I2C to Parallel Port
//
//
// Assumption:
//   Parallel port is connected as I2C address 0x40. That is:
//      upper nibble is fixed in the chip as '4'
//      lower nibble is set as zero by connecting all three address lines to ground.
//
//   PCF8574 is connected to sensor port 1.
//
/////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////
//
//                                           Main Task
//
// Virtuall all I2C sensors are connected via I2C address 0x02. This program is used to scan
// the complete address range to see if there are any other I2C devices on the sensor port
// with different addresses.
//
// Note that addresses are always "even" numbers. The 'odd' numbered addresses are used for
// write messages to a valid good address.
//
/////////////////////////////////////////////////////////////////////////////////////////////

byte i2cconfg[3];
const tSensors kPort 			= S1;
const short kSize         = 0;
const short kI2CAddr      = 1;
const short kInternalAddr = 2;

typedef ubyte TResults[8];


void displayResults(short nLine, short nAddress, const string &sNameString, TResults &ReplyResults, short nindex)
{
	i2cconfg[kSize]         = 2;         // Two bytes in the message
	i2cconfg[kI2CAddr]      = nAddress;
	i2cconfg[kInternalAddr] = nindex;

	sendI2CMsg(kPort, &i2cconfg[0], sizeof(TResults));
	while (nI2CStatus[kPort] == STAT_COMM_PENDING)
	{}
	if (nI2CStatus[kPort] != NO_ERR)
		return;

	readI2CReply(kPort, &ReplyResults[0], sizeof(TResults));
	displayTextLine(nLine, "%s", sNameString, "");
	displayTextLine(nLine + 1, "%s", ReplyResults[0]);
}

task main()
{
	short nAddress;
	int   nLastGoodAddress    = -1;
	bool  bGoodAddress[256];
	TResults nVersion;
	TResults nManufacturer;
	TResults nProduct;

	SensorType[kPort] = sensorI2CCustom;

	//
	// Selectively turn on one single output pin at a time
	//
	for (nAddress = 0; nAddress <= 255; ++nAddress)
		bGoodAddress[nAddress] = false;
	while (true)
	{
		for (nAddress = 0; nAddress < 256; nAddress += 2)
		{
			//
			// Build outgoing message and send
			//
			i2cconfg[kSize]         = 2;         // Two bytes in the message
			i2cconfg[kI2CAddr]      = nAddress;
			i2cconfg[kInternalAddr] = 0;

			sendI2CMsg(kPort, &i2cconfg[0] , 0);
			while (nI2CStatus[kPort] == STAT_COMM_PENDING)
			{}
			if (nI2CStatus[kPort] != NO_ERR)
			{
			  if (nAddress == nLastGoodAddress)
			    nLastGoodAddress = -1;
			  continue;
			}

			//
			// found a responding device
			//
			bGoodAddress[nAddress] = true;
			nLastGoodAddress = nAddress;
			displayResults(2, nAddress, "Manufacturer", nManufacturer, 0x08);
			displayResults(4, nAddress, "Version",      nVersion,      0x00);
			displayResults(6, nAddress, "Product",      nProduct,      0x10);
		}
	}
	return;
}
