void simulateLevelSelect(Input* input, float& dt) {
  draw_rect(0, 0, 90, 45, BLUE);

  printMenuPhrase("Pick A Level", -52, 30, 6, false, square, RED);

  if (pressed(BUTTON_RIGHT)) {
	selected++;
	if (selected > 4) {
	  selected = 1;
	}
	mciSendString(L"play button from 0", NULL, 0, 0);
  }

  if (pressed(BUTTON_LEFT)) {
	selected--;
	if (selected < 1) {
	  selected = 4;
	}
	mciSendString(L"play button from 0", NULL, 0, 0);
  }
  switch (selected) {
  case(1):
	color1 = RED;
	color2 = BLACK;
	color3 = BLACK;
	color4 = BLACK;
	break;
  case(2):
	color1 = BLACK;
	color2 = RED;
	color3 = BLACK;
	color4 = BLACK;
	break;
  case(3):
	color1 = BLACK;
	color2 = BLACK;
	color3 = RED;
	color4 = BLACK;
	break;
  case(4):
	color1 = BLACK;
	color2 = BLACK;
	color3 = BLACK;
	color4 = RED;
	break;
  }
  printMenuPhrase("1", -50, 0, 16, false, square, color1);
  
  printMenuPhrase("2", -20, 0, 16, false, square, color2);

 
  printMenuPhrase("3", 10, 0, 16, false, square, color3);
  printMenuPhrase("4", 40, 0, 16, false, square, color4);


  {
	draw_triangles(-50, -16, 3, 8, GREEN, 1); //left arrow
	draw_rect(-45, -23.7, 5, 2, GREEN);
	draw_triangles(50, -16, 3, 8, GREEN, 2); //right arrow
	draw_rect(45, -23.7, 5, 2, GREEN);
  }


  if (pressed(BUTTON_ENTER)) {
	if (selected == 1) {
	  options = LEVEL1;
	  game_info.started_level = true;
	}
	else  if (selected == 2) {
	  options = LEVEL2;
	  game_info.started_level = true;
	  color1 = RED;
	  color2 = BLACK;
	  color3 = BLACK;
	  color4 = BLACK;
	}
	else if (selected == 3) {
	  options = LEVEL3;
	  game_info.started_level = true;
	  color1 = RED;
	  color2 = BLACK;
	  color3 = BLACK;
	  color4 = BLACK;
	}
	else {
	  options = LEVEL4;
	  game_info.started_level = true;
	  color1 = RED;
	  color2 = BLACK;
	  color3 = BLACK;
	  color4 = BLACK;
	}
  }
  
}