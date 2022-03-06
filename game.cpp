#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!(input->buttons[b].is_down) && input->buttons[b].changed)

#define coin(c,x_y_wid_hei_coll) coins->coin[c].x_y_wid_hei_coll



float player_posX = 0.f;
float player_posY = 0.f;
float player_posX2 = 100.f;
float player_posY2 = 500.f;

//Needed to keep track of previous pos for collision
float old_X;
float old_Y;
float old_X2;
float old_Y2;

bool vacancy = true;


u32 background = BLACK;
int timer = 0;
COLORDIRECTION direction = INCREMENT;
u32 color = 0x000001;

u32 color1 = RED;
u32 color2 = BLACK;
u32 color3 = BLACK;

bool coins_set = false;

internal void
restart_pos() {
  //draw_rect(0, 0, 1, 1, 0x00ff22);
  player_posX = 0;
  player_posY = 0;
}



internal void
modify_color_up(u32 &color, u32 increment, u32 end, COLORDIRECTION &direction) {
  if (direction == INCREMENT)
  {
	if (color < end) {
		color += increment;
	}
	if (color == end) {
	  direction = DECREMENT;
	}
  }
}

internal void
modify_color_down(u32 &color, u32 increment, u32 end, COLORDIRECTION& direction) {
  if (direction == DECREMENT) {
	if (color != end) {
		color -= increment;
	}
	else if (color == end) {
	  direction = INCREMENT;
	}
 }
}


internal void 
collision(Coin_State* coins) {

  draw_rect(player_posX, player_posY, 4, 4, 0x00ff22, vacancy, coins);
  if (!vacancy) {
	//restart_pos();
	player_posX = old_X;
	player_posX2 = old_X2;
	player_posY = old_Y;
	player_posY2 = old_Y2;
	draw_rect(player_posX, player_posY, 4, 4, 0x00ff22);
  }
}



internal void
setCoins(Coin_State* coins, u32 coin1, u32 coin2, u32 coin3) {
  for (int i = 0; i < AMOUNT; i++) {
	coins->coin[i].collected = false;
  }
  coins->coin[0].color = coin1;
  coins->coin[1].color = coin2;
  coins->coin[2].color = coin3;
  coins_set = true;
}

internal void
Level1Coins(Coin_State* coins) {
  

  if (coin(0, collected) == false) {
	draw_coin(-10, -10, 6, 6, coins->coin[0].color);
	draw_coin(-85, 49, 3, 1, WHITE);
  }
  else if (coin(0, collected) == true) {
	draw_coin(-85, 49, 3, 1, coins->coin[0].color);
  }


  if (coin(1, collected) == false) {
	draw_coin(10, 10, 6, 6, coins->coin[1].color);
	draw_coin(-80, 49, 3, 1, WHITE);
  }
  else if (coin(1, collected) == true) {
	draw_coin(-80, 49, 3, 1, coins->coin[1].color);
  }

  if (coin(2, collected) == false) {
	draw_coin(30, 30, 6, 6, coins->coin[2].color);
	draw_coin(-75, 49, 3, 1, WHITE);
  }
  else if (coin(2, collected) == true) {
	draw_coin(-75, 49, 3, 1, coins->coin[2].color);
  }

}

enum GAMEMODE {
  MAINMENU,
  LEVELSELECT,
  LEVEL1,
  LEVEL2,
  LEVEL3,
};

GAMEMODE options = MAINMENU;
int helper = 1;

