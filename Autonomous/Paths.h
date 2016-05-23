void path1(){
	//Shoot the balls first,then push balls.
	shootBalls = false;
	SetLongShoot();
	FieldBasedSetMotor(-127,-127);
	AutonomousShooting(1,false);
	FieldBasedSetMotor(-50,-50);
	AutonomousShooting(0.5,false);
	FieldBasedSetMotor(0,0);
	AutonomousShooting(0.05,false);
	FieldBasedSetMotor(10,10);
	AutonomousShooting(0.05,false);
	FieldBasedSetMotor(0,0);
	AutonomousShooting(1,true);
	ShootingBrake();
	StartGettingBalls();
	//Balls are in the net now.

	FieldBasedTurn(0.26,60);
	FieldBasedSetMotor(40,127);
	sleep(800);
	forward(0.6,seconds,60);
	FieldBasedSetMotor(-30,127);
	sleep(320);
	forward(0.3,seconds,100);
	forward(1.2,seconds,40);
	StartLosingBalls();
	sleep(1500);
	StopGettingBalls();
	//Balls are in the launch area now.

	backward(0.70,seconds,80);
	FieldBasedTurn(0.3,-60);
	backward(0.5,seconds,50);

	StartGettingBalls();
	ForwardWithBrake(1,seconds,70);
	FieldBasedSetMotor(-127,127);
	sleep(200);
	backward(0.5,seconds,80);
}

void path2(){
	//Push the balls close to the player standing area.
	//FieldBasedTurn(0.03,100);
	backward(0.90,seconds,100);
	FieldBasedTurn(0.24,-100);//if red, minus means turn right
	FieldBasedSetMotor(127,50);//right, left
	sleep(1050);
	FieldBasedSetMotor(127,-30);
	sleep(390);
	forward(1.5,seconds,40);

	//Balls are in the launch area now.

	FieldBasedSetMotor(-127,-30);
	sleep(800);


	FieldBasedTurn(1,40);
	forward(1.5,seconds,100);
}

void path3(){
	//Prevent other robots from going out
	SetLongShoot();
	AutonomousShooting(3.5);
	if(gameField == FieldBlueBack || gameField == FieldRedBack){
		FieldBasedTurn(0.13,100);//Back Field
		BackwardWithBrake(2,seconds,100);
	}
	else{
		FieldBasedTurn(0.2,100);//Front Field
		BackwardWithBrake(2.5,seconds,100);
	}


}
