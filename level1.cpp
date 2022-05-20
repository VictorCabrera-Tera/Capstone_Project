

static void simulateLevel1(Input* input, float& dt) {
	mciSendString(L"stop bgm", NULL, 0, 0);
	mciSendString(L"stop over", NULL, 0, 0);
	printLevelText("Level 1", -10, 49, WHITE);
	printLevelText("Lives ", 50, 49, WHITE);
	printLevelText("Coins ", -90, 49, WHITE);

	printLevelText("Score ", -90, -46, WHITE);
	printLevelText(std::to_string(game_info.playerScore.getScore()).c_str(), -65, -46, WHITE);

	if (!levelInfoSet) {
	  game_info.borderColor = DARKGREEN;
	  game_info.bkgColor = LIGHTGREEN;

	  game_info.jumps.resetJumps();
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

	  player_posX = game_info.getLevel1Spawn().x; //get the spawnpoint
	  player_posY = game_info.getLevel1Spawn().y;
	  mciSendString(L"play lvl1 from 0", NULL, 0, 0);
	  musc = 0;

	  hearts();
	  Point enemy1Pos(-38, 20), enemy2Pos(32, 22);
	  game_info.enemy_pos[0] = enemy1Pos;
	  game_info.enemy_pos[1] = enemy2Pos;

	  game_info.playerScore.resetScore();

	  //game_info.playerScore.pStartTime = game_info.playerScore.getCurrentTime();
	  game_info.timer.resetTime();
	  levelInfoSet = true;
	}

	// unit / second * second/ frame = unit / frame

	if (leftclear == true) {
		if (is_down(BUTTON_LEFT)) {
			//player_posX -= speed * dt;
			xvelocity = -40; //-50

			/*
			if (xvelocity > 0) {
				xvelocity -= 200 * dt;
			}
			xvelocity -= 100 * dt;
			if (xvelocity < -250) {
				xvelocity = -250;
			}
			*/
		}
	}

	if (released(BUTTON_LEFT)) {
		xvelocity = 0;

	}

	if (rightclear == true) {
		if (is_down(BUTTON_RIGHT)) { // 
			//player_posX += speed * dt;
			xvelocity = 40; //50
			/*
			if (xvelocity < 0) {
				xvelocity += 200 * dt;
			}

			xvelocity += 100 * dt;
			if (xvelocity > 250) {
				xvelocity = 250;
			}
			*/
		}
	}

	if (released(BUTTON_RIGHT)) {
		xvelocity = 0;

	}

	if (pressed(BUTTON_SPACEBAR) && game_info.jumps.getJumpAvailable()>0)
	{
		//player_posY += speed * dt;
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





	move_vertical(&game_info.enemy_pos[0].y, &delta, dt, 10, -15, 26);

	move_sideways(&game_info.enemy_pos[1].x, &delta1, dt, 20, -65, 71);
	//move_sideways(&enemy_x, delta, dt, 20);
	//move_vertical(&enemy_y, delta, dt, 20);
	//move_diagonal_tl(&enemy_x, &enemy_y, delta, dt, 20);	

	{
		draw_rect(82, -37.5, 8, 7.5, RED); //fills in lower right corner

		draw_rect(-69, -44, 5, 1, RED); //bump1

		draw_rect(-40, -41, 15, 1, RED); //plat1

		draw_right_tri(2.2, -44.9, 2.8, RED); //little ledge next to stairs
		draw_rect(45, -42, 40, 3, RED); //stairs
		draw_rect(55, -37, 20, 2, RED);
		draw_rect(65, -33, 20, 2, RED);
		draw_rect(72.5, -29, 17.5, 2, RED);

		draw_rect(19, -28, 8, 0.5, RED); //plat2



		draw_rect(-44, -20, 35, 0.8, RED); //plat3
		draw_rect(-1, -22, 5, 0.5, RED);

		draw_rect(-76, -17, 3, 2.3, RED); //bump2


		//draw_rect(-53, -9, 11, 0.2, RED); //platform 4
		draw_rect(-51, -8.3, 9, 0.5, RED);
		draw_rect(-47, -4.3, 5, 4, RED);
		//draw_right_tri(-51, -8.1, 9, RED);

		draw_rect(-38, 35, 4, 10, RED); //wall
		draw_rect(-38, 0.7, 4, 9.5, RED); //wall

		draw_diamond(game_info.enemy_pos[0].x, game_info.enemy_pos[0].y, 3, 3, BLUE); //enemy 1

		draw_rect(30, 12, 50, 1, RED); //last platform
		draw_coin(30, 32, 30, 20, RED); //the red hexagon platform

		draw_coin(game_info.enemy_pos[1].x, game_info.enemy_pos[1].y, 5, 5, BLUE); //enemy 2
	}
	//draw_heart(6, 6, 1, GREEN);

	drawLevelCoins();
	drawColletableHearts();
	collision(&game_info.coins, dt, options);
	draw_hearts();
	drawJumps();

	if (game_info.getCoinCollected(0) && game_info.getCoinCollected(1) && game_info.getCoinCollected(2)) {
		//set the goal to a color when interacted, will make options to level2, thus going to next level
		//options = LEVEL2;
		draw_triangles(69, 25, 1.6, 1.6, YELLOW, 1);
		draw_rect(71, 20, 0.5, 7, YELLOW);
		game_info.timer.addTime(dt);
		if ((player_posX >= 70 && player_posX <= 72) && (player_posY >= 14 && player_posY <= 16)) {
			float time = game_info.timer.getTime();

			//game_info.playerScore.pFinishTime = game_info.playerScore.getCurrentTime();
			//int time = game_info.playerScore.secondsSpent(game_info.playerScore.pStartTime, game_info.playerScore.pFinishTime);

			game_info.playerScore.addScore(500 * ((float)20 / (float)time));
			game_info.setCHcolor(0xDA189C, 0xDA189D);
			options = LEVEL2;
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