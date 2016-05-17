#include "PIDLibrary.h"
PIDConfigure* shootingConfigure;
MotorSpeedController shootingController;
int shootingMode;
float MotorLongTargetPower = 42;
float MotorShortTargetPower = 30;
void SetLongShoot(){
	shootingConfigure->p = LongShootP;
	shootingConfigure->targetSpeed = LongShootTargetSpeed;
	shootingController.targetPower = &MotorLongTargetPower;
	shootingMode = 0;
}
void SetShortShoot(){
	shootingConfigure->p = ShortShootP;
	shootingConfigure->targetSpeed = ShortShootTargetSpeed;
	shootingController.targetPower = &MotorShortTargetPower;
	shootingMode = 1;
}
bool autoShoot = false;
void ShootingInit(){
	shootingConfigure = NewPIDConfigure(ShortShootP,0,0,2);

	shootingController.configure = shootingConfigure;
	shootingController.motor = ShootingRight;
	shootingController.extendMotor = ShootingLeft;
	shootingController.lastError = 0;
	shootingController.encoder = ShootingEncoder;
	KalmanFilterInit(&shootingController.filterState,0,5);

	SetShortShoot();
}
bool shootingBrake = true;
void ShootingControl(){
	if( getTimer(T1,milliseconds) >= 50){//1
		if(vexRT[JoystickManuShootBtn] || autoShoot){//2
			//clearDebugStream();
			MotorSpeedControllerRefresh(&shootingController,!(autoShoot || vexRT[JoystickGettingBallsBtn]));
			if(MotorSpeedControllerInRange(&shootingController)){//3
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
				if(SensorValue[ShootingEncoder] >= 5) {
					motor[ShootingLeft] = -6;
					motor[ShootingRight] = -6;
				}
				else {
					motor[ShootingLeft] = 0;
					motor[ShootingRight] = 0;
				}
				SensorValue[ShootingEncoder] = 0;
			}

		}
		resetTimer(T1);
	}//

}

void ShootingConfigControl(){
	if(vexRT[JoystickLongShootBtn]){
		SetLongShoot();
		playTone(1700,30);
		sleep(300);
	}
	else if(vexRT[JoystickShortShootBtn]){
		SetShortShoot();
		playTone(1300,30);
		sleep(300);
	}
	else if(vexRT[JoystickAutoShootBtn]){
		autoShoot = !autoShoot;
		playTone(1500,30);
		sleep(300);
	}
}
