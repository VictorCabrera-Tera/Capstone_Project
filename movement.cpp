

//the only variable you would change here would be int max, changing int max would increase the amount of time it moves in one direction NOT speed
//create variables outside of simulate game, for example
//int delta = 1; ,NEED & in front 
//int count = 0; ,NEED & in front
//int max = 10;
//int min = 0;
/*
internal void
run_loop(int* delta, int* count, int max, int min) {
  *count += *delta;
  if (*count == min || *count == max) {
	*delta = -*delta;
  }
}
*/
//enemy1_posX = x variable of what you want to move, NEED & IN FRONT OF VARIABLE
// delta= delta variable, set it to 0 if you want it to move left first, set it to 1 if you want it to move right first, NEED & IN FRONT OF VARIABLE
// dt =dt , just write dt 
// speed can be any number, represents how fast you want it to move
// stop1 is the lower of the 2 values, stop 2 is the higher of two values
internal void
move_sideways(float *enemy1_posX, int *delta, float dt, float speed,float stop1 , float stop2) {
	if (stop2 < *enemy1_posX) {
		*delta = 0;
	}
	if (stop1 > *enemy1_posX) {
		*delta = 1;
	}
	if ((*delta == 1)) {
		*enemy1_posX += speed * dt;
	}
	if ((*delta == 0)) {
		*enemy1_posX -= speed * dt;
	}
}

internal void
move_vertical(float* enemy1_posY, int* delta, float dt, float speed, float stop1, float stop2) {
	if (stop2 < *enemy1_posY) {
		*delta = 0;
	}
	if (stop1 > *enemy1_posY) {
		*delta = 1;
	}
	if ((*delta == 1)) {
		*enemy1_posY += speed * dt;
	}
	if ((*delta == 0)) {
		*enemy1_posY -= speed * dt;
	}


}
// for stop 1 and stop2 , X position is assumed.
internal void
move_diagonal_tl(float* enemy1_posX, float* enemy1_posY, int* delta, float dt, float speed, float stop1, float stop2) {
	if (stop2 < *enemy1_posX) {
		*delta = 0;
	}
	if (stop1 > *enemy1_posX) {
		*delta = 1;
	}
	if (*delta == 1) {
		*enemy1_posX += speed * dt;
		*enemy1_posY += speed * dt;
	}
	if (*delta == 0) {
		*enemy1_posX -= speed * dt;
		*enemy1_posY -= speed * dt;
	}
}
// for stop 1 and stop2 , X position is assumed.
internal void
move_diagonal_bl(float* enemy1_posX, float* enemy1_posY, int* delta, float dt, float speed, float stop1, float stop2) {
	if (stop2 < *enemy1_posX) {
		*delta = 0;
	}
	if (stop1 > *enemy1_posX) {
		*delta = 1;
	}
	if (*delta == 1) {
		*enemy1_posX += speed * dt;
		*enemy1_posY -= speed * dt;
	}
	if (*delta == 0) {
		*enemy1_posX -= speed * dt;
		*enemy1_posY += speed * dt;
	}
}
