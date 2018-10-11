///////////////////////////////////////////////////////////////////////////////////////////
//
//                        Initalization of Double Arrays
//
// Sample program to show several different methods for initializaiton of doubly indexed
// arrays.
//
///////////////////////////////////////////////////////////////////////////////////////////

char doubleArray1[3][4] =
{
  {'X', 'X', 'X', 'X'},
  {'X', 'X', 'X', 'X'},
  {'X', 'X', 'X', 'X'}
};


char doubleArray11[3][4] =
{
  {'X', 'X', 'X', 'X'},
  {'X', 'X', 'X', 'X'},
  {'X', 'X', 'X', 'X'},  // Same as above but optional comma at end of initialization list
};


char doubleArray2[][] =  // Both array bounds will be determined from the 'initialization' expressions
{
  {'X', 'X', 'X', 'X'},
  {'X', 'X', 'X', 'X'},
  {'X', 'X', 'X', 'X'},
};

char doubleArray3[3][] =  // Second array bounds will be determined from the 'initialization' expressions
{
  {'X', 'X', 'X', 'X'},
  {'X', 'X', 'X', 'X'},
  {'X', 'X', 'X', 'X'},
};

char doubleArray4[3][4] =
{'X','X','X','X',   'X','X','X','X',   'X','X','X','X'}; // An alternative way of using the whitespace in defining the array


// Constructing an array iteratively - This is the best method for arrays that are too large to be reasonably
// initialized by typing out all of the array indecies within the program
{
  int index1;
  int index2;

  char doubleArray5[3][4];

  for (index1 = 0; index1 < 3; ++index1)
  {
    for (index2 = 0; index2 < 4; ++index2)
      doubleArray5[index1][index2] = 'X';
  }
  return;
}
