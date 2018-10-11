const int size = 1000;
long array[size];
long test[size];

void shellSortBC(long *A, int size)
{
  int i, j, increment;
  int temp;
  increment = size / 2;

  while (increment > 0) {
    for (i = increment; i < size; i++) {
      j = i;
      temp = A[i];
      while ((j >= increment) && (A[j-increment] > temp)) {
        A[j] = A[j - increment];
        j = j - increment;
      }
      A[j] = temp;
    }

    if (increment == 2)
       increment = 1;
    else
       increment = (unsigned int) ((float)increment / 2.2);
  }
}

task main()
{
	long timeBC = 0;
	long timeNative = 0;

	for (int i = 0; i < size; i++)
	{
		array[i] = rand();
	}

	writeDebugStream("Native sort: ");
	time1[T1] = 0;
	for (int i = 0; i < 100; i++)
	{
		memcpy(test, array, size);
		shellSort(test, size);
	}
	timeNative = time1[T1];
	writeDebugStreamLine("%d", timeNative);

	shellSort(array, size);

	writeDebugStream("Bytecode sort: ");
	time1[T1] = 0;
	for (int i = 0; i < 100; i++)
	{
		memcpy(test, array, size);
		shellSortBC(test, size);
	}
	timeBC = time1[T1];
	writeDebugStreamLine("%d", timeBC);
}
