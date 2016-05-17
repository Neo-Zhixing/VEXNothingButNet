
/*
|  |  |  |  |  |  |
|  |  |  |  |  |  |
|  |  |  |  |  |  |
|  |  |  |  |  |  |
|BF|  |  |  |  |RF|
|  |BB|  |  |RB|  |

BF:Field Blue Front
BB:Field Blue Back
RB:Field Red Back
RF:Field Red Front
*/

enum Field{
	FieldBlueFront,
	FieldBlueBack,
	FieldRedBack,
	FieldRedFront
};
Field gameField = FieldRedFront;


typedef struct {
	float p, i, d;
} PidConfigStruct;

PidConfigStruct gyroPidConfig;

void TurnToAngle (float angle,short maxPower,float maxTime) {
	float lastError = 0;
	float totalError = 0;

	int refreshTimes = 0;
	float maxError = 0;
	float minError = 0;

	Gyro_Reset();

	resetTimer(timer2);
	resetTimer(timer3);
	while (true) {
		if (getTimer(T2, milliseconds) < 10) continue;
		if (getTimer(T3,seconds) > maxTime && maxTime != 0) break;
		Gyro_Refresh();
		float currentAngle = (float)Gyro_Get();

		float error = angle - currentAngle;


		//Exit data collection
		refreshTimes ++ ;
		if(error > maxError) maxError = error;
		if(error < minError) minError = error;
		if(refreshTimes >= 10){
			refreshTimes = 0;
			
			if ((maxError - minError) <= 10) {
				// End of turning.
				writeDebugStreamLine("maxError:%f   minError:%f",maxError,minError);
				writeDebugStreamLine("-------Exit--------");
				break;
			}
			maxError = 0;
			minError = 0;
		}

		totalError = error + totalError * 0.99;
		if ((lastError > 0) != (error > 0)) totalError = 0;

		float pResult = gyroPidConfig.p * error;
		float iResult = gyroPidConfig.i * totalError;
		float dResult = gyroPidConfig.d * (error - lastError);

		float result = pResult + iResult + dResult;

		lastError = error;

		writeDebugStreamLine(
			"p : %f\ti : %f\td : %f\tr : %f",
			pResult, iResult, dResult, result);

		if (result > maxPower) result = maxPower;
		else if (result < -maxPower) result = -maxPower;

		updateMotorDriveTrain();
		setPIDEnableForDrivetrain(false);
		setMotorSpeeds(result,-result);
		resetTimer(timer2);
	}

	setMotorSpeeds(0,0);
}


void FieldBasedGyroTurn(float angle,short maxPower,float maxTime){
	if(gameField == FieldBlueBack || gameField == FieldBlueFront)//If the field is blue
		TurnToAngle(angle,maxPower,maxTime);
	else
		TurnToAngle(-angle,maxPower,maxTime);
}
void FieldBasedGyroTurn(float angle){
	FieldBasedGyroTurn(angle,127,0);
}
void FieldBasedGyroTurn(float angle,float maxTime){
	FieldBasedGyroTurn(angle,127,maxTime);
}
