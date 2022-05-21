/**
   Will play Level 2

   @param input points to an Input object containing information about what key's state has been modified and if it is pressed
   @param dt is the amount of time it took for 1 frame in the game
**/
void simulateLevel2(Input* input, float& dt) {
	mciSendString(L"stop bgm", NULL, 0, 0);
	mciSendString(L"stop lvl1", NULL, 0, 0);
	//mciSendString(L"stop coin", NULL, 0, 0);
	printLevelText("Level 2", -10, 49, WHITE);
	printLevelText("Lives ", 50, 49, WHITE);
	printLevelText("Coins ", -90, 49, WHITE);
	printLevelText("Score ", -90, -46, WHITE);
	printLevelText(std::to_string(game_info.playerScore.getScore()).c_str(), -65, -46, WHITE);



	if (!levelInfoSet) {
	  game_info.borderColor = 0xBF360C;
	  game_info.bkgColor = LIGHTGRAY;

	  game_info.resetCoinsCollected();
	  game_info.resetPowerUpInfo();
	  game_info.jumps.resetJumps();
	  Point coin1pos(33, 17), coin2pos(78, -10), coin3pos(-39, -14);
	  game_info.setCoinsPositions(coin1pos, coin2pos, coin3pos);

	  game_info.setPowerUpColor(SHRINK, TEAL); //set the color for Shrink power up, setting also signifies power up is being used in level
	  Point shrinkPos(-10, -42);
	  game_info.setPowerUpPosition(SHRINK, shrinkPos); //set Shrink's position

	  game_info.setPowerUpColor(PHASE_THROUGH, TURQUOISE); //set Phase color
	  Point phaseThroughPos(-37, 37);
	  game_info.setPowerUpPosition(PHASE_THROUGH, phaseThroughPos); //set phase position

	  game_info.setCHcolor(0xDA189C, 0xDA189D);
	  game_info.setCollectableHeart();
	  Point chPos1(-25, 13), chPos2(42, -42);
	  game_info.setCHpos(chPos1, chPos2);



	  player_posX = game_info.getLevel2Spawn().x; //get the spawnpoint
	  player_posY = game_info.getLevel2Spawn().y;
	  mciSendString(L"play lvl2 from 0", NULL, 0, 0);
	  musc = 0;
	  hearts();

	  Point enemy1Pos(40, 26), enemy2Pos(70, 26), enemy3Pos(56, -19),
		  enemy4Pos(-75, 40), enemy5Pos(-66, -3), enemy6Pos(-82, -23),
		  enemy7Pos(-36, -33);
	  game_info.enemy_pos[0] = enemy1Pos;
	  game_info.enemy_pos[1] = enemy2Pos;
	  game_info.enemy_pos[2] = enemy3Pos;
	  game_info.enemy_pos[3] = enemy4Pos;
	  game_info.enemy_pos[4] = enemy5Pos;
	  game_info.enemy_pos[5] = enemy6Pos;
	  game_info.enemy_pos[6] = enemy7Pos;

	  game_info.timer.resetTime();

	  jump_height = 3500;
	  levelInfoSet = true;
	  //hearts();
	}
	if (!freemode) { //freemode is the "god mode" in the game. Allows for immunity to everything
		if (leftclear == true) {
			if (is_down(BUTTON_LEFT)) {
				xvelocity = -40;

			}
		}

		if (released(BUTTON_LEFT)) {
			xvelocity = 0;

		}

		if (rightclear == true) {
			if (is_down(BUTTON_RIGHT)) { 
				xvelocity = 40;
			}
		}

		if (released(BUTTON_RIGHT)) {
			xvelocity = 0;

		}

		if (pressed(BUTTON_SPACEBAR) && game_info.jumps.getJumpAvailable() > 0)
		{
			game_info.jumps.removeJump();
			yvelocity += jump_height * 0.0166;
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

	}
	else {
		if (is_down(BUTTON_LEFT) && player_posX > -87) {
			player_posX -= speed * dt;
		}
		if (is_down(BUTTON_RIGHT) && player_posX < 87) {
			player_posX += speed * dt;
		}
		if (is_down(BUTTON_DOWN) && player_posY > -42) {
			player_posY -= speed * dt;
		}
		if (is_down(BUTTON_UP) && player_posY < 42) {
			player_posY += speed * dt;
		}
		old_Y = player_posY;
		old_X = player_posX;
	}



	{
		draw_rect(0, 0, 90, 0.8, RED); //BORDER
		draw_rect(-29, 27.5, 0.3, 17.5, RED);
		draw_rect(29, 27.5, 0.3, 17.5, RED);

		draw_rect(0, 35, 5, 0.5, RED); //top middle platforms
		draw_rect(-20, 27, 5, 0.5, RED);
		draw_rect(20, 27, 5, 0.5, RED);
		draw_rect(0, 20, 7, 0.5, RED);
		draw_rect(24, 10, 5, 0.5, RED);
		draw_rect(-24, 10, 5, 0.5, RED);

		draw_right_tri(86, 0, 4, RED); //top right triangle

		draw_triangles(89, 30, 1, 15, BLUE, 1); //spikes
		draw_triangles(89, 28, 1, 15, BLUE, 1);
		draw_triangles(89, 26, 1, 15, BLUE, 1);

		draw_rect(70, 13, 5, 0.5, RED); //top right platforms
		draw_rect(37, 13, 8, 0.5, RED);


		draw_triangles(-88, 34, 2, 15, BLUE, 2); //top left spikes
		draw_triangles(-88, 30, 2, 15, BLUE, 2);
		draw_triangles(-88, 26, 2, 15, BLUE, 2);

		draw_rect(-84, 6.8, 6, 2, RED); //top left stairs
		draw_rect(-73, 2.8, 17, 2, RED);

		draw_rect(-67, 17, 5, 0.5, RED); //top left platforms
		draw_rect(-37, 22, 8, 0.5, RED);
		draw_rect(-67, 28, 5, 0.5, RED);
		draw_rect(-37, 33, 8, 0.5, RED);

		draw_rect(-8, -10, 8, 0.5, RED); //lower middle platforms
		draw_rect(-15.5, -26, 1, 16.5, RED);

		draw_rect(-10.5, -3.5, 0.5, 4, RED);
		draw_rect(13, -17, 1, 17, RED);

		draw_triangles(13, -30, 1, 15, BLUE, 4); //spikes (lower right)

		draw_triangles(48, -30, 2, 15, BLUE, 4);
		draw_triangles(50, -30, 2, 15, BLUE, 4);
		draw_triangles(52, -30, 2, 15, BLUE, 4);
		draw_triangles(54, -30, 2, 15, BLUE, 4);
		draw_triangles(56, -30, 2, 15, BLUE, 4);
		draw_triangles(58, -30, 2, 15, BLUE, 4);
		draw_triangles(60, -30, 2, 15, BLUE, 4);
		draw_triangles(62, -30, 2, 15, BLUE, 4);
		draw_triangles(64, -30, 2, 15, BLUE, 4);

		draw_triangles(56, -13, 2, 15, BLUE, 4);

		draw_rect(31, -40, 8, .5, RED); //lower right platforms
		draw_rect(78, -38, 8, .5, RED);

		draw_rect(56, -28, 8, .5, RED); //(mess with this)
		draw_rect(31, -31, 5, .5, RED);
		draw_rect(78, -18, 5, .5, RED);

		draw_rect(-36, -42, 20, 0.5, RED); //lower left platforms
		draw_rect(-74.5, -42, 12, 0.5, RED);

		draw_rect(-38, -38, 16, 0.5, RED);
		draw_rect(-73, -38, 10, 0.5, RED);

		draw_rect(-63, -35.5, 0.5, 3, RED);
		draw_rect(-39, -33, 24, 0.5, RED);

		draw_rect(-76, -33, 14, 0.5, RED);
		draw_rect(-74.5, -28, 15.5, 0.5, RED);
		draw_rect(-59, -30, 0.5, 2.5, RED);

		draw_rect(-43.5, -23, 27, 0.5, RED);
		draw_rect(-83, -20, 7, 0.5, RED);

		draw_rect(-87.5, -16, 2.5, 0.5, RED);
		draw_rect(-89, -12, 1, 0.5, RED);
		draw_rect(-80, -12.5, 0.5, 3.5, RED);
		draw_rect(-61, -9.5, 19, 0.5, RED);

		draw_rect(-43.5, -18, 20, 0.5, RED);
		draw_rect(-42.5, -9.5, 0.5, 9, RED);


		draw_rect(-25, -10, 12, 0.5, RED);

	}
	{
		move_vertical(&game_info.enemy_pos[0].y, &delta, dt, 6, 23, 36);
		move_vertical(&game_info.enemy_pos[1].y, &delta1, dt, 8, 23, 36);

		draw_diamond(game_info.enemy_pos[0].x, game_info.enemy_pos[0].y, 3, 3, BLUE); //top right enemy 1
		draw_diamond(game_info.enemy_pos[1].x, game_info.enemy_pos[1].y, 3, 3, BLUE); //top right enemy 2

		move_sideways(&game_info.enemy_pos[2].x, &delta2, dt, 20, 36, 76);
		draw_coin(game_info.enemy_pos[2].x, game_info.enemy_pos[2].y, 3, 3, BLUE); //Lower right enemy (enemy 3)

		move_diagonal_bl(&game_info.enemy_pos[3].x, &game_info.enemy_pos[3].y, &delta3, dt, 18, -80, -44);
		draw_enemy(game_info.enemy_pos[3].x, game_info.enemy_pos[3].y, 4, 4, BLUE); //top right enemy (enemy 4)


		move_sideways(&game_info.enemy_pos[4].x, &delta4, dt, 20, -85, -46);
		move_sideways(&game_info.enemy_pos[5].x, &delta5, dt, 20, -85, -26);
		move_sideways(&game_info.enemy_pos[6].x, &delta6, dt, 16, -50, -26);

		draw_coin(game_info.enemy_pos[4].x, game_info.enemy_pos[4].y, 3, 3, BLUE); //Lower left enemy 1 (enemy 5)
		draw_coin(game_info.enemy_pos[5].x, game_info.enemy_pos[5].y, 3, 3, BLUE); //Lower left enemy 2 (enemy 6)
		draw_coin(game_info.enemy_pos[6].x, game_info.enemy_pos[6].y, 3, 3, BLUE); //Lower left enemy 3 (enemy 7)

	}

	//Shrink functionality
	if (game_info.getPowerUpCollected(SHRINK)) { //if collected the power up
		if (!game_info.shrunk) {  //if the player is normal size
			player_sizex = 1; //make player smaller
			player_sizey = 1;
			jump_height = 2500.0; //decrease jump height

			Point shrinkPos(-3, -4);
			game_info.setPowerUpPosition(SHRINK, shrinkPos); //draw another shrink power up somewhere else
			game_info.setPowerUpCollected(SHRINK, false);
			game_info.shrunk = true;
		}
		else {
			player_sizex = 2; //reset values 
			player_sizey = 2;
			jump_height = 3500.0; 
			if (!game_info.getCoinCollected(2)) { //only respawn another shrink if second coin hasn't been collected yet
				Point shrinkPos(-10, -42);
				game_info.setPowerUpPosition(SHRINK, shrinkPos);
				game_info.setPowerUpCollected(SHRINK, false);
				game_info.shrunk = false;
			}

		}
	}

	//Phase functionality
	if (game_info.getPowerUpCollected(PHASE_THROUGH)) {
		fakeWall = game_info.getPowerUpColor(PHASE_THROUGH); //the walls that will change color will become the color of the power up 
		draw_rect(-29, 36.5, 0.3, 3, fakeWall); //draws these shapes over the platforms. allows players to go through them
		draw_rect(0, 0, 10, 0.8, fakeWall);
		draw_rect(29, 19.5, 0.3, 6, fakeWall);

		draw_rect(-66.5, -33, 3, 0.5, fakeWall);
		draw_rect(-36.5, -33, 5, 0.5, fakeWall);
		draw_rect(-42.5, -4.8, 0.5, 4.1, fakeWall);

		draw_rect(-61, -9.5, 4.2, 0.5, fakeWall);
		draw_rect(-61, -10.5, 4.2, 0.5, RED);

	}


	drawLevelCoins();
	drawColletableHearts();
	drawLevelPowerUps();
	collision(&game_info.coins, dt, options);
	draw_hearts();
	drawJumps();
	if (game_info.getCoinCollected(0) && game_info.getCoinCollected(1) && game_info.getCoinCollected(2)) {
		//set the goal to a color when interacted, will make options to level2, thus going to next level
		draw_triangles(-7, -33.5, 1.6, 1.6, YELLOW, 1);
		draw_rect(-5, -38, 0.5, 7, YELLOW);
		if ((player_posX >= -6 && player_posX <= -4) && (player_posY >= -45.5 && player_posY <= -37.5)) {

			float time = game_info.timer.getTime();

			game_info.playerScore.addScore(1000 * ((float)50 / (float)time));
			options = LEVEL3;
			player_sizex = 2;
			player_sizey = 2;
			accel = 50.0; 
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