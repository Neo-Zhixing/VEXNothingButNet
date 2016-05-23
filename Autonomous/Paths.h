void path1(){
	//Shoot the balls first,then push balls.
	SetLongShoot();
	FieldBasedSetMotor(-127,-127);
	AutonomousShooting(1,false);
	FieldBasedSetMotor(-30,-30);
	AutonomousShooting(0.1,false);
	FieldBasedSetMotor(0,0);
	AutonomousShooting(1,true);
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
