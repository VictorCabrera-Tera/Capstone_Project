#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!(input->buttons[b].is_down) && input->buttons[b].changed)


float player_posX = 0.f;
float player_posY = 0.f;
float player_posX2 = 100.f;
float player_posY2 = 500.f;
bool vacancy = true;


float speed = 50.f; //unit per second
internal void
simulate_game(Input* input, float dt) {

  clear_screen(0xFF5500);


  // unit / second * second/ frame = unit / frame
  if (is_down(BUTTON_UP)) {
	player_posY += speed * dt;
	player_posY2 += speed * dt;

  }
  if (is_down(BUTTON_DOWN)) {
	player_posY -= speed * dt;
	player_posY2 -= speed + dt;
  }
  if (is_down(BUTTON_LEFT)) {
	player_posX -= speed * dt;
	player_posX2 -= speed * dt;
  }
  if (is_down(BUTTON_RIGHT)) {
	player_posX += speed*dt;
	player_posX2 += speed*dt;

  }
  if (is_down(BUTTON_SPACEBAR)) speed += 0.01;
  
  //draw_right_tri(50, 60, -30, 0x00ffff);
  //draw_rect(player_posX, player_posY, 1, 1, 0x00ff22, vacancy);
  //if (!vacancy) {
	//draw_rect(0, 0, 1, 1, 0x00ff22, vacancy);
	//player_posX = 0;
	//player_posY = 0;
  //}
  //draw_rect(30, 30, 5, 5, 0x00ff22);
  //draw_rect(-20, 20, 8, 3, 0x00ff22);
 
  draw_enemy(player_posX+8, player_posY+200, player_posX2+8, player_posY2+20, 0x00ff22);
  //draw_tri(player_posX, player_posY, player_posX2, (player_posY+200), 0x00ff22);

}