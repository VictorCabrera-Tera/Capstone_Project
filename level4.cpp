/**
   Will play Level 4

   @param input points to an Input object containing information about what key's state has been modified and if it is pressed
   @param dt is the amount of time it took for 1 frame in the game
**/
void simulateLevel4(Input* input, float& dt) {
  mciSendString(L"stop bgm", NULL, 0, 0);
  mciSendString(L"stop lvl3", NULL, 0, 0);
  printLevelText("Level 4", -10, 49, WHITE);
  printLevelText("Lives ", 50, 49, WHITE);
  printLevelText("Coins ", -90, 49, WHITE);

  printLevelText("Score ", -90, -46, WHITE);
  printLevelText(std::to_string(game_info.playerScore.getScore()).c_str(), -65, -46, WHITE);

  //printLevelText("Jumps ", 50, -46, WHITE);


  if (!levelInfoSet) {
	game_info.borderColor = PURPLE;
	game_info.bkgColor = LIGHTPURPLE;

	game_info.resetCoinsCollected(); //makes all coins' collected variable to false
	game_info.resetPowerUpInfo();
	game_info.jumps.resetJumps();
	Point coin1Pos(-20, -35);
	Point coin2Pos(70, 31);
	Point coin3Pos(-87, 31);
	game_info.setCoinsPositions(coin1Pos, coin2Pos, coin3Pos); //stores the position of the coins
	
	game_info.setCHcolor(0xDA189C, 0xDA189D);
	game_info.setCollectableHeart();
	Point chPos1(87, -35);
	Point chPos2(74, 4);
	game_info.setCHpos(chPos1, chPos2);


	game_info.setPowerUpColor(IMMUNITY, NAVY);
	Point immunPos(-73, 22);
	game_info.setPowerUpPosition(IMMUNITY, immunPos);
	game_info.setImmunityColors(BLUE, GRAY); //set what color is for active enemies, and what color is for inactive
	game_info.setImmunColorSwapped(false); //set that the colors for inactive and active enemies has not been swapped yet

	player_posX = game_info.getLevel4Spawn().x; //get the spawnpoint
	player_posY = game_info.getLevel4Spawn().y;
	mciSendString(L"play lvl1 from 0", NULL, 0, 0);
	musc = 0;

	hearts();
	Point enemy1Pos(-33, 0), enemy2Pos(15, -27), enemy3Pos(50,-44),enemy4Pos(-40,44),
	  enemy5Pos(-65, -14), enemy6Pos(-86.5, 32), enemy7Pos(0, -11), enemy8Pos(42, 30);
	game_info.enemy_pos[0] = enemy1Pos;
	game_info.enemy_pos[1] = enemy2Pos;
	game_info.enemy_pos[2] = enemy3Pos;
	game_info.enemy_pos[3] = enemy4Pos;
	game_info.enemy_pos[4] = enemy5Pos;
	game_info.enemy_pos[5] = enemy6Pos;
	game_info.enemy_pos[6] = enemy7Pos;
	game_info.enemy_pos[7] = enemy8Pos;



	//game_info.playerScore.pStartTime = game_info.playerScore.getCurrentTime();
	game_info.timer.resetTime();

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

  if (pressed(BUTTON_SPACEBAR) && game_info.jumps.getJumpAvailable() > 0)
  {
	game_info.jumps.removeJump();
	yvelocity += 3500 * 0.0166;
	dtadd = 0;
  }

  if (game_info.jumps.getJumpAvailable() < 2) {
	dtadd += dt;
	if (dtadd > 1) {
	  game_info.jumps.resetJumps();
	  dtadd = 0;
	}
  }

  old_Y = player_posY;
  old_X = player_posX;


  player_posY += ((yvelocity * dt) + (accel * dt * dt * 0.5));
  player_posX += xvelocity * dt;
  yvelocity += accel * dt;





  if (!game_info.getPowerUpCollected(IMMUNITY)) {
	//original enemies movement
	move_sideways(&game_info.enemy_pos[0].x, &delta17, dt, 10, -89, -33);
	move_vertical(&game_info.enemy_pos[1].y, &delta18, dt, 12, -44, -27);
	move_vertical(&game_info.enemy_pos[2].y, &delta19, dt, 12, -44, -27);
	move_vertical(&game_info.enemy_pos[3].y, &delta20, dt, 17, 11, 44);

	//fake coins
	draw_circle(-20, -35, 3, game_info.getImmunityColor(1)); //fake lower middle coin
	draw_circle(70, 31, 3, game_info.getImmunityColor(1)); //fake upper right coin
	draw_circle(-87, 31, 3, game_info.getImmunityColor(1)); //fake upper left coin
  }
  //once collected the power up, and if the active and inactive enemies haven't been swapped yet
  if (game_info.getPowerUpCollected(IMMUNITY) && game_info.getImmunColorSwapped() == false) {
	game_info.swapImmunityColors(); //swap the active and inactive enemies
	game_info.setImmunColorSwapped(true); //swap occured
  }
  if (game_info.getPowerUpCollected(IMMUNITY)) {
	drawLevelCoins();

	//secondary enemies movement
	move_diagonal_bl(&game_info.enemy_pos[4].x, &game_info.enemy_pos[4].y, &delta21, dt, 10, -65, -50);
	move_vertical(&game_info.enemy_pos[5].y, &delta22, dt, 12, 27, 44);
	move_sideways(&game_info.enemy_pos[6].x, &delta23, dt, 17, -4, 57);
	move_vertical(&game_info.enemy_pos[7].y, &delta24, dt, 17, -2, 44);

  }


  //original enemies 
  {
	//start off as blue enemies, but once swap occurs they will be gray
	draw_rect(game_info.enemy_pos[0].x, game_info.enemy_pos[0].y, 1, 40, game_info.getImmunityColor(0)); //left blue wall
	draw_rect(game_info.enemy_pos[1].x, game_info.enemy_pos[1].y, 15, 1, game_info.getImmunityColor(0)); //longer first lower wall
	draw_rect(game_info.enemy_pos[2].x, game_info.enemy_pos[2].y, 10, 1, game_info.getImmunityColor(0)); //shoter second lower wall
	draw_rect(game_info.enemy_pos[3].x, game_info.enemy_pos[3].y, 20, 1, game_info.getImmunityColor(0)); //upper wall

	draw_triangles(74, 10, 6, 6, game_info.getImmunityColor(0), 1); //trapping the second heart
	draw_triangles(74, 10, 6, 6, game_info.getImmunityColor(0), 2);

  }
  //secondary enemies / obstacles
  {
	draw_triangles(-52, -21, 1, 1, game_info.getImmunityColor(1), 1); //spike on platform side (facing left)

	draw_enemy(game_info.enemy_pos[4].x, game_info.enemy_pos[4].y, 4, 4, game_info.getImmunityColor(1)); //enemy diagonal  
	draw_triangles(game_info.enemy_pos[5].x, game_info.enemy_pos[5].y, 2, 2, game_info.getImmunityColor(1), 5); //diamond on left

	draw_triangles(-89, -35, 1, 1, game_info.getImmunityColor(1), 2); //spike on left

	draw_coin(game_info.enemy_pos[6].x, game_info.enemy_pos[6].y, 3, 3, game_info.getImmunityColor(1)); //hexagon on lower mid
	draw_diamond(game_info.enemy_pos[7].x, game_info.enemy_pos[7].y, 2, 2, game_info.getImmunityColor(1)); //diamond near goal

	draw_tri(-20, -42, 10, 3, game_info.getImmunityColor(1)); //trapezoid holding lower middle coin


	draw_tri(70, 24, 10, 3, game_info.getImmunityColor(1)); //trapezoid holding upper right coin



  }
  

  //platforms
  {

	draw_rect(-34, -4, 40, 1, RED); //starting platform

	draw_rect(-82, 3, 1, 42, RED); //longest left wall
	draw_rect(-82, 23, 1, 5, LIGHTPURPLE); //longest left wall opening

	draw_rect(-73, -22, 1, 17, RED);//wall making hole

	draw_rect(-65, -35, 8, 1, RED);//lower left jump 1
	draw_rect(-42, -22, 9, 1, RED);//lower left jump 2



	draw_rect(-33, -29, 1, 16, RED);//lower wall
	draw_rect(-20, -14, 13, 1, RED); //lower wall platform

	draw_rect(7, -9, 1, 17, RED);//right wall next to spawn
	draw_rect(27, -25, 19, 1, RED); //right wall platform

	draw_rect(63, -7, 27, 1, RED); //rightmost platform
	draw_rect(-26, 9, 55, 1, RED); //platform above starting platform

	draw_rect(18, 30, 21, 1, RED); //platform holding goal
	draw_rect(67, 20, 23, 1, RED); //platform top right
	draw_rect(-3, 37, 1, 8, RED);// top right wall

	draw_rect(80, -41, 10, 4, RED); //lower right step
	draw_rect(15, -21, 8, 4, RED); //middle right step
	draw_rect(-73, 14, 10, 4, RED); //upper left step


  }


  drawJumps();
  drawColletableHearts();
  drawLevelPowerUps();
  collision(&game_info.coins, dt, options);
  draw_hearts();

  if (game_info.getCoinCollected(0) && game_info.getCoinCollected(1) && game_info.getCoinCollected(2)) {
	//set the goal to a color when interacted, will make options to level2, thus going to next level
	
	draw_triangles(5, 43, 1.6, 1.6, YELLOW, 1);
	draw_rect(7, 38, 0.5, 7, YELLOW);

	if ((player_posX >= 4 && player_posX <= 8) && (player_posY >= 32 && player_posY <= 34)) {
	  float time = game_info.timer.getTime();

	  game_info.playerScore.addScore(2000 * ((float)60 / (float)time));
	  options = FINALSCREEN;
	  levelInfoSet = false;
	  if (heart_collected) {
		health_points--;
		heart_collected = false;

	  }



	}
  }
  else {
	game_info.timer.addTime(dt);
  }
}