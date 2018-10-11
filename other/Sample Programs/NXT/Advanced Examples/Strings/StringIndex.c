
string sTemp;
char   sArray[20];


task main()
{
	int i;
	float aSin30a;
	float aSin30b;

	aSin30a = asin(30);
	aSin30b = asin((30 / (float) 360) * (2 * PI));

	memcpy(sArray, sTemp, sizeof(sArray));
	for (i = 0; i < 10; ++i)
	  sArray[i] = '0' + i;
	sArray[10] = 0; // end of string termination
	strcpy(sTemp, sArray);
	return;

}
