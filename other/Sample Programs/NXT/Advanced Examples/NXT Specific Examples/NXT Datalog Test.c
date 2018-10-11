//////////////////////////////////////////////////////////////////////////////////////////////////
//
//                             Test Datalog on the NXT
//                             =======================
//
// This short program illustrate the use of the "Datalog" on the NXT. It illustrates:
// 1. Writing a 1000 entries to the datalog
// 2. Storing the datalog into a standard NXT data file ("DATAnnnn.rdt") at the end of the program
//
// From within the ROBOTC IDE, there are two other datalog related functionalities that are useful
// to experiment with:
// 1. When the debugger is open, then there is a window avaiable (command "Windows -> Datalog") that
//    allows you to view the contents of the datalog.
// 2. Within the "Windows -> Nxt Brick -> File Management" command, there's the capability to read
//    one of these data files and display in the ROBOTC IDE main window. It will upload the "rdt" file
//    and print the contents.
// 3. Also within the "Windows -> Nxt Brick -> File Management" command window are commands to allow
//    you to upload files to the PC where you can post-process them with PC commands.
//
// More useful comments are embedded in this program.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

//
// This program only applies to the NXT. Generate error if using any other platform
//
#pragma platform(NXT)

const int kDatalogSize = 2000;
int nDatalogSize;
const TTimers myTimer = T1;

task main()
{
	int i;

	nDatalogSize = kDatalogSize;
	const int kDataPointType1 = 1;
	const int kDataPointType2 = 2;

	displayTextLine(1, "Datalog Test");

	//
	// A simple loop to fill the datalog. It runs so fast that you probably can't see the
	// numbers changed in the call to 'displayTextLine'
	//
	time1[myTimer] = 0;
	for (i = 0; i < kDatalogSize; ++i)
	{
		if ((i % 10) == 0)
		{
			AddToDatalog(0, time1[myTimer]);
		  AddToDatalog(kDataPointType2, i);
		}
		AddToDatalog(kDataPointType1, i);
		AddToDatalog(0, i);
		displayTextLine(3, "Write %d", i);
		wait1Msec(1);
	}

	//
	// Saves the complete datalog (which is stored in RAM) into a standard NXT file. The
	// file is named "DATAnnnn.RDT" where 'nnnn' is the next available numerical index.
	//
	// The NXT will keep up to 10 'DATAnnnn" files saved on the NXT. It will automatically
	// delete older "DATA" files when there are more than 10.
	//
	// You can use the ROBOTC IDE to upload the datalog via the "Window->NXT Brick->File Management"
	// command.
	//
	// There's another way to display the datalog in ROBOTC. When the debugger is open -- sse
	// the command "Window -> Debug Window" there is another command "Window -> Datalog" that becomes
	// active and allows you to upload the current Datalog contents from RAM to the PC. Note: it will
	// only display the first 500 or so entries in the datalog.
	//
	// Note that the NXT RAM contents (and thus the datalog) are lost when NXT is powered off.
	//
	SaveNxtDatalog();

	playSound(soundFastUpwardTones);
	while (bSoundActive)
	{
		// wait until sound is complete and then some more. Just so user knows program is finished.
	}
	wait1Msec(3000);
	return;
}
