#include "PIDLibrary.h"
PIDConfigure* shootingConfigure;
MotorSpeedController leftShootingController;
MotorSpeedController rightShootingController;
int shootingMode;
float LeftMotorLongTargetPower = 42;
float RightMotorLongTargetPower = 42;
float LeftMotorShortTargetPower = 35;
float RightMotorShortTargetPower = 35;
void SetLongShoot(){
	shootingConfigure->p = LongShootP;
	shootingConfigure->targetSpeed = LongShootTargetSpeed;
	leftShootingController.targetPower = &LeftMotorLongTargetPower;
	rightShootingController.targetPower = &RightMotorLongTargetPower;
	shootingMode = 0;
}
void SetShortShoot(){
	shootingConfigure->p = ShortShootP;
	shootingConfigure->targetSpeed = ShortShootTargetSpeed;
	leftShootingController.targetPower = &LeftMotorShortTargetPower;
	rightShootingController.targetPower = &RightMotorShortTargetPower;
	shootingMode = 1;
}
bool autoShoot = false;
void ShootingInit(){
	shootingConfigure = NewPIDConfigure(ShortShootP,0,0,2);

	leftShootingController.configure = shootingConfigure;
	leftShootingController.motor = ShootingLeft;
	leftShootingController.extendMotor = ExtendShootingLeft;
	leftShootingController.lastError = 0;
	leftShootingController.encoder = ShootingEncoderLeft;
	KalmanFilterInit(&leftShootingController.filterState,0,5);

	rightShootingController.configure = shootingConfigure;
	rightShootingController.motor = ShootingRight;
	rightShootingController.extendMotor = ExtendShootingRight;
	rightShootingController.lastError = 0;
	rightShootingController.encoder = ShootingEncoderRight;
	KalmanFilterInit(&rightShootingController.filterState,0,5);

	SetShortShoot();
}
bool shootingBrake = true;
void ShootingControl(){
	if( getTimer(T1,milliseconds) >= 50){//1
		if(vexRT[JoystickManuShootBtn] || autoShoot){//2
			//clearDebugStream();
			MotorSpeedControllerRefresh(&leftShootingController,!(autoShoot || vexRT[JoystickGettingBallsBtn]));
			MotorSpeedControllerRefresh(&rightShootingController,!(autoShoot || vexRT[JoystickGettingBallsBtn]));
			if(MotorSpeedControllerInRange(&leftShootingController) && MotorSpeedControllerInRange(&rightShootingController)){//3
				//The shooting wheels are ready
				playTone(1000,5);//Beep
				if(autoShoot){
					motor[GettingBalls] = 127;
					motor[CarringBalls] = 127;
				}
			}else{//The shooting wheels are not ready
				if(autoShoot){
					motor[GettingBalls] = 0;
					motor[CarringBalls] = 0;
				}
				 /*if(SensorValue[BallPosSwitch]){
				   motor[GettingBalls] = 0;
				  	motor[CarringBalls] = 0;
				 }else{
				 motor[GettingBalls] = 127;
				 motor[CarringBalls] = 127;
				}*/
			}//3
		}//2
		else{
			if(shootingBrake){
				if(SensorValue[ShootingEncoderLeft] >= 5) {
					motor[ShootingLeft] = -6;
					motor[ExtendShootingLeft] = -6;
				}
				else {
					motor[ShootingLeft] = 0;
					motor[ExtendShootingLeft] = 0;
				}
				if(SensorValue[ShootingEncoderRight] >= 5) {
					motor[ShootingRight] = -6;
					motor[ExtendShootingRight] = -6;
				}
				else {
					motor[ShootingRight] = 0;
					motor[ExtendShootingRight] = 0;
				}
				SensorValue[ShootingEncoderLeft] = 0;
				SensorValue[ShootingEncoderRight] = 0;
			}

		}
		resetTimer(T1);
	}//

}

void ShootingConfigControl(){
	if(vexRT[JoystickLongShootBtn]){
		SetLongShoot();
		if(!bSoundActive) playTone(1700,300);
	}
	else if(vexRT[JoystickShortShootBtn]){
		SetShortShoot();
		if(!bSoundActive) playTone(1300,300);
	}
	else if(vexRT[JoystickAutoShootBtn]){
		autoShoot = !autoShoot;
		playTone(1500,30);
		sleep(300);
	}
}
