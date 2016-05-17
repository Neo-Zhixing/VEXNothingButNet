#pragma config(I2C_Usage, I2C1, i2cSensors)

#pragma config(Sensor, dgtl2,  ShootingEncoderLeft,        sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  ShootingEncoderRight,        sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  AutoLaunch, sensorTouch)

#pragma config(Sensor, in1,    Gyro,            sensorGyro)
#pragma config(Sensor, in2,    PowerExpander,   sensorAnalog)


#pragma config(Motor,  port1,  CarringBalls,         tmotorVex393TurboSpeed_HBridge,  openLoop, reversed                    )
#pragma config(Motor,  port2,  ChassisLeftFront,     tmotorVex393TurboSpeed_MC29,     openLoop,           driveLeft         )
#pragma config(Motor,  port8,  ChassisRightFront,    tmotorVex393TurboSpeed_MC29,     openLoop, reversed, driveRight        )
#pragma config(Motor,  port3,  ChassisLeftBack,      tmotorVex393TurboSpeed_MC29,     openLoop,           driveLeft         )
#pragma config(Motor,  port9,  ChassisRightBack,     tmotorVex393TurboSpeed_MC29,     openLoop, reversed, driveRight        )
#pragma config(Motor,  port6,  ShootingLeft,         tmotorVex393HighSpeed_MC29,      openLoop, reversed)
#pragma config(Motor,  port7,  ExtendShootingLeft,   tmotorVex393HighSpeed_MC29,      openLoop                              )
#pragma config(Motor,  port4,  ShootingRight,        tmotorVex393HighSpeed_MC29,      openLoop)
#pragma config(Motor,  port5,  ExtendShootingRight,  tmotorVex393HighSpeed_MC29,      openLoop, reversed                    )
#pragma config(Motor,  port10, GettingBalls,         tmotorVex393TurboSpeed_HBridge,  openLoop, reversed                    )