#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!(input->buttons[b].is_down) && input->buttons[b].changed)


internal void simulateLevel1(Input* input, float& dt) {
	mciSendString(L"stop bgm", NULL, 0, 0);
	printLevelText("Level 1", -10, 49, WHITE);
	printLevelText("Lives ", 50, 49, WHITE);
	printLevelText("Coins ", -90, 49, WHITE);

	if (!levelInfoSet) {
		game_info.resetCoinsCollected(); //makes all coins' collected variable to false
		Point coin1Pos(-39, -36);
		Point coin2Pos(-76, -12);
		Point coin3Pos(30, 30);
		game_info.setCoinsPositions(coin1Pos, coin2Pos, coin3Pos); //stores the position of the coins

		game_info.setCollectableHeart();
		Point chPos1(-25, 10);
		game_info.setCHpos(chPos1, NULL);

		player_posX = game_info.getLevel1Spawn().x; //get the spawnpoint
		player_posY = game_info.getLevel1Spawn().y;
		mciSendString(L"play lvl1 from 0", NULL, 0, 0);
		musc = 0;

		hearts();
		Point enemy1Pos(-38, 20), enemy2Pos(32, 22);
		game_info.enemy_pos[0] = enemy1Pos;
		game_info.enemy_pos[1] = enemy2Pos;


		levelInfoSet = true;
	}

	// unit / second * second/ frame = unit / frame

	if (leftclear == true) {
		if (is_down(BUTTON_LEFT)) {
			//player_posX -= speed * dt;
			xvelocity = -20;

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
			xvelocity = 20;
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

	if (pressed(BUTTON_SPACEBAR))
	{
		//player_posY += speed * dt;
		yvelocity += 3000 * 0.0166;

	}

	old_Y = player_posY;
	old_X = player_posX;


	player_posY += ((yvelocity * dt) + (accel * dt * dt * 0.5));
	player_posX += xvelocity * dt;
	yvelocity += accel * dt;





	move_vertical(&game_info.enemy_pos[0].y, &delta, dt, 3, -15, 26);

	move_sideways(&game_info.enemy_pos[1].x, &delta1, dt, 10, -65, 71);
	//move_sideways(&enemy_x, delta, dt, 20);
	//move_vertical(&enemy_y, delta, dt, 20);
	//move_diagonal_tl(&enemy_x, &enemy_y, delta, dt, 20);	

	{
		draw_rect(82, -38, 8, 8, RED); //fills in lower right corner

		draw_rect(-69, -44, 5, 1, RED); //bump1

		draw_rect(-40, -41, 15, 1, RED); //plat1

		draw_right_tri(2.2, -44.9, 2.8, RED); //little ledge next to stairs
		draw_rect(45, -42, 40, 3, RED); //stairs
		draw_rect(55, -37, 20, 2, RED);
		draw_rect(65, -33, 20, 2, RED);
		draw_rect(75, -29, 20, 2, RED);

		draw_rect(19, -28, 8, 0.5, RED); //plat2



		draw_rect(-44, -20, 35, 0.8, RED); //plat3
		draw_rect(-1, -22, 5, 0.5, RED);

		draw_rect(-76, -17, 3, 2.3, RED); //bump2


		draw_rect(-53, -9, 11, 0.2, RED); //platform 4
		draw_rect(-51, -8.3, 9, 0.5, RED);
		draw_right_tri(-51, -8.1, 9, RED);

		draw_rect(-38, 35, 4, 10, RED); //wall
		draw_rect(-38, 2, 4, 8, RED); //wall

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

	if (game_info.getCoinCollected(0) && game_info.getCoinCollected(1) && game_info.getCoinCollected(2)) {
		//set the goal to a color when interacted, will make options to level2, thus going to next level
		//options = LEVEL2;
		draw_triangles(69, 25, 1.6, 1.6, YELLOW, 1);
		draw_rect(71, 20, 0.5, 7, YELLOW);
		if ((player_posX >= 70 && player_posX <= 72) && (player_posY >= 14 && player_posY <= 16)) {
			options = LEVEL2;
			levelInfoSet = false;
			if (heart_collected) {
				health_points--;
				heart_collected = false;

			}

		}
	}
}