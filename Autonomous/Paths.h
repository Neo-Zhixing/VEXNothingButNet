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
	backward(0.95,seconds,100);
	FieldBasedTurn(0.17,-100);//if red, minus means turn right
	forward(0.32,seconds,100);
	FieldBasedSetMotor(127,50);//right, left
	sleep(470);
	FieldBasedSetMotor(127,-30);
	sleep(455);
	forward(1,seconds,50);
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
