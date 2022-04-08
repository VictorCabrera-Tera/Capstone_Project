void simulateLevel3(Input* input, float& dt) {
  mciSendString(L"stop bgm", NULL, 0, 0);
  mciSendString(L"stop lvl2", NULL, 0, 0);
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
	mciSendString(L"play lvl3 from 0", NULL, 0, 0);
	//hearts();
	musc = 0;
  }

  draw_rect(0, 0, 80, 20, BLUE);
  drawLevelCoins();
  draw_hearts();
  collision(&game_info.coins, dt, options);
}