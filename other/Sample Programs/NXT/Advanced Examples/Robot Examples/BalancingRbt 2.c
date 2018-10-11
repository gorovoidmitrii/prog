// Robot on two wheels
// Change 'bias' to make the robot turn faster or slower (zero for stationary)
//  k1, k2, k3, k4 feedback gains are specified below

const tSensors GyroSensor          = (tSensors) S3;   //gyro sensor//
const tSensors SonarSensor         = (tSensors) S2;

const int   half_h     = 12
; //2;      // Increment used in Runge-Kutta integration
const int   GyroScale  = 2 * half_h;
const float t_scale    = 1000 / half_h;
const float minDist    = 30;     // distance before robot turns
const float v          = 0.0;    // This is the desired velocity of the robot

task main ()
{
	float a          = 0.2;
	float aa         = 0.001;   // aa is the filter time-constant to take care of the gyro drift
	float theta_bias = 0;
	// This is the feedback loop gain
	float k1    = 0.0;     // position feedback gain
	float k2    = -90;      // velocity feedback gain
	float k3    = 8;       // tilt feedback gain
	float k4    = 10.0;    // angular velocity feedback gain
	float k_d   = 16;			 // how fast react to obstacles
	float f1    = 0;
	float f2    = 0;
	int   pwr   = 0;
	int   pwr_th;
	int   pwr_w;
	float kTurnError   = 13 / half_h;     // feedback to keeps the two wheels in-sync
	long  turnError  = 0;
	long  turnOffset = 0;
	int   batt  = 0 ;
	float GyroBias = 600;  // This is the bias that I had to apply to my gyro sensor.  You may need to find your own gyro bias

	float a_pwr      = 1;
	float f_pwr      = 0;
	float k_pwr;           // This is the gain that is computed adaptively based on the battery voltage (as the battery is drained, the gain is increased)
	float fBasePower;

	float theta     = 0;
	float theta_old = 0;
	long  timeOld   = 0;
	float x = 0, x_old =0, x_dot=0;
	float dist = 0;
	bool bInAvoidanceState = false;

	// This causes the motors to stop when they are set to zero
	bFloatDuringInactiveMotorPWM = false;
	bMotorReflected[motorA] = false;
	bMotorReflected[motorC] = false;
	theta_old = 0;
	timeOld = nPgmTime;
	f1=0;
	x_old=0;
	wait1Msec(100);


	clearTimer(T1);
	if (true)
	{
		// Find the gyro bias associated w/ the balanced position
		// Hold the robot in the balanced position for 3 sec to find the gyro bias
		GyroBias = 0;
		while (time1[T1] < 3000)
		{
			// filter the sensor output
			wait1Msec(100);
			GyroBias = (1 - a) * GyroBias + a * SensorValue(GyroSensor);
		}
	}
	else
	{
		// I ended up hard-coding the bias after measuring it a few times.
		// comment out the following line if you want the Gyro bias to be measured adaptively
		GyroBias = 592.6;
	}
	// play a sound when the training is over
	playSound(soundBeepBeep);


	// Measure the battery voltage and compensate for it by adjusting the gain (k_pwr)
	batt = nAvgBatteryLevel;
	k_pwr = 0.7 + (1.1 - 0.7) / (8816 - 8196) * (float) (8816 - batt);

	nMotorEncoder[motorC] = 0;
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorA] = 0;

	// Use the sonar sensor for collisoin avoidance
	SensorType[SonarSensor] = sensorSONAR;
	SensorType[GyroSensor] = sensorLightActive;
	while(true)
	{
		if (!bInAvoidanceState)
		{
			int delta_dist = 0;

			dist = SensorRaw[SonarSensor];
			delta_dist = dist - minDist;
			if (delta_dist < 0)
			{
				// are we close to an obstacle?
				bInAvoidanceState = true;
				clearTimer(T3);   // If yes, turn for 2.5 second
			}
		}
		else
		{
			if (time1(T3) > 2500)
			{
				bInAvoidanceState = false;
				// find out how much more motorA has turned so that we can compensate for it later (when the motors are sync'ed up)
				turnOffset = nMotorEncoder[motorA] - nMotorEncoder[motorC];
			}
		}

		//
		// Runge-Kutta integration (http://en.wikipedia.org/wiki/Runge-kutta)
		//
		wait1Msec(half_h);
		f2 = (SensorRaw(GyroSensor) - GyroBias) / (float) GyroScale; // f(tn+h/2)
		wait1Msec(half_h);
		theta = theta_old + (f1+2*f2) * (nPgmTime - timeOld) / (float) t_scale;
		theta_old = theta;
		x = nMotorEncoder[motorC];
		// compute the linear velocity
		x_dot = x - x_old;
		f1 = (SensorRaw(GyroSensor) - GyroBias) / (float) GyroScale; // f(tn)
		timeOld = nPgmTime;
		x_old = x;

		// Compute the long-term average of tilt
		theta_bias = theta_bias * (1 - aa) + theta * aa;


		pwr_th = k3 * (theta - theta_bias);
		pwr_w  = k4 * f1;
		pwr    = pwr_th + pwr_w + k1*x + k2*(x_dot-(v));

		// Weighted calculation
		f_pwr  = (1-a_pwr)*f_pwr + a_pwr*pwr;


		fBasePower = k_pwr * f_pwr;
		if (bInAvoidanceState)
		{
			motor[motorA] = fBasePower - k_d;
			motor[motorC] = fBasePower + k_d;
		}
		else
		{
		  // kTurnError is to keep the robot going straight
		  turnError = nMotorEncoder[motorA] - nMotorEncoder[motorC] - turnOffset;
			motor[motorA] = fBasePower - kTurnError * turnError;
			motor[motorC] = fBasePower;
		}

	}
}
