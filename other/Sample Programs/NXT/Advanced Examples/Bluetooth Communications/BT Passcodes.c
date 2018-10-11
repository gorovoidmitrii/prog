////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//             Sample Program to Manipulate Default Bluetooth Passcodes
//
// ROBOTC maintains two different Bluetooth "default" passcodes.
//
// Default    is stored in flash memory and is permanent. In a fresh unmodified firmware load
//            the default passcode is set to the value "1234".
//
// Session    is stored in RAM and is valid only for a single power-on cycle of the NXT.
//
// ROBOTC has functions to read and write both passcodes (PINs).
//
// When the NXT is first powered up the "Default" passcode is copied to the "Session" passcode.
// The Default passcode is also copied to the session passcode whenever it is modified.
//
// THe "default" Sessionpasscode has two purposes.
//
// 1. It (i.e. the current setting of the "Session" passcode) is used as the initial value when
//    a passcode is manually entered via the NXT LCD and keypad.
//
// 2. Manual passcode entry can be bypassed and the "Session" passcode directly used as password
//    input if the boolean variable 'bBTSkipPswdPrompt' is set.
//
// The reason there are two different defaults is because there are cases when you may want to
// modify the "Session" passcode without updating the default. For example,
//
// 1. The default passcode in several NXTs and a PC have all been set to "5678" (i.e. a nice value
//    outside of the normal default. These devices all simply connect to each other without
//    requiring passcode entry because 'bBTSkipPswdPrompt' has been set.
//
// 2. You also have a bluetooth enabled GPS receiver that has a fixed passcode of "0000". You
//    cannot use the "5678" passcode. You occassionally have need to connect to the GPS receiver
//    and want to do so within your application program. So you set the session passcode to '0000'
//    but do not modify the default.
//
//    After you have connected, you use the "resetSessionPIN()" function to restore the
//    session passcode to the default value stored in Flash.
//
// NOTE: The parameters to these functions are ROBOTC 'string'. The passcode is actually 16-characters.
//       Using a 'string' means that a passcode byte of 0x00 cannot be used as it will be treated
//       as the string termination character. This is likely not a big deal as the manual passcode
//       entry function only supports a subset of printable ASCII characters anyway so there is not
//       a worse restriction than already existed.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT)


intrinsic TFileIOResult requestPinEntry()   asm(BTOpcdFcn(PinReq));

task main()
{
  static const string sPIN2 = "2222";
  static const string sPIN3 = "3333";

  string sDefault1;
	string sDefault2;
	string sDefault3;

	string sSession1;
	string sSession2;
	string sSession3;


  //
  // Program simply reads and writes the various passcodes. Use the ROBOTC debugger to confirm that the
  // expected result is achieved.
  //
  getDefaultPIN(sDefault1);
  getSessionPIN(sSession1);

  //
  // Confirm that setting "Default" also updates the "Session"
  //
  setDefaultPIN(sPIN2);
  getDefaultPIN(sDefault2);
  getSessionPIN(sSession2);

  //
  // Confirm that setting "Session" does not update the "Session"
  //
  setSessionPIN(sPIN3);
  getDefaultPIN(sDefault3);
  getSessionPIN(sSession3);

  setDefaultPIN(sDefault1);   // Restore to original value

  //
  // Test PIN code entry. A very bad kludge
  //

  TFileIOResult nStatus;

  bBTSkipPswdPrompt = false;
  requestPinEntry();
  while (true)
  {
  	nStatus = nBluetoothCmdStatus;
  	if (!bBTBusy)
  		break;
  }

}
