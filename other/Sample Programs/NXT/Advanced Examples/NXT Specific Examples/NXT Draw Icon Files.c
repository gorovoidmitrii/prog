///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    Test RIC File Display
//
// Simple program will iterate through all the RIC files on the NXT displaying them one by one with
// a one second delay between files
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT)   // Program applies only to the NXT platform

task main()
{
	string sFileName;
	short nFilesize;
	TFileHandle hFileHandle;
	TFileIOResult nIoResult;

	FindFirstFile(hFileHandle, nIoResult, "*.ric", sFileName, nFilesize);
  while (nIoResult == ioRsltSuccess)
  {
  	eraseDisplay();
  	displayRICFile(0, 0, sFileName);
		wait1Msec(1000);
  	FindNextFile(hFileHandle, nIoResult, sFileName, nFilesize);
	}
	Close(hFileHandle, nIoResult);
  return;
}
