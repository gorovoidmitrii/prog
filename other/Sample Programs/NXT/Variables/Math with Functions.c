int math(int x)
{
  x = x + 5;
  x = x - 2;
  x = x * 10;
  return x;
}

task main()
{
  int A = 5;
  int B = 20;
  int resultA = 0;
  int resultB = 0;

  resultA = math(A);
  resultB = math(B);

  displayString(1, "A = %d", resultA);
  displayString(2, "B = %d", resultB);

  wait1Msec(5000);
}
