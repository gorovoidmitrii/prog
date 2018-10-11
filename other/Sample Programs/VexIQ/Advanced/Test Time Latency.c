
static float fAvgUserCycleTime;
static volatile unsigned long nNumbOfUserCycles;

const int kTickHistogramSize = 35;
unsigned long nTickDelta[kTickHistogramSize];

const int kTaskTimeHistogramSize = 60;
unsigned long nSystemTaskHistogram[kTaskTimeHistogramSize];
unsigned long nUserTaskHistogram[kTaskTimeHistogramSize];

task main()
{
	static unsigned long nCurrTime;
	static unsigned long nPrevTime;
	static unsigned long nDelta;
	static unsigned long nStartUserCycleCount;
	static unsigned long nStartTime;
	static unsigned long nPrevUserCycleCount;
	static unsigned long nPrevSystemTaskTime;
	static unsigned long nPrevUserTaskTime;

	nStartUserCycleCount = nVexIQUserTaskCycles;
	nPrevSystemTaskTime  = nVexIQSystemTime;
	nPrevUserTaskTime 	 = nVexIQUserTaskTime;
	nStartTime = nVexIQRawTime;
	nPrevTime = nVexIQRawTime;
	while (true)
	{
		nCurrTime = nVexIQRawTime;
		nDelta = nCurrTime - nPrevTime;
		if (nDelta > (kTickHistogramSize - 1))
			nDelta = (kTickHistogramSize - 1);
		++nTickDelta[nDelta];
		nPrevTime = nCurrTime;

		nNumbOfUserCycles = nVexIQUserTaskCycles - nStartUserCycleCount;
		if (nNumbOfUserCycles != nPrevUserCycleCount)
		{
			unsigned long nCurrSystemTaskTime;
			unsigned long nCurrUserTaskTime;
			unsigned long nTaskPeriod;

			nCurrSystemTaskTime = nVexIQSystemTime;
			nCurrUserTaskTime 	= nVexIQUserTaskTime;
			if ((nNumbOfUserCycles % 20) == 19)
			{
				fAvgUserCycleTime = (nCurrTime - nStartTime) / (float) nNumbOfUserCycles;
			}

			if (nNumbOfUserCycles == (unsigned) (nPrevUserCycleCount + 1))
			{
				nTaskPeriod = nCurrSystemTaskTime - nPrevSystemTaskTime;

				if (nTaskPeriod < kTaskTimeHistogramSize)
					++nSystemTaskHistogram[nTaskPeriod];
				else
					++nSystemTaskHistogram[kTaskTimeHistogramSize - 1];

				nTaskPeriod = nCurrUserTaskTime - nPrevUserTaskTime;

				if (nTaskPeriod < kTaskTimeHistogramSize)
					++nUserTaskHistogram[nTaskPeriod];
				else
					++nUserTaskHistogram[kTaskTimeHistogramSize - 1];
			}
			nPrevSystemTaskTime = nCurrSystemTaskTime;
			nPrevUserTaskTime = nCurrUserTaskTime;
			nPrevUserCycleCount = nNumbOfUserCycles;
		}
	}
}
