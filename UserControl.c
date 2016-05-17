bool RisingDown = false;
void RisingControl(){
	if(vexRT[JoystickRisingUpBtn]){
		RisingDown = false;
		if(SensorValue[LeftUpSwitch]) motor[RisingLeft] = 0;
		else motor[RisingLeft] = 127;
		if(SensorValue[RightUpSwitch]) motor[RisingRight] = 0;
		else motor[RisingRight] = 127;
	}
	else if(vexRT[JoystickRisingDownBtn]){
		RisingDown = true;
		if(SensorValue[LeftDownSwitch]) motor[RisingLeft] = 0;
		else motor[RisingLeft] = -127;
		if(SensorValue[RightDownSwitch]) motor[RisingRight] = 0;
		else motor[RisingRight] = -127;
	}
	else if(RisingDown){
		motor[RisingLeft] = -15;
		motor[RisingRight] = -15;
	}
	else{
		motor[RisingLeft] = 0;
		motor[RisingRight] = 0;
	}
}



void BallsControl(){
	if(autoShoot) return;
	if(vexRT[JoystickGettingBallsBtn]){
		motor[GettingBalls] = 127;
		motor[CarringBalls] = 127;

	}
	else if (vexRT[JoystickLosingBallsBtn]){
		motor[GettingBalls] = -80;
		motor[CarringBalls] = -80;
		if(motor[ShootingLeft] == 0)motor[ShootingLeft] = -30;
		if(motor[ShootingRight] == 0)motor[ShootingRight] = -30;
	}
	else{
		motor[GettingBalls] = 0;
		motor[CarringBalls] = 0;
	}
}

void ChassisControl()
{
	float nRightSideSpeed = 0;
	float nLeftSideSpeed = 0;

	updateMotorDriveTrain();

	setPIDEnableForDrivetrain(false);
    float verticalValue =  GetPower(vexRT[ChassisVerticalJoystick]) + vexRT[ChassisSlowVerticalJoystick] * ChassisSlowScaledValue;
    float horizontalValue = GetPower(vexRT[ChassisHorizontalJoystick]) + vexRT[ChassisSlowHorizontalJoystick] * ChassisSlowScaledValue;
    nRightSideSpeed = verticalValue - horizontalValue;
    nLeftSideSpeed = verticalValue + horizontalValue;
    if(nRightSideSpeed > 127) nRightSideSpeed = 127;
    else if(nRightSideSpeed < -127) nRightSideSpeed = -127;
    if(nLeftSideSpeed > 127) nLeftSideSpeed = 127;
    else if(nLeftSideSpeed < -127) nLeftSideSpeed = -127;

	setMotorSpeeds((short)nRightSideSpeed,(short) nLeftSideSpeed);
}



task usercontrol()
{
	autoShoot = false;
	SetShortShoot();
	while (true)
	{
		if(holdMainTask) continue;
		AutonomousControl();
		ChassisControl();
		RisingControl();
		ShootingControl();
		ShootingConfigControl();
		BallsControl();
	  //UserControlCodePlaceholderForTesting(); // Remove this function call once you have "real" code.
	}
}
