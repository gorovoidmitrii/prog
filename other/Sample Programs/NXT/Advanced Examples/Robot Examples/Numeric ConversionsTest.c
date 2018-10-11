/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                         Numeric Conversion Tests
//
// Sample program to demonstrate the ability to convert between numeric types. Alose demonstrates
// capability to generate "exception" when a large float value is stored into a "integer" value
// that is too small!
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


byte byteVar1;
short shortVar1;
long  longVar1;
float floatVar1;

// Different opcodes are used for variables with "Big" addresses. Create some big variables
string nFiller[40];
byte byteVar2;
short shortVar2;
long  longVar2;
float floatVar2;

task main()
{
	while (true)
	{
	  bFloatConversionErrors = false; // Disable errors on out of range float values
		for (floatVar1 = 1; floatVar1 < 0x7FFFFFFF; floatVar1 *= 1.1)
		{
			// Variables with "small" addresses

			byteVar1  = floatVar1;
			shortVar1 = floatVar1;
			longVar1  = floatVar1;
			byteVar1  = -floatVar1;
			shortVar1 = -floatVar1;
			longVar1  = -floatVar1;

			// Variables with "big" addresses

			floatVar2 = floatVar1;

			byteVar2  = floatVar2;
			shortVar2 = floatVar2;
			longVar2  = floatVar2;
			byteVar2  = -floatVar2;
			shortVar2 = -floatVar2;
			longVar2  = -floatVar2;
		}

		// Repeat, but generate exception on "overflow". "Exceptions" are expected and program
		// will hit a "breakpoint"

		bFloatConversionErrors = true; // Enable errors on out of range float values
		for (floatVar1 =1; floatVar1 < 0x7FFFFFFF; floatVar1 *= 1.1)
		{
			// Variables with "small" addresses

			byteVar1  = floatVar1;
			shortVar1 = floatVar1;
			longVar1  = floatVar1;
			byteVar1  = -floatVar1;
			shortVar1 = -floatVar1;
			longVar1  = -floatVar1;

			// Variables with "big" addresses

			floatVar2 = floatVar1;

			byteVar2  = floatVar2;
			shortVar2 = floatVar2;
			longVar2  = floatVar2;
			byteVar2  = -floatVar2;
			shortVar2 = -floatVar2;
			longVar2  = -floatVar2;
		}
	}
}
