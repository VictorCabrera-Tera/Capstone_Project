//@Param input so I can use the macros for the keys instead of doing it the long way
//press escape or enter on resume to unpause
//press enter on resume to quit to desktop
static void
pauseMenu(Input* input)
{
  //pause_selected's value will alter the colors for the words 
  if (pressed(BUTTON_DOWN)) {
	pause_selected++;
	if (pause_selected > 3) {
	  pause_selected = 1;
	}
  }
  if (pressed(BUTTON_UP)) {
	pause_selected--;
	if (pause_selected < 1) {
	  pause_selected = 3;
	}
  }
  switch (pause_selected) {
  case(1):
	P_color = RED;
	P_color1 = YELLOW;
	P_color2 = YELLOW;
	break;
  case(2):
	P_color = YELLOW;
	P_color1 = RED;
	P_color2 = YELLOW;
	break;
  case(3):
	P_color = YELLOW;
	P_color1 = YELLOW;
	P_color2 = RED;
	break;
  }

  if (pressed(BUTTON_ENTER)) { //selected an option in the pause menu
	if (pause_selected == 1) { //selected to resume the game
	  game_info.pause = !game_info.pause;
	}
	else  if (pause_selected == 2) { //selected to go to the main menu
	  game_info.pause = !game_info.pause;
	  options = MAINMENU;
	  levelInfoSet = false; //so u don't start at the same spot u we're on the level 
	  game_info.started_level = false;  //so u can't pause on the main menu
	  player_sizex = 2;
	  player_sizey = 2;
	  health_points = 3;
	  heart_collected = false;
	}
	else { //chose to quit the game
	  running = false; //closes the windows interface
	}
  }
  draw_rect(0, 0, 41, 31, YELLOW);
  draw_rect(0, 0, 40, 30, BLACK);
  printMenuPhrase("Resume", -30, 20, 10, false, triangle, P_color);
  printMenuPhrase("Main", -30, 5, 10, false, triangle, P_color1);
  printMenuPhrase("Quit", -30, -10, 10, false, triangle, P_color2);

}

//shows the game over screen
//@Param input so I can use the macros for the keys instead of doing it the long way
static void
game_over_menu(Input* input)
{
  
	if (!game_info.ply_game_over_musc) {
	  mciSendString(L"play over from 0", NULL, 0, 0);
	  game_info.ply_game_over_musc = true;
	}
	

	if (pressed(BUTTON_DOWN)) {
		over_selected++;
		if (over_selected > 3) {
			over_selected = 1;
		}
	}
	if (pressed(BUTTON_UP)) {
		over_selected--;
		if (over_selected < 1) {
			over_selected = 3;
		}
	}
	switch (over_selected) {
	case(1):
		 G_color = BLUE;
		 G_color1 = WHITE;
		 G_color2 = WHITE;
		break;
	case(2):
		 G_color = WHITE;
		 G_color1 = BLUE;
		 G_color2 = WHITE;
		break;
	case(3):
		G_color = WHITE;
		G_color1 = WHITE;
		G_color2 = BLUE;
		break;
	}
	if (pressed(BUTTON_ENTER)) {
		if (over_selected == 1) { //chose to restart the game
			game_over = !game_over;
			options = LEVEL1;
			levelInfoSet = false;
			player_sizex = 2;
			player_sizey = 2;
			accel = 50;
			health_points = 3;
			game_info.ply_game_over_musc = false;
		}
		else  if (over_selected == 2) { //chose to go to the main menu
			game_over = !game_over;
			options = MAINMENU;
			levelInfoSet = false; 
			game_info.started_level = false;  
			player_sizex = 2;
			player_sizey = 2;
			accel = 50;
			health_points = 3;
			game_info.ply_game_over_musc = false;

		}
		else {
			running = false; //closes the windows interface
		}
	}

  draw_rect(0, 0, 42, 35, BLUE);
  draw_rect(0, 0, 41, 34, BLACK);
  draw_rect(0, 15, 41, 0.5, WHITE);
  printMenuPhrase("Game-over", -39.5, 28, 5, false, triangle, WHITE);
  printMenuPhrase("Restart", -25, 10, 8, false, triangle, G_color);
  printMenuPhrase("Main", -25, -5, 8, false, triangle, G_color1);
  printMenuPhrase("Quit", -25, -20, 8, false, triangle, G_color2);
}