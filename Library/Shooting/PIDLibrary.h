#include "KalmanFilter.h"
typedef struct{
	float p,i,d;
	float tolerance;
	float targetSpeed;
}PIDConfigure;
typedef struct{
	tMotor motor;
	tMotor extendMotor;
	tSensors encoder;
	PIDConfigure *configure;
	float *targetPower;
	float totalError;
	float lastError;
	int rawSensorValue;
	KalmanFilterState filterState;
	float power;
}MotorSpeedController;

PIDConfigure* NewPIDConfigure(float p,float i,float d,float tolerance){
	PIDConfigure configure;
	configure.p = p;
	configure.i = i;
	configure.d = d;
	configure.tolerance = tolerance;
	return &configure;
}

void MotorSpeedControllerRefresh(MotorSpeedController* controller,bool calibrate){
	float rawValue = abs(SensorValue[controller->encoder]) * EncoderScaledValue;
	float sensorValue = KalmanFilter(controller->filterState,rawValue);
	controller->rawSensorValue = rawValue;
	float error = controller->configure->targetSpeed - sensorValue;
	SensorValue[controller->encoder] = 0;
	controller->lastError = error;

	float offset;
	if(error > 0)offset = error*error*error * controller->configure->p;
	else offset = error * 1.5;
	float power = offset + *(controller->targetPower);
	if(power > 127) power = 127;
	else if(power < 0) power = 0;

	motor[controller->motor] = power;
	motor[controller->extendMotor] = power;
	controller->power = power;

	if(abs(error) >= 1 &&abs(error) < 4 && calibrate)*(controller->targetPower) += (1/error) * 0.3;
	writeDebugStreamLine("%f|%f|%f|%f|%f|%d",error,power,sensorValue,rawValue,*(controller->targetPower),calibrate);
}

bool MotorSpeedControllerInRange(MotorSpeedController* controller){
	return abs(controller->lastError) <= controller->configure->tolerance;
}

void MotorSpeedControllerCalibrate(MotorSpeedController* controller){
	float rawValue = abs(SensorValue[controller->encoder]) * EncoderScaledValue;
	float sensorValue = KalmanFilter(controller->filterState,rawValue);
	float error = controller->configure->targetSpeed - sensorValue;
	SensorValue[controller->encoder] = 0;

	//Proportion Part
	float pResult = controller->configure->p * error;

	//Integral Part
	controller->totalError *= 0.9;
	controller->totalError += error;
	if((controller->lastError > 0) != (error > 0)) controller->totalError = 0;
	float iResult = controller->totalError * controller->configure->i;

	//Differential Part
	float dError = error - controller->lastError;
	float dResult = dError * controller->configure->d;
	controller->lastError = error;

	float power = pResult + iResult + dResult + *(controller->targetPower);
	if(power > 127) power = 127;
	else if(power < 0) power = 0;

	motor[controller->motor] = power;
	motor[controller->extendMotor] = power;
	*(controller->targetPower) = power;
	writeDebugStreamLine("error%f   motor%f sensor %f",error,power,sensorValue);
	controller->power = power;
}
