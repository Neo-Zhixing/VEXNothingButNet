void CalibrateAction(){
	shootingConfigure->p = 0.1;
	shootingConfigure->i = 0.0005;
	shootingConfigure->d = 1.5;
	SetShortShoot();
	shootingConfigure->p = 0.1;
	while(!(nLCDButtons == kButtonCenter)){
		if(nLCDButtons == kButtonLeft || nLCDButtons == kButtonRight){
			allMotorsOff();
			return;
		}
		clearDebugStream();
		MotorSpeedControllerCalibrate(&shootingController);
		if(MotorSpeedControllerInRange(&shootingController)){
			writeDebugStreamLine("In Range!!!");
			playTone(1500,5);
		}
		clearLCDLine(1);

		string line;
		stringFormat(line,"L:%3.1f P:%2.1f",shootingController.lastError,shootingController.power);

		displayLCDString(1,0,line);
		sleep(50);
	}
	WaitTillButtonsRelease();

	SetLongShoot();
	shootingConfigure->p = 0.1;
	while(!(nLCDButtons == kButtonCenter)){
		if(nLCDButtons == kButtonLeft || nLCDButtons == kButtonRight){
			allMotorsOff();
			return;
		}
		clearDebugStream();
		MotorSpeedControllerCalibrate(&shootingController);
		if(MotorSpeedControllerInRange(&shootingController)){
			writeDebugStreamLine("In Range!!!");
			playTone(1500,5);
		}

		clearLCDLine(1);

		string line;
		stringFormat(line,"L:%3.1f P:%2.1f",shootingController.lastError,shootingController.power);

		displayLCDString(1,0,line);
		sleep(50);
	}
	WaitTillButtonsRelease();
	SetShortShoot();
}
void Calibrate(){
	displayLCDCenteredString(1,"Push To Start");
	if(nLCDButtons == kButtonRight || nLCDButtons == kButtonLeft){
		holdMainTask = true;
		WaitTillButtonsRelease();
		CalibrateAction();
		WaitTillButtonsRelease();
		holdMainTask = false;
	}
}
