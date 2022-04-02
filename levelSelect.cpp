void simulateLevelSelect(Input* input, float& dt) {
  

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
	  game_info.started_level = true;
	}
	else  if (selected == 2) {
	  options = LEVEL2;
	  game_info.started_level = true;

	}
	else {
	  options = LEVEL3;
	  game_info.started_level = true;

	}
  }
  
}