#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!(input->buttons[b].is_down) && input->buttons[b].changed)

#define coin(c,x_y_wid_hei_coll) coins->coin[c].x_y_wid_hei_coll

#include "game_global_variables.cpp"


internal void
restart_pos() {
	//draw_rect(0, 0, 1, 1, 0x00ff22);
	player_posX = 0;
	player_posY = 0;
}


internal void
collision(Coin_State* coins, float dt) {
	/*
	draw_rect(player_posX, player_posY, 4, 4, 0x00ff22, vacancy,bottom,left,right,top, coins);

	if (bottom == FALSE) {
		yvelocity = 0;

	}
	else {
		yvelocity += accel * dt;

	}
	if (left == FALSE) {
		leftclear = TRUE;
		draw_tri(enemy_x, enemy_y, 10, 10, RED);
		yvelocity += accel * dt;
	}
	else {
		leftclear = false;

	}
	if (right == FALSE) {
		rightclear = TRUE;
		yvelocity += accel * dt;
	}
	else {
		rightclear = FALSE;

	}
	if (!vacancy) {
		//restart_pos();;
		player_posX = old_X;
		player_posY = old_Y;
		draw_rect(player_posX, player_posY, 4, 4, 0x00ff22)

		/*
		if (top = TRUE) {
			//n
		}
		else {
			//n
		}

		//xvelocity = 0;
;
	}
	else {
		yvelocity += accel * dt;
	}
	*/

	draw_rect(player_posX, player_posY, 2, 2, GREEN, vacancy, bottom, left, right, top, enemy_touched, coins);
	if (!vacancy) {
		if (enemy_touched){
		  enemy_touched = false;
		  restart_pos();
		}
		else {


		  clear = false;

		  if (bottom == false) {
			yvelocity = 0;
		  }
		  if (left == false) {
			leftclear = false;
			xvelocity = 0;
		  }
		  else {
			leftclear = true;
		  }
		  if (right == false) {
			rightclear = false;
			xvelocity = 0;
		  }
		  else {
			rightclear = true;
		  }

		  if (top == false) {
			yvelocity = 0;
		  }
		  //xvelocity = 0;
		  player_posX = old_X;
		  player_posX2 = old_X2;
		  player_posY = old_Y;
		  player_posY2 = old_Y2;
		  draw_rect(player_posX, player_posY, 2, 2, GREEN);
		}
	}
	else {
		clear = true;
		yvelocity += accel * dt;

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
	int collected_coins = 0;
	static int cc = 0;
	mciSendString(L"open ..\\sound\\coin.wav type waveaudio alias coin", NULL, 0, 0);
	
	if (coin(0, collected) == false) {
	  draw_circle(-39, -36, 3, coins->coin[0].color);
	  draw_circle(-69, 48, 2, WHITE);
	}
	else if (coin(0, collected) == true) {
	  draw_circle(-69, 48, 2, coins->coin[0].color);
	  collected_coins++;
	}


	if (coin(1, collected) == false) {
	  draw_circle(-76, -12, 3, coins->coin[1].color);
	  draw_circle(-65, 48, 2, WHITE);
	}
	else if (coin(1, collected) == true) {
	  draw_circle(-65, 48, 2, coins->coin[1].color);
	  collected_coins++;
	}

	if (coin(2, collected) == false) {
	  draw_circle(30, 30, 3, coins->coin[2].color);
	  draw_circle(-61, 48, 2, WHITE);
	}
	else if (coin(2, collected) == true) {
	  draw_circle(-61, 48, 2, coins->coin[2].color);
	  collected_coins++;
	}

	//beeps once when coin is collected
	if (collected_coins != cc) {
	  mciSendString(L"play coin from 1", NULL, 0, 0);
	  cc = collected_coins;
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
int selected = 1;

float speed = 50.f; //unit per second



internal void
simulate_game(Input* input, float &dt, Coin_State* coins, HWND window) {

	clear_screen(RED);
	draw_rect(0, 0, 90, 45, WHITE);


	if (coins_set == false) {
		setCoins(coins, 0xFFD800, 0xFFD900, 0xFFDA00);
	}
	if (options == LEVEL1) {

		printLevelText("Level 1", -10, 49, WHITE);
		printLevelText("Lives ", 50, 49, WHITE);
		printLevelText("Coins ", -90, 49, WHITE);
		//start of pause stuff
		if (pause_count == 2 && pause == true)
		{
			pause = false;
			pause_count = pause_count - 2;
			
		}
		if (pause == true) {
		  printMenuPhrase("Pause", -43, 25, 13, false, ticket, BLUE);
		  temp += 1;
		  temp2 = temp * dt;
		}
			

		//if (pressed(BUTTON_ESCAPE) && pause == true)
		//	pause = false;
		/*
		if (pressed(BUTTON_ESCAPE))
		{
			pause_count++;
			if (pause == false)
			{
				pause = true;
			}	
		}*/
		if (pause == true)
		{
			mciSendString(L"pause bgm", NULL, 0, 0);
		}
		if (pause == false)
		{
			mciSendString(L"resume bgm", NULL, 0, 0);
		}
		//end of pause stuff

		// unit / second * second/ frame = unit / frame

		if (leftclear == true) {
			if (is_down(BUTTON_LEFT) && pause == false) {
				//player_posX -= speed * dt;
				xvelocity = -20;

				/*
				if (xvelocity > 0) {
					xvelocity -= 200 * dt;
				}
				xvelocity -= 100 * dt;
				if (xvelocity < -250) {
					xvelocity = -250;
				}
				*/
			}
		}

		if (released(BUTTON_LEFT)) {
			xvelocity = 0;

		}

		if (rightclear == true) {
			if (is_down(BUTTON_RIGHT) && pause == false) { // 
				//player_posX += speed * dt;
				xvelocity = 20;
				/*
				if (xvelocity < 0) {
					xvelocity += 200 * dt;
				}

				xvelocity += 100 * dt;
				if (xvelocity > 250) {
					xvelocity = 250;
				}
				*/
			}
		}

		if (released(BUTTON_RIGHT)) {
			xvelocity = 0;

		}

		if (pressed(BUTTON_SPACEBAR) && pause == false) 
		{
			//player_posY += speed * dt;
			yvelocity -= 3000 * dt;
			
		}
		
		old_Y = player_posY;
		old_X = player_posX;
		
		if (pause == false)
		{
			player_posY -= yvelocity * dt;
			player_posX += xvelocity * dt;
			yvelocity += accel * dt;
		}



		if (pause == false) {
			
			run_loop(&delta, &count, max, min);
			move_vertical(&enemy_y, delta, dt, 8);
			
			run_loop(&delta2, &count2, max2, min2);
			move_sideways(&enemy_x2, delta2, dt, 20);
			//move_sideways(&enemy_x, delta, dt, 20);
			//move_vertical(&enemy_y, delta, dt, 20);
			//move_diagonal_tl(&enemy_x, &enemy_y, delta, dt, 20);	
		}

		draw_rect(82, -38, 8, 8, RED); //fills in lower right corner

		draw_rect(-69, -44, 5, 1, RED); //bump1

		draw_rect(-40, -41, 15, 1, RED); //plat1

		draw_right_tri(2.2, -44.9, 2.8, RED); //little ledge next to stairs
		draw_rect(45, -42, 40, 3, RED); //stairs
		draw_rect(55, -37, 20, 2, RED);
		draw_rect(65, -33, 20, 2, RED);
		draw_rect(75, -29, 20, 2, RED);

		draw_rect(19, -28, 8, 0.5, RED); //plat2



		draw_rect(-44, -20, 35, 0.8, RED); //plat3
		draw_rect(-1, -22, 5, 0.5, RED);

		draw_rect(-76, -17, 3, 2.3, RED); //bump2


		draw_rect(-53, -9, 11, 0.2, RED); //platform 4
		draw_rect(-51, -8.3, 9, 0.5, RED);
		draw_right_tri(-51, -8.1, 9, RED);

		draw_rect(-38, 35, 4, 10, RED); //wall
		draw_rect(-38, 2, 4, 8, RED); //wall

		draw_diamond(enemy_x, enemy_y, 3, 3, BLUE); //enemy 1

		draw_rect(30, 12, 50, 1, RED); //last platform
		draw_coin(30, 32, 30, 20, RED); //the red hexagon platform

		draw_coin(enemy_x2, enemy_y2, 5, 5, BLUE); //enemy 2

		//draw_heart(6, 6, 1, GREEN);

		Level1Coins(coins);
		collision(coins, dt);

	}
	else if (options == MAINMENU) {
		
		if (pause == false) 
		{
			mciSendString(L"open ..\\sound\\Satorl_Marsh2.wav type waveaudio alias bgm", NULL, 0, 0);
			mciSendString(L"play bgm", NULL, 0, 0);
		}	
		

		draw_rect(0, 0, 90, 45, BLUE);
		printMenuPhrase("Main Menu", -43, 25, 13, true, ticket, GREEN);
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
		if (color1 == RED) {
		  printMenuPhrase("Start-Level", -50, -20, 6, false, square, RED);
		}
		draw_rect(-20, 0, 1, 10, color1); //left side
		draw_rect(-20, -10, 10, 1, color1);
		draw_rect(-24, 10, 5, 1, color1);

		if (color2 == RED) {
		  printMenuPhrase("Level-Select", -50, -20, 6, false, square, RED);
		}

		draw_rect(10, 10, 1, 3, color2); //Right side
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

		printMenuPhrase("Pick-A-Level", -48, 40, 6, false, square, RED);

		if (pressed(BUTTON_DOWN)) {
			selected++;
			if (selected > 3) {
			  selected = 1;
			}
		}

		if (pressed(BUTTON_UP)) {
		  selected--;
			if (selected < 1) {
			  selected = 3;
			}
		}
		switch (selected) {
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
			if (selected == 1) {
				options = LEVEL1;
			}
			else  if (selected == 2) {
				options = LEVEL2;
			}
			else {
				options = LEVEL3;
			}
		}
	}
	else if (options == LEVEL2) {
	  printLevelText("Level 2", -10, 49, WHITE);
	  printLevelText("Lives ", 50, 49, WHITE);
	  printLevelText("Coins ", -90, 49, WHITE);
	  draw_rect(0, 0, 80, 20, RED);
	}
	else if (options == LEVEL3) {
	  printLevelText("Level 3", -10, 49, WHITE);
	  printLevelText("Lives ", 50, 49, WHITE);
	  printLevelText("Coins ", -90, 49, WHITE);
	  draw_rect(0, 0, 80, 20, BLUE);
	}
}
