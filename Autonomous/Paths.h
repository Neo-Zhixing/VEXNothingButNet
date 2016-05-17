void path1(){
	SetLongShoot();
	AutonomousShooting(3.5);
	ShootingBrake();
	FieldBasedTurn(0.2,-100);
	backward(0.95,seconds,100);
	FieldBasedTurn(0.32,100);

	StartGettingBalls();
	forward(0.8,seconds,40);
	backward(0.3,seconds,30);
	forward(0.8,seconds,30);
	sleep(300);
	StopGettingBalls();

	backward(0.2,seconds,50);
	FieldBasedTurn(0.4,-100);
	FieldBasedTurn(0.05,50);

	StartLosingBalls();
	sleep(1000);
	StopGettingBalls();

	FieldBasedTurn(0.4,100);
	forward(0.5,seconds,40);

	BackwardWithBrake(1.1,seconds,100);
	FieldBasedSetMotor(40,-127);
	sleep(900);

	backward(1,seconds,100);
	sleep(1000);
	StartGettingBalls();
	forward(4,seconds,50);
}

void path2(){
	//Get the balls close to the player standing area.
	SetLongShoot();
	AutonomousShooting(3.5);
	ShootingBrake();
	FieldBasedTurn(0.02,100);
	backward(1.4,seconds,100);
	FieldBasedTurn(0.2,-100);


	//Point to the balls
	StartGettingBalls();
	forward(2,seconds,50);
	backward(0.5,seconds,50);
	forward(1,seconds,60);
	sleep(300);
	backward(1.5,seconds,90);
	StopGettingBalls();

	FieldBasedTurn(0.25,80);
	StartGettingBalls();
	forward(1,seconds,100);
	StopGettingBalls();
	backward(1,seconds,100);
	SetShortShoot();
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
