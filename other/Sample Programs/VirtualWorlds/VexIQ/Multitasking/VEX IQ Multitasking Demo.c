/*------------------------------------------------------------------------------------------------
  This program will run two tasks simulatenously, showing the ability to have your robot complete
  multiple objectives/tasks at the same time. This is illustrated by displaying characters on the
  VEX IQ's LCD Screen to show the two tasks running at the same time.

  In each task is a number of "sleep" commands - these commands yield the processor for a specific
  amount of time to allow other tasks to run.
------------------------------------------------------------------------------------------------*/

//============================================| TASK ONE |============================================
task One()
{
  while(true)
  {
    displayTextLine(0, "Task ONE: /    |");
    sleep(75);
    displayTextLine(0, "Task ONE:  -   /");
    sleep(75);
    displayTextLine(0, "Task ONE:   -  -");
    sleep(75);
    displayTextLine(0, "Task ONE:    \ \ ");   	/* An extra space is needed because '\' */
    sleep(75);                                /* is the "Line Continuation character. */
  }
}
//====================================================================================================

//============================================| TASK TWO |============================================
task Two()
{
  while(true)
  {
    displayTextLine(1, "Task TWO:    / |");
    sleep(75);
    displayTextLine(1, "Task TWO:   -  \ ");   /* An extra space is needed because '\' */
    sleep(75);                              /* is the "Line Continuation character. */
    displayTextLine(1, "Task TWO:  -   -");
    sleep(75);
    displayTextLine(1, "Task TWO: \    /");
    sleep(75);
  }
}
//====================================================================================================


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
  startTask(One);   /* Comment out either of these two lines */
  startTask(Two);   /* to see a Task running individually.   */

  while(true)
  {
    sleep(25); // Keep the program alive, but let the other tasks have the processor by "sleeping"
  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
