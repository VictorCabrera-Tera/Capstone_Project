

//the only variable you would change here would be int max, changing int max would increase the amount of time it moves in one direction NOT speed
//create variables outside of simulate game, for example
//int delta = 1; ,NEED & in front 
//int count = 0; ,NEED & in front
//int max = 10;
//int min = 0;
internal void
run_loop(int* delta, int* count, int max, int min) {
  *count += *delta;
  if (*count == min || *count == max) {
	*delta = -*delta;
  }
}

//enemy1_posX = x variable of what you want to move, NEED & IN FRONT OF VARIABLE
// delta= delta, write the name of the looprun delta you are using , NEED & IN FRONT OF VARIABLE
// dt =dt , just write dt 
// speed can be any number, represents how fast you want it to move
internal void
move_sideways(float* enemy1_posX, int delta, float dt, float speed) {
  if (delta == 1) {
	*enemy1_posX += speed * 0.01666;
  }
  if (delta == -1) {
	*enemy1_posX -= speed * 0.01666;
  }
}

internal void
move_vertical(float* enemy1_posY, int delta, float dt, float speed) {
  if (delta == 1) {
	*enemy1_posY += speed * 0.01666;
  }
  if (delta == -1) {
	*enemy1_posY -= speed * 0.01666;
  }
}

internal void
move_diagonal_br(float* enemy1_posX, float* enemy1_posY, int delta, float dt, float speed) {
  if (delta == 1) {
	*enemy1_posX += speed * 0.01666;
	*enemy1_posY -= speed * 0.01666;
  }
  if (delta == -1) {
	*enemy1_posX -= speed * 0.01666;
	*enemy1_posY += speed * 0.01666;
  }
}
internal void
move_diagonal_bl(float* enemy1_posX, float* enemy1_posY, int delta, float dt, float speed) {
  if (delta == 1) {
	*enemy1_posX -= speed * 0.01666;
	*enemy1_posY -= speed * 0.01666;
  }
  if (delta == -1) {
	*enemy1_posX += speed * 0.01666;
	*enemy1_posY += speed * 0.01666;
  }
}
internal void
move_diagonal_tl(float* enemy1_posX, float* enemy1_posY, int delta, float dt, float speed) {
  if (delta == 1) {
	*enemy1_posX -= speed * 0.01666;
	*enemy1_posY += speed * 0.01666;
  }
  if (delta == -1) {
	*enemy1_posX += speed * 0.01666;
	*enemy1_posY -= speed * 0.01666;
  }
}
