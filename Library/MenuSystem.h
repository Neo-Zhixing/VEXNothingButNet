/*
------------------------------
|       Current State        |
|         Infomation         |
------------------------------
Value-   Change State   Value+

*/
bool displayMenu = true;
enum MenuState{
	MenuBattery,MenuAutoPath,MenuAutoPos,MenuCalibrate,MenuGyro
};
const unsigned short MenuStateCount = 5;
MenuState menuState = MenuBattery;
void PrintMenuStateName(){
	string str;
	switch(menuState){
		case MenuBattery:
		str = "Battery";
		break;

		case MenuAutoPath:
		str = "Auto Path";
		break;

		case MenuAutoPos:
		str = "Auto Position";
		break;

		case MenuCalibrate:
		str = "Calibrate";
        break;

        case MenuGyro:
        str = "Gyro";
        break;
	}
	displayLCDCenteredString(0,str);
}
void WaitTillButtonsRelease(){
	while(nLCDButtons != kButtonNone){

	}
}
void BatteryCheck(){
	float mainLevel = nAvgBatteryLevel/1000.0; //main battery level
	float backupLevel = BackupBatteryLevel/1000.0; //backup battery level
	float secondLevel = ((float)SensorValue[PowerExpander]/280); //power expander battery level
	string line;
	stringFormat(line,"M%1.1f P%1.1f B%1.1f",mainLevel,secondLevel,backupLevel);
	displayLCDString(1,0,line);
}
void AutoPos(){
    if(nLCDButtons == kButtonRight){
        if(gameField == FieldRedFront) gameField = FieldBlueFront;
        else gameField ++;
        WaitTillButtonsRelease();
    }
    else if(nLCDButtons == kButtonLeft){
        if(gameField == FieldBlueFront) gameField = FieldRedFront;
        else gameField --;
        WaitTillButtonsRelease();
    }

    string str;
    switch (gameField) {
        case FieldBlueFront:
            str = "FieldBlueFront";
            break;
        case FieldBlueBack:
            str = "FieldBlueBack";
            break;
        case FieldRedFront:
            str = "FieldRedFront";
            break;
        case FieldRedBack:
            str = "FieldRedBack";
            break;
    }
    displayLCDCenteredString(1,str);
}


const unsigned short pathCount = 3;
unsigned short path = 1;

void AutoPath(){
    if(nLCDButtons == kButtonRight){
        if(path >= pathCount) path = 1;
        else path++;
        WaitTillButtonsRelease();
    }
    else if(nLCDButtons == kButtonLeft){
        if(path <= 1) path = pathCount;
        else path--;
        WaitTillButtonsRelease();
    }

    string str;
    switch (path) {
        case 1:
            str = "1 PushSideNoShoot";
            break;
        case 2:
            str = "2 PushBackNoShoot";
            break;
        case 3:
            str = "Path3:Prevent Out";
            break;
    }
    displayLCDCenteredString(1,str);
}
#include "Shooting/Calibrate.h"
void GyroTest(){
    string str;
    stringFormat(str,"%d",SensorValue[Gyro]);
    displayLCDCenteredString(1,str);
}
task MenuSystem(){
    while(1){
    	if(!displayMenu) continue;
        if(nLCDButtons == kButtonCenter){
            menuState++;
            if(menuState >= MenuStateCount) menuState = MenuBattery;
            WaitTillButtonsRelease();
        }
        PrintMenuStateName();
        switch(menuState){
            case MenuBattery:
                BatteryCheck();
                break;
            case MenuAutoPos:
                AutoPos();
                break;
            case MenuAutoPath:
                AutoPath();
                break;
            case MenuCalibrate:
                Calibrate();
                break;
            case MenuGyro:
                GyroTest();
                break;
        }
        sleep(50);
    }
}
