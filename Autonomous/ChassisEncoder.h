
void forward(int target,short maxSpeed,float maxTime){
	SensorValue[ChassisEncoder] = 0;
	resetTimer(timer2);//refresh timer
	resetTimer(timer3);//timeout timer
	int refreshTimes = 0;
	int maxError = 0;
	int minError = 0;
	while(1){
		if (getTimer(T2, milliseconds) < 10) continue;//refresh per 10 ms
		if (getTimer(T3,milliseconds) < maxTime && maxTime != 0) break;//time out

		int error = target - SensorValue[ChassisEncoder];
		float offset = error * ChassisP;

		if(offset > 127) offset = 127;
		else if(offset < -127) offset = -127;

		updateMotorDriveTrain();
		setPIDEnableForDrivetrain(false);
		setMotorSpeeds(offset,offset);

		refreshTimes++;
		if(error > maxError) maxError = error;
		else if(error < minError) minError = error;
		if(refreshTimes > 10){
			refreshTimes = 0;
			if(maxError - minError > 10) break;
			maxError = 0;
			minError = 0;
		}
	}
	setMotorSpeeds(0,0);
}