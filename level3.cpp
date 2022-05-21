/**
   Will play Level 3

   @param input points to an Input object containing information about what key's state has been modified and if it is pressed
   @param dt is the amount of time it took for 1 frame in the game
**/
void simulateLevel3(Input* input, float& dt) {
	mciSendString(L"stop bgm", NULL, 0, 0);
	mciSendString(L"stop lvl2", NULL, 0, 0);
	printLevelText("Level 3", -10, 49, WHITE);
	printLevelText("Lives ", 50, 49, WHITE);
	printLevelText("Coins ", -90, 49, WHITE);

	printLevelText("Score ", -90, -46, WHITE);
	printLevelText(std::to_string(game_info.playerScore.getScore()).c_str(), -65, -46, WHITE);


	if (!levelInfoSet) {
	  game_info.borderColor = RED;
	  game_info.bkgColor = LIGHTPINK;

	  game_info.resetCoinsCollected();
	  game_info.resetPowerUpInfo();
	  game_info.jumps.resetJumps();
	  Point coin1pos(-86, 36), coin2pos(-42, 0), coin3pos(16, 2);
	  game_info.setCoinsPositions(coin1pos, coin2pos, coin3pos);


	  game_info.setPowerUpColor(PHASE_THROUGH, TURQUOISE);
	  Point phaseThroughPos(86, 36);
	  game_info.setPowerUpPosition(PHASE_THROUGH, phaseThroughPos);

	  game_info.setCHcolor(0xDA189C, 0xDA189D);
	  game_info.setCollectableHeart();
	  Point chPos1(1, 1), chPos2(87, -14.5);
	  game_info.setCHpos(chPos1, chPos2);



	  player_posX = game_info.getLevel3Spawn().x; //get the spawnpoint
	  player_posY = game_info.getLevel3Spawn().y;
	  mciSendString(L"play lvl3 from 0", NULL, 0, 0);
	  musc = 0;
	  hearts();

	  Point	enemy1Pos(-70, -30),
		  enemy2Pos(1, -10),
		  enemy3Pos(0, 33.5),
		  enemy4Pos(15, -28),
		  enemy5Pos(40, -13),
		  enemy6Pos(65, 2),
		  enemy7Pos(0, 18),
		  enemy8Pos(40, 28),
		  enemy9Pos(40, 2),
		  enemy10Pos(15, -13);

	  game_info.enemy_pos[0] = enemy1Pos;
	  game_info.enemy_pos[1] = enemy2Pos;
	  game_info.enemy_pos[2] = enemy3Pos;
	  game_info.enemy_pos[3] = enemy4Pos;
	  game_info.enemy_pos[4] = enemy5Pos;
	  game_info.enemy_pos[5] = enemy6Pos;
	  game_info.enemy_pos[6] = enemy7Pos;
	  game_info.enemy_pos[7] = enemy8Pos;
	  game_info.enemy_pos[8] = enemy9Pos;
	  game_info.enemy_pos[9] = enemy10Pos;

	  //game_info.playerScore.pStartTime = game_info.playerScore.getCurrentTime();
	  game_info.timer.resetTime();

	  game_info.setLevel3Spawn(-85, -41);

	  levelInfoSet = true;
	  //hearts();
	}


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
		yvelocity += 4200 * 0.0166;
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

	if (touched) {
		game_info.setLevel3Spawn(-5, -38);
	}


	/*

		//type = 1 facing left
		//type = 2 facing right
		//type = 3 facing down
		//type = 4 facing up
		//type = 5 full diamond
		draw_triangles(-63, 10, 1, 15, BLUE, 1);
		draw_triangles(-50, 10, 1, 15, BLUE, 2);
		draw_triangles(-57, 5, 2, 15, BLUE, 3);
		draw_triangles(-57, 15, 7, 15, BLUE, 4);
	  }
	*/

	//x , y , length, thickness




	//left platforms
	draw_rect(-70, -14, 2, 0.5, RED);
	draw_rect(-86, -29, 4, 0.5, RED);
	draw_rect(-55, -29, 4, 0.5, RED);
	draw_rect(-70, 16, 2, 0.5, RED);
	draw_rect(-86, 1, 4, 0.5, RED);
	draw_rect(-55, 1, 4, 0.5, RED);
	draw_rect(-86, 31, 4, 0.5, RED);
	draw_rect(-55, 31, 4, 0.5, RED);
	draw_triangles(-88, -27.5, 2, 1, BLUE, 4);
	draw_triangles(-53, -27.5, 2, 1, BLUE, 4);
	draw_triangles(-88, 2.5, 2, 1, BLUE, 4);
	draw_triangles(-53, 2.5, 2, 1, BLUE, 4);
	draw_triangles(-88, 32.5, 2, 1, BLUE, 4);
	//draw_triangles(-53, 32.5, 2, 1, BLUE, 4);
	draw_triangles(-70, -44, 2, 1, BLUE, 4);
	//left column
	draw_rect(-48, -9, 3, 40, RED);

	//attached part
	draw_rect(20, 31, 71, 0.5, RED);

	//second left column
	draw_rect(-36, -5, 3, 36, RED);

	//bottom right part
	//platforms
	draw_rect(-29, -31, 4, 0.5, RED);
	//	draw_rect(-14, -17.5, 4, 2.5, RED);
	draw_rect(0, -18, 12, 2, RED);
	draw_rect(1, -2, 6, 1, RED);

	//column
	draw_rect(10, -10, 3, 23, RED);




	//overhead
	draw_rect(25, 12, 60, 2, RED);


	//platforms for 3by3

	draw_rect(15, -32, 4, 0.5, RED);

	draw_rect(40, -32, 4, 0.5, RED);

	draw_rect(65, -32, 4, 0.5, RED);

	draw_rect(88, -32, 4, 0.5, RED);

	draw_rect(15, -17, 4, 0.5, RED);

	draw_rect(40, -17, 4, 0.5, RED);

	draw_rect(65, -17, 4, 0.5, RED);

	draw_rect(88, -17, 4, 0.5, RED);

	draw_rect(15, -2, 4, 0.5, RED);

	draw_rect(40, -2, 4, 0.5, RED);

	draw_rect(65, -2, 4, 0.5, RED);

	draw_rect(88, -2, 4, 0.5, RED);



	draw_triangles(-7, -33.5, 1.6, 1.6, BLACK, 1);
	draw_rect(-5, -38, 0.5, 7, BLACK);




	//enemies
	draw_diamond(game_info.enemy_pos[0].x, game_info.enemy_pos[0].y, 3, 3, BLUE);
	move_vertical(&game_info.enemy_pos[0].y, &delta7, dt, 15, -40, 40);

	draw_diamond(game_info.enemy_pos[1].x, game_info.enemy_pos[1].y, 3, 3, BLUE);
	move_sideways(&game_info.enemy_pos[1].x, &delta8, dt, 20, -10, 4);

	draw_diamond(game_info.enemy_pos[2].x, game_info.enemy_pos[2].y, 1, 1, BLUE);
	move_sideways(&game_info.enemy_pos[2].x, &delta9, dt, 50, -30, 80);

	draw_diamond(game_info.enemy_pos[3].x, game_info.enemy_pos[3].y, 2, 2, BLUE);
	move_sideways(&game_info.enemy_pos[3].x, &delta10, dt, 20, 15, 88);

	draw_diamond(game_info.enemy_pos[4].x, game_info.enemy_pos[4].y, 2, 2, BLUE);
	move_sideways(&game_info.enemy_pos[4].x, &delta11, dt, 20, 15, 88);

	draw_diamond(game_info.enemy_pos[5].x, game_info.enemy_pos[5].y, 2, 2, BLUE);
	move_sideways(&game_info.enemy_pos[5].x, &delta12, dt, 20, 15, 88);

	draw_diamond(game_info.enemy_pos[6].x, game_info.enemy_pos[6].y, 2, 2, BLUE);
	move_sideways(&game_info.enemy_pos[6].x, &delta13, dt, 30, -20, 75);
	draw_diamond(game_info.enemy_pos[7].x, game_info.enemy_pos[7].y, 2, 2, BLUE);
	move_sideways(&game_info.enemy_pos[7].x, &delta14, dt, 15, -20, 75);
	if (game_info.getPowerUpCollected(PHASE_THROUGH)) {
		fakeWall = game_info.getPowerUpColor(PHASE_THROUGH);
		draw_rect(-42, 31, 3, 0.5, fakeWall);

	}




	drawColletableHearts();
	drawLevelPowerUps();







	drawJumps();

	drawLevelCoins();
	collision(&game_info.coins, dt, options);
	draw_hearts();

	if (game_info.getCoinCollected(0) && game_info.getCoinCollected(1) && game_info.getCoinCollected(2)) {
		//set the goal to a color when interacted, will make options to level2, thus going to next level
		draw_triangles(-30, 26, 1.6, 1.6, YELLOW, 1);
		draw_rect(-28, 21, 0.5, 7, YELLOW);
		if ((player_posX >= -29 && player_posX <= -27) && (player_posY >= 14 && player_posY <= 21)) {

			float time = game_info.timer.getTime();

			game_info.playerScore.addScore(1000 * ((float)50 / (float)time));

			options = LEVEL4;

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