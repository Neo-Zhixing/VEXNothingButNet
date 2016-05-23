#include "Gyro.h"
#include "GyroTurning.h"
#include "ChassisEncoder.h"

#include "../Library/MenuSystem.h"
void FieldBasedTurn(float time,short speed){
	if(gameField == FieldBlueBack || gameField == FieldBlueFront){//If the field is blue
		if(speed > 0) turnRight(time,seconds,speed);
		else turnLeft(time,seconds,speed);
	}
	else{
		if(speed > 0) turnLeft(time,seconds,speed);
		else turnRight(time,seconds,speed);
	}
}
void FieldBasedSetMotor(short leftPower,short rightPower){
	if(gameField == FieldBlueBack || gameField == FieldBlueFront){//If the field is blue
		motor[ChassisLeftFront] = leftPower;
		motor[ChassisLeftBack] = leftPower;
		motor[ChassisRightFront] = rightPower;
		motor[ChassisRightBack] = rightPower;
	}
	else{
		motor[ChassisLeftFront] = rightPower;
		motor[ChassisLeftBack] = rightPower;
		motor[ChassisRightFront] = leftPower;
		motor[ChassisRightBack] = leftPower;
	}
}
void StartGettingBalls(){
	motor[GettingBalls] = 127;
	motor[CarringBalls] = 127;
}
void StartLosingBalls(short power = 127){
	motor[GettingBalls] = -power;
	motor[CarringBalls] = -power;
}
void StopGettingBalls(){
	motor[GettingBalls] = 0;
	motor[CarringBalls] = 0;
}
void BallsBackward(){
	motor[GettingBalls] = -127;
	motor[CarringBalls] = -127;
	sleep(200);
	motor[GettingBalls] = 0;
	motor[CarringBalls] = 0;
}
void ForwardWithBrake(const float quantity = 1.0, const tMovementUnits unitType = rotations, const short speed = 50){
	forward(quantity*0.85,unitType,speed);
	forward(quantity*0.1,unitType,speed*0.5);
	backward(quantity*0.05,unitType,speed*0.5);
}
void BackwardWithBrake(const float quantity = 1.0, const tMovementUnits unitType = rotations, const short speed = 50){
	backward(quantity*0.85,unitType,speed);
	backward(quantity*0.1,unitType,speed*0.5);
	forward(quantity*0.05,unitType,speed*0.5);
}
bool shootBalls = true;
void AutonomousShooting(float time,bool shoot = true){
	if(!shootBalls){
		if(!shoot)
			sleep(time*1000);
		return;
	}
	autonomousShoot = true;
    autoShoot = shoot;
    resetTimer(T3);
    while(getTimer(T3,seconds) <= time){
        ShootingControl();
    }
    autoShoot = false;
    motor[ShootingLeft] = 0;
    motor[ShootingRight] = 0;
    motor[ExtendShootingLeft] = 0;
    motor[ExtendShootingRight] = 0;
    motor[GettingBalls] = 0;
    motor[CarringBalls] = 0;
    autonomousShoot = true;
}
task ShootingBrakeTask(){
	motor[ShootingLeft] = -10;
	motor[ShootingRight] = -10;
	motor[ExtendShootingLeft] = -6;
	motor[ExtendShootingRight] = -6;
	while(1){
		if(SensorValue[ShootingEncoderLeft] < 5 && SensorValue[ShootingEncoderRight] < 5) break;
		SensorValue[ShootingEncoderLeft] = 0;
		SensorValue[ShootingEncoderRight] = 0;
		sleep(50);
	}
	motor[ShootingLeft] = 0;
	motor[ShootingRight] = 0;
}
void ShootingBrake(){
	startTask(ShootingBrakeTask);
}
#include "Paths.h"
