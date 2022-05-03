void simulateLevel4(Input* input, float& dt) {
  mciSendString(L"stop bgm", NULL, 0, 0);
  mciSendString(L"stop lvl3", NULL, 0, 0);
  printLevelText("Level 4", -10, 49, WHITE);
  printLevelText("Lives ", 50, 49, WHITE);
  printLevelText("Coins ", -90, 49, WHITE);

  printLevelText("Score ", -90, -46, WHITE);
  printLevelText(std::to_string(game_info.playerScore.getScore()).c_str(), -65, -46, WHITE);

  printLevelText("Jumps ", 50, -46, WHITE);


  if (!levelInfoSet) {
	game_info.resetCoinsCollected(); //makes all coins' collected variable to false
	Point coin1Pos(-39, -36);
	Point coin2Pos(-76, -12);
	Point coin3Pos(30, 30);
	game_info.setCoinsPositions(coin1Pos, coin2Pos, coin3Pos); //stores the position of the coins

	game_info.setCHcolor(0xDA189C, RED);
	game_info.setCollectableHeart();
	Point chPos1(74, -25);
	Point chPos2(74, -40);
	game_info.setCHpos(chPos1, chPos2);

	player_posX = game_info.getLevel4Spawn().x; //get the spawnpoint
	player_posY = game_info.getLevel4Spawn().y;
	mciSendString(L"play lvl1 from 0", NULL, 0, 0);
	musc = 0;

	hearts();
	Point enemy1Pos(-20, 0), enemy2Pos(0, -30), enemy3Pos(0,40);
	game_info.enemy_pos[0] = enemy1Pos;
	game_info.enemy_pos[1] = enemy2Pos;
	game_info.enemy_pos[2] = enemy3Pos;


	game_info.playerScore.pStartTime = game_info.playerScore.getCurrentTime();
	levelInfoSet = true;
	
  }


  if (leftclear == true) {
	if (is_down(BUTTON_LEFT)) {
	  xvelocity = -40; //-50
	}
  }

  if (released(BUTTON_LEFT)) {
	xvelocity = 0;

  }

  if (rightclear == true) {
	if (is_down(BUTTON_RIGHT)) { // 
	  xvelocity = 40; //50
	}
  }

  if (released(BUTTON_RIGHT)) {
	xvelocity = 0;

  }

  if (pressed(BUTTON_SPACEBAR))
  {
	yvelocity += 3500 * 0.0166;

  }

  old_Y = player_posY;
  old_X = player_posX;


  player_posY += ((yvelocity * dt) + (accel * dt * dt * 0.5));
  player_posX += xvelocity * dt;
  yvelocity += accel * dt;


	
  //platforms
  {
	draw_rect(0, -4, 5, 1, RED);

	draw_rect(0, -4, 5, 1, RED);

  }
  //enemies
  move_sideways(&game_info.enemy_pos[0].x, &delta17, dt, 10, -70, -10);
  move_vertical(&game_info.enemy_pos[1].y, &delta18, dt, 10, -40, -10);
  move_vertical(&game_info.enemy_pos[2].y, &delta19, dt, 10, 10, 30);

  {
	draw_rect(game_info.enemy_pos[0].x, game_info.enemy_pos[0].y, 1, 40, BLUE);
	draw_rect(game_info.enemy_pos[1].x, game_info.enemy_pos[1].y, 40, 1, BLUE);
	draw_rect(game_info.enemy_pos[2].x, game_info.enemy_pos[2].y, 40, 1, BLUE);

  }
  //arrows
  { 
	draw_triangles(74, -40, 2.5, 8, WHITE, 4); //left arrow
	draw_rect(74, -48, 1, 1, WHITE);
	draw_triangles(79,-40, 2.5, 8, WHITE, 4); //right arrow
	draw_rect(79, -48, 1, 1, WHITE);
  }
  drawLevelCoins();
  drawColletableHearts();
  collision(&game_info.coins, dt, options);
  draw_hearts();

  if (game_info.getCoinCollected(0) && game_info.getCoinCollected(1) && game_info.getCoinCollected(2)) {
	//set the goal to a color when interacted, will make options to level2, thus going to next level
	
	draw_triangles(69, 25, 1.6, 1.6, YELLOW, 1);
	draw_rect(71, 20, 0.5, 7, YELLOW);
	if ((player_posX >= 70 && player_posX <= 72) && (player_posY >= 14 && player_posY <= 16)) {
	  game_info.playerScore.pFinishTime = game_info.playerScore.getCurrentTime();
	  int time = game_info.playerScore.secondsSpent(game_info.playerScore.pStartTime, game_info.playerScore.pFinishTime);

	  game_info.playerScore.addScore(500 * ((float)20 / (float)time));
	  game_info.setCHcolor(0xDA189C, 0xDA189D);
	  options = FINALSCREEN;
	  levelInfoSet = false;
	  if (heart_collected) {
		health_points--;
		heart_collected = false;

	  }



	}
  }
}