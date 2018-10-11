#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_5,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_6,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_7,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_8,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           ,              tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port2,           ,              tmotorVex269, openLoop, encoder, encoderPort, I2C_5, 1000)
#pragma config(Motor,  port3,           ,              tmotorVex269, openLoop, encoder, encoderPort, I2C_6, 1000)
#pragma config(Motor,  port4,           ,              tmotorVex269, openLoop, encoder, encoderPort, I2C_7, 1000)
#pragma config(Motor,  port5,           ,              tmotorVex269, openLoop)
#pragma config(Motor,  port6,           ,              tmotorVex269, openLoop, encoder, encoderPort, I2C_8, 1000)
#pragma config(Motor,  port7,           ,              tmotorVex269, openLoop)
#pragma config(Motor,  port8,           ,              tmotorVex269, openLoop, encoder, encoderPort, I2C_3, 1000)
#pragma config(Motor,  port9,           ,              tmotorVex269, openLoop, reversed, encoder, encoderPort, I2C_4, 1000)
#pragma config(Motor,  port10,          ,              tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_2, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int encoderValues[10];

void copyEncoderValues()
{
  for (int i = 0; i < 10; ++i)
    encoderValues[i] = nMotorEncoder[i];
  return;
}


task main()
{
  //nCortexCommType = ctUSBCable;
	nMotorEncoder[port1]  = 0;
	nMotorEncoder[port10] = 0;
	nMotorEncoder[port8]  = 0;
	nMotorEncoder[port9]  = 0;
	copyEncoderValues();

  while (true)
  {
    motor[port1]  = -20;
    motor[port10] = -20;
    motor[port8]  = -20;
    motor[port9]  = -20;

    wait1Msec(800);
    copyEncoderValues();

    motor[port1]  = 0;
    motor[port10] = 0;
    motor[port8]  = 0;
    motor[port9]  = 0;

    wait1Msec(1800);
    copyEncoderValues();

    motor[port1]  = 100;
    motor[port10] = 80;
    motor[port8]  = 60;
    motor[port9]  = 40;

    wait1Msec(800);
    copyEncoderValues();

    motor[port1]  = 0;
    motor[port10] = 0;
    motor[port8]  = 0;
    motor[port9]  = 0;

    wait1Msec(1800);
    copyEncoderValues();
  }
}
