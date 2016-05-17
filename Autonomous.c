#include "Autonomous/AutonomousLibrary.h"


void autonomousFunc(){
    gyroPidConfig.p = 0.3;
    gyroPidConfig.i = 0.04;
    gyroPidConfig.d = 8;


    switch (path) {
        case 1:
            path1();
            break;
        case 2:
            path2();
            break;
        case 3:
            path3();
            break;
    }
    allMotorsOff();
}
task autonomous () {
    autonomousFunc();
}



void AutonomousControl(){
    if(SensorValue[AutoLaunch]){
        autonomousFunc();
    }
}
