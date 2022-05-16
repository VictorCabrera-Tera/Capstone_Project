bool firstScreen;
void simulateFinalScreen(Input* input, float& dt) {
  fill_window(BLUE);
  draw_rect(0, 0, 90, 45, TURQUOISE);
  if (!levelInfoSet) {
	firstScreen = true;
	levelInfoSet = true;
  }
  if (firstScreen) {
	printMenuPhrase("G a m e", -30, 20, 20, false, ticket, PURPLE);
	printMenuPhrase("C o m p l e t e d !", -83, 10, 20, false, ticket, PURPLE);

	printLevelText("Press Enter to Quit", -33, -10, PURPLE);

	draw_rect(0, -27, 30, 5, TEAL);
	printLevelText("Score ", -20, -26, WHITE);
	printLevelText(std::to_string(game_info.playerScore.getScore()).c_str(), 10, -26, WHITE);


	draw_triangles(80, -31, 3, 8, TEAL, 2); //right arrow
	draw_rect(75, -38.7, 5, 2, TEAL);
  }
  else {
	printMenuPhrase("Special Thanks To", -75, 20, 10, false, square, PURPLE);
	printLevelText("Dan Zaidan", -20, 0, PURPLE);
	printLevelText("www  youtube  com user  DanZaidan", -58,-19, PURPLE);
	draw_rect(-44, -21, 1, 1, PURPLE);
	draw_rect(-13, -21, 1, 1, PURPLE);
	printMenuPhrase("/ /", 0, -17,4,false,square, PURPLE);

	printLevelText("Music by TAD and DeltaBreaker", -55, -40, PURPLE);

	draw_triangles(-80, -31, 3, 8, TEAL, 1); //left arrow
	draw_rect(-75, -38.7, 5, 2, TEAL);
  }
  if (pressed(BUTTON_ENTER)) {
	running = false;
  }
  if (pressed(BUTTON_RIGHT)) {
	firstScreen = false;
  }
  if (pressed(BUTTON_LEFT)) {
	firstScreen = true;
  }
}