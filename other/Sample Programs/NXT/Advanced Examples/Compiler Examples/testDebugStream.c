int nSleepInterval;
int dummy;


task main()
{
	nSleepInterval = 5;
	while (true)
	{
		writeDebugStreamLine("Debugstream Test: %d", nPgmTime);
		sleep(nSleepInterval);
	}
}
