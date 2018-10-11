task main()
{
	int nPortIndex;
	TVexIQDeviceTypes nDeviceType;
	TDeviceStatus nDeviceStatus;
	short nDeviceVersion;
	bool bI2CType;
	char *pzType;
	string sVersion;
	int nNumbOfDevices = 0;
	clearDebugStream();

	for (nPortIndex = 0; nPortIndex < 12; ++nPortIndex)
	{
		getVexIqDeviceInfo(nPortIndex, nDeviceType, nDeviceStatus, nDeviceVersion);
		if (nDeviceType == vexIQ_SensorNone)
			continue;

		switch (nDeviceType)
		{
		default:											pzType = "?????";			bI2CType = false;		break;
		case vexIQ_SensorMOTOR:				pzType = "Motor";			bI2CType = true;		break;
		case vexIQ_SensorLED:					pzType = "LED";				bI2CType = true;		break;
		case vexIQ_SensorRGB:					pzType = "RGB";				bI2CType = true;		break;
		case vexIQ_SensorGYRO:				pzType = "Gyro";			bI2CType = true;		break;
		case vexIQ_SensorSONAR:				pzType = "Sonar";			bI2CType = true;		break;

		case vexIQ_SensorBUMPER:			pzType = "Bumpr";			bI2CType = false;		break;
		}

		if (bI2CType)
		{
			sprintf(sVersion, "V%d", nDeviceVersion);
		}
		else
		{
			sVersion = "";
		}
		if (nNumbOfDevices == 0)
    	writeDebugStreamLine("Port:  Type    Version");
		writeDebugStreamLine("%4d:  %5s   %3s", nPortIndex + 1, pzType, sVersion);
		if (nNumbOfDevices < 5)
		{
			drawUserText(nNumbOfDevices * 9, 0, "Port %2d: %5s %3s", nPortIndex + 1, pzType, sVersion);
		}

		++nNumbOfDevices;
	}
	sleep(10000);
}
