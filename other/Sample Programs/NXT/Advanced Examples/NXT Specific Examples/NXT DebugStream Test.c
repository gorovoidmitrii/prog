///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                             Test ROBOTC DebugStream
//
// ROBOTC has feature to write text to a "debugStream". Text that is written to the debug stream will
// appear on a PC based window when the ROBOTC debugger is active.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(_DEBUG)
  #warning "Debug stream is only active when compiled with 'debug' option"
#endif

{
	int i;
	string sString;

	for (i = 0; i < 10000; ++i)
	{
		stringFormat(sString, "Debug test%05d", i);
		writeDebugStreamLine(sString);
		wait1Msec(1);
	}
	return;
}
