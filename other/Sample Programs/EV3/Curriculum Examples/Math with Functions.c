int A = 5;
int B = 20;

int math(int incomingValue)
{
  int resultValue = 0;

  resultValue = incomingValue + 5;
  resultValue = resultValue - 2;
  resultValue = resultValue * 10;
  return resultValue;
}

task main()
{
  int resultA = 0;
  int resultB = 0;

  resultA = math(A);
  resultB = math(B);

  displayTextLine(1, "A = %d", resultA);
  displayTextLine(2, "B = %d", resultB);

  sleep(10000);
}