float speed = 50.f; //unit per second
internal void
simulate_game(Input* input, float dt, Coin_State* coins) {
  
  clear_screen(BLACK);
  draw_rect(0, 0, 90, 45, WHITE);
  if (coins_set == false) {
	setCoins(coins, 0xFFD800, 0xFFD900,0xFFDA00);
  }
  if (options == LEVEL1) {
	//color = 0x0000AA * dt;
  //modify_color_up(background, color, BLUE, direction);
  //modify_color_down(background, color, BLACK, direction);
  /*
  if (timer > 10) {
	switch (direction) {
	case (INCREMENT):
	  //color = 0x0000FF *dt;
	  modify_color_up(background, color, BLUE, direction);
	  break;
	case(DECREMENT):
	  //color = 0x0000FF * dt;
	  modify_color_down(background, color, BLACK, direction);
	  break;
	}
	timer = 0;
  }
  else {
	timer +=1;
  }
  */



	// unit / second * second/ frame = unit / frame
	if (is_down(BUTTON_UP)) {
	  //Maintain the original position
	  old_Y = player_posY;
	  old_Y2 = player_posY2;

	  player_posY += speed * dt;
	  player_posY2 += speed * dt;

	}
	if (is_down(BUTTON_DOWN)) {
	  old_Y = player_posY;
	  old_Y2 = player_posY2;

	  player_posY -= speed * dt;
	  player_posY2 -= speed + dt;
	}
	if (is_down(BUTTON_LEFT)) {

	  old_X = player_posX;
	  old_X2 = player_posX2;

	  player_posX -= speed * dt;
	  player_posX2 -= speed * dt;
	}
	if (is_down(BUTTON_RIGHT)) {

	  old_X = player_posX;
	  old_X2 = player_posX2;

	  player_posX += speed * dt;
	  player_posX2 += speed * dt;

	}
	if (pressed(BUTTON_SPACEBAR)) {
	  speed += 10.50;
	}
	if released(BUTTON_SPACEBAR) 	PlaySound(L"C:\\Users\\steve\\Desktop\\My_First_Cpp_Game\\My_First_Cpp_Game\\Satorl_Marsh2.wav", 0, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);


	//draw_right_tri(85, -45, 5, 0x00ffff);
	//draw_rect(30, 30, 5, 5, 0xffff22, vacancy);

	//draw_tri(-65, 25, 10, 8, YELLOW);

	Level1Coins(coins);


	//The player
	collision(coins);


	//draw_ticket(player_posX, player_posY, 6, 8, YELLOW);


	//draw_rect(-20, 20, 8, 3, 0x00ff22, vacancy);

	//draw_enemy(266, 615, 386, player_posY2, 0x00ff22);
	//draw_tri(player_posX, player_posY, player_posX2, (player_posY+200), 0x00ff22);
	//draw_coin(-85, 49, 3, 1, YELLOW);
  }
  else if (options == MAINMENU) {
	
	draw_rect(0, 0, 90, 45, BLUE);
	u32 temp;
	//draw_rect()
	if (pressed(BUTTON_LEFT)) {
	  temp = color1;
	  color1 = RED;
	  color2 = BLACK;
	}
	if (pressed(BUTTON_RIGHT)) {
	  temp = color1;
	  color1 = BLACK;
	  color2 = RED;


	}
	if (pressed(BUTTON_ENTER)) {
	  if (color1 == RED) {
		options = LEVEL1;

	  }
	  else {
		options = LEVELSELECT;

		color1 = RED;
		color2 = BLACK;
	  }
	}
	draw_rect(-20, 0, 1, 10, color1);
	draw_rect(-20, -10, 10, 1, color1);
	draw_rect(-24, 10,5, 1, color1);

	

	draw_rect(10, 10, 1, 3, color2);
	{
	  draw_rect(13, 10, 1, 1, color2);
	  draw_rect(16, 10, 1, 1, color2);
	  draw_rect(19, 10, 1, 1, color2);
	}
	draw_rect(10, 0, 1, 3, color2);
	{
	  draw_rect(13, 0, 1, 1, color2);
	  draw_rect(16, 0, 1, 1, color2);
	  draw_rect(19, 0, 1, 1, color2);
	}
	draw_rect(10, -10, 1, 3, color2);
	{
	  draw_rect(13, -10, 1, 1, color2);
	  draw_rect(16, -10, 1, 1, color2);
	  draw_rect(19, -10, 1, 1, color2);
	}


  }
  else if (options == LEVELSELECT) {


  if (pressed(BUTTON_DOWN)) {
	helper++;
	if (helper > 3) {
	  helper = 1;
	}
  }

  if (pressed(BUTTON_UP)) {
	helper--;
	if (helper < 1) {
	  helper = 3;
	}
  }
  switch (helper) {
  case(1):
	color1 = RED;
	color2 = BLACK;
	color3 = BLACK;
	break;
  case(2):
	color1 = BLACK;
	color2 = RED;
	color3 = BLACK;
	break;
  case(3):
	color1 = BLACK;
	color2 = BLACK;
	color3 = RED;
	break;
  }
  draw_rect(0, 20, 2, 5, color1);

  draw_rect(-10, 0, 2, 5, color2);
  draw_rect(10, 0, 2, 5, color2);

  draw_rect(0, -20, 2, 5, color3);
  draw_rect(20, -20, 2, 5, color3);
  draw_rect(-20, -20, 2, 5, color3);


  if (pressed(BUTTON_ENTER)) {
	if (helper == 1) {
	  options = LEVEL1;
	}
	else  if (helper == 2) {
	  options = LEVEL2;
	}
	else {
	  options = LEVEL3;
	}
  }
}

  else if (options == LEVEL2) {
	draw_rect(0, 0, 80, 20, RED);
  }
  else if (options == LEVEL3) {
	draw_rect(0, 0, 80, 20, BLUE);
  }
}