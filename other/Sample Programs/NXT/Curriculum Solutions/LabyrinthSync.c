task main()
{
	//sync the motors and set their turn ratio to equal power (go straight)
  nSyncedMotors = synchBC;
  nSyncedTurnRatio = 100;

  //Set the master motor to move forward
  motor[motorB] = 50;
  wait1Msec(4000);

  //Set the turn ratio to fully mirrored (point turn)
  nSyncedTurnRatio = -100;

    motor[motorB] = 50; //the robot will turn left if the master is positive
  wait1Msec(600);

  //Set the slave motor to match the master and the master motor to move forward
  nSyncedTurnRatio = 100;

  motor[motorB] = 50;
  wait1Msec(3000);

  //Set the turn ratio to fully mirrored (point turn)
  nSyncedTurnRatio = -100;

  motor[motorB] = -50; //the robot will turn right if the master is negative
  wait1Msec(600);

  //Set the slave motor to match the master and the master motor to move forward
  nSyncedTurnRatio = 100;

  motor[motorB] = 50;
  wait1Msec(3000);

  //Set the turn ratio to fully mirrored (point turn)
  nSyncedTurnRatio = -100;

  motor[motorB] = -50; //the robot will turn right if the master is negative
  wait1Msec(600);

  //Set the slave motor to match the master and the master motor to move forward
  nSyncedTurnRatio = 100;

  motor[motorB] = 50;
  wait1Msec(3000);

}
