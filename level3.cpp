void simulateLevel3(Input* input, float& dt) {
  printLevelText("Level 3", -10, 49, WHITE);
  printLevelText("Lives ", 50, 49, WHITE);
  printLevelText("Coins ", -90, 49, WHITE);


  if (!levelInfoSet) {
	game_info.resetCoinsCollected();
	Point coin1Pos(0, 0);
	Point coin2Pos(20, 20);
	Point coin3Pos(-30, -30);
	game_info.setCoinsPositions(coin1Pos, coin2Pos, coin3Pos); //stores the position of the coins

	player_posX = game_info.getLevel3Spawn().x;
	player_posY = game_info.getLevel3Spawn().y;
	levelInfoSet = true;
  }

  draw_rect(0, 0, 80, 20, BLUE);
  drawLevelCoins();
  collision(&game_info.coins, dt, options);
}