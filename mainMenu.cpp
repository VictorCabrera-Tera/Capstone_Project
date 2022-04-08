void simulateMainMenu(Input* input, float& dt) {

  mciSendString(L"open ..\\sound\\Satorl_Marsh2.wav type waveaudio alias bgm", NULL, 0, 0);
  mciSendString(L"play bgm", NULL, 0, 0);
  
  draw_rect(0, 0, 90, 45, BLUE);
  printMenuPhrase("Main Menu", -43, 25, 13, true, ticket, GREEN);
  u32 temp;
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
	  game_info.started_level = true;
	}
	else {
	  options = LEVELSELECT;

	  color1 = RED;
	  color2 = BLACK;
	}
  }
  if pressed(BUTTON_SPACEBAR) {
	freemode = true;
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