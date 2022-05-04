void simulateFinalScreen(Input* input, float& dt) {
  draw_rect(0, 0, 90, 45, TURQUOISE);
  printMenuPhrase("Completed Game", -60, 20, 10, true, circle, PURPLE);

  printLevelText("Press Enter to Quit Game", -45, 0, PURPLE);

  if (pressed(BUTTON_ENTER)) {
	running = false;
  }

  printLevelText("Score ",-25, -16, WHITE);
  printLevelText(std::to_string(game_info.playerScore.getScore()).c_str(), 5, -16, WHITE);


  printLevelText("Music by TAD and DeltaBreaker", -55, -40, PURPLE);
}