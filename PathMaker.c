#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorSONAR)
#pragma config(Sensor, S3,     HTGyro,         sensorAnalogInactive)
#pragma config(Sensor, S4,     HTIRS2,         sensorI2CCustom)
#pragma config(Motor,  motorA,          motorTray,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorD,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     collector,     tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

float total_distance = 0;

void initializeRobot()
{
  //servo[servo1] = 0;  // Gripper opened
  nMotorPIDSpeedCtrl[motorTray] = mtrSpeedReg;
 	motor[motorTray] = 0;
  return;
}
void resetEncoders(){
	nMotorEncoder[motorD] = 0;
	nMotorEncoder[motorE] = 0;
}
void turn(int direction) {
	int mul = direction;
	if(degrees < 0) {
		mul = -1;
	}
	float prev_rot = 0;

	resetEncoders();
	//float degreesToTurn = degrees - (degrees/27);
	motor[motorD] = 15 * mul;
	motor[motorE] = -15 * mul;
	clearTimer(T1);

		float current_rot = HTGYROreadRot(HTGyro) +14;
		float time = time1[T1];

		float distance = ((prev_rot+current_rot)/2)*time/1000;
		total_distance += distance;
		prev_rot = current_rot;
		clearTimer(T1);
		wait1Msec(10);
motor[motorD] = 0;
motor[motorE] = 0;
  }


task main()
{
  initializeRobot();

  bool isLaunching = false;
  bool isDropping = false;
  int mThreshold = 15;      // Sets dead zones to avoid unnecessary movement
  int aThreshold = 30;
  int xVal, yVal;           //Stores left analog stick values
  float scaleFactor = 40.0 / 127;           //Sets max. average motor power and maps range of analog stick to desired range of power

  //waitForStart();   // wait for start of tele-op phase

  while (true)
  {
    getJoystickSettings(joystick); // Retrieves data from the joystick
    xVal = joystick.joy1_x1;
    yVal = joystick.joy1_y1;
    //Checks if analog stick values are within the dead zone

    /*if (abs(xVal) < mThreshold)
    {

      xVal = 0;
    }
    if (abs(yVal) < mThreshold)
    {
      yVal = 0;
    }*/

    //motor[motorD] = ((yVal) + (xVal) * scaleFactor)/3;      //Sets left motor power
    //motor[motorE] = ((yVal) - (xVal) * scaleFactor)/3;      //Sets right motor power

    //if(joy1Btn(1) == 1 && !isDropping){
    //	isDropping = true;
    //	//servo[servo1] = 120;
    //	servoLower(5);

    //	servo[servo1] = 0;
   //	wait1Msec(500);
    //}
//4 is forward, 2 is backwards, 7 is left, 8 is right

    if(joy1Btn(4) == 1){
    	motor[motorTray] = 20;
    } else if (joy1Btn(2) == 1){
    	motor[motorTray] = -20;
    } else if (joy1Btn(7) == 1){

    }else if (joy1Btn(8) == 1){
    	motor[motorTray] = -20;
    }else{
    	//RECORD CURRENT VARIABLES, THEN RESET EVERYTHING
    }

    //Controls launcher
    //if(joy1Btn(1) == 1 && isLaunching == false){
    	//isLaunching = true;
    	//fireLauncher();
    	//isLaunching = false;
    //}
	//wait1Msec(1);
  }

}