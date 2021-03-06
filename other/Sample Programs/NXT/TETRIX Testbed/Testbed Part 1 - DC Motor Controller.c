#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S2,     touch,               sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
  while(1 == 1)   //Loop forever
  {
    if(SensorValue[touch] == 1)   //If the touch sensor is pressed...
    {
      motor[motorD] = 25;         //...spin Motor D at 25% power.
    }
    else                          //Else, the touch sensor isn't pressed...
    {
      motor[motorD] = 0;          //...turn Motor D off.
    }
  }
}
