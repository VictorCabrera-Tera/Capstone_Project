//@Param input so I can use the macros for the keys instead of doing it the long way
//press escape or enter on resume to unpause
//press enter on main to go back to mainmenu
//press enter on quit to quit to desktop
internal void
pauseMenu(Input* input)
{
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
	
		if (pressed(BUTTON_ENTER)) {
			if (pause_selected == 1) {
				game_info.pause = !game_info.pause;
			}
			else  if (pause_selected == 2) {
				game_info.pause = !game_info.pause;
				options = MAINMENU;
				levelInfoSet = false; //so u don't start at the same spot u we're on the level 
				game_info.started_level = false;  //so u can't pause on the main menu
			}
			else {
				running = false; //closes the windows interface
			}
		}
		draw_rect(0, 0, 40, 30, BLACK);
		printMenuPhrase("Resume", -30, 20, 10, false, triangle, P_color);
		printMenuPhrase("Main", -30, 5, 10, false, triangle, P_color1);
		printMenuPhrase("Quit", -30, -10, 10, false, ticket, P_color2);
		
} 
