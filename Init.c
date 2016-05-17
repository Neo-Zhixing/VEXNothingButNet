#include "Library/Shooting/MotorSpeedController.h"
#include "Library/Motor.h"
task MenuSystem();
bool holdMainTask = false;
void pre_auton()
{
	bLCDBacklight = true;
	nGlobalJoyScaledValue *= 2;
	ShootingInit();
    startTask(MenuSystem);
}