void simulateLevel2(Input* input, float& dt) {
  printLevelText("Level 2", -10, 49, WHITE);
  printLevelText("Lives ", 50, 49, WHITE);
  printLevelText("Coins ", -90, 49, WHITE);
  
  if (!levelInfoSet) {
	game_info.resetCoinsCollected();
	game_info.resetPowerUpInfo();

	game_info.setCoinsColor(GRAY, NAVY, TEAL);

	Point coin1pos(20,20), coin2pos(10,10), coin3pos(30,30);
	game_info.setCoinsPositions(coin1pos, coin2pos, coin3pos);

	game_info.setPowerUpColor(SHRINK, YELLOW);
	Point shrinkPos(40, -40);
	game_info.setPowerUpPosition(SHRINK, shrinkPos);
	
	game_info.setPowerUpColor(PHASE_THROUGH, TURQUOISE);
	Point phaseThroughPos(30, -40);
	game_info.setPowerUpPosition(PHASE_THROUGH, phaseThroughPos);

	game_info.setPowerUpColor(IMMUNITY, BROWN);
	Point immunityPos(50, -40);
	game_info.setPowerUpPosition(IMMUNITY, immunityPos);



	player_posX = game_info.getLevel2Spawn().x; //get the spawnpoint
	player_posY = game_info.getLevel2Spawn().y;

	levelInfoSet = true;
  }
  if (!freemode) {
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
	  yvelocity -= 3000 * 0.0166;

	}
	old_Y = player_posY;
	old_X = player_posX;

	player_posY -= yvelocity * dt;
	player_posX += xvelocity * dt;
	yvelocity += accel * dt;

  }
  else {
	if (is_down(BUTTON_LEFT)) {
	  player_posX -= speed * dt;
	}
	if (is_down(BUTTON_RIGHT)) {
	  player_posX += speed * dt;
	}	
	if (is_down(BUTTON_DOWN)) {
	  player_posY -= speed * dt;
	}	
	if (is_down(BUTTON_UP)) {
	  player_posY += speed * dt;
	}
	old_Y = player_posY;
	old_X = player_posX;
  }



  {


	//type = 1 facing left
	//type = 2 facing right
	//type = 3 facing down
	//type = 4 facing up
	//type = 5 full diamond
	draw_triangles(-63, 10, 1, 15, BLUE, 1);
	draw_triangles(-50, 10, 1, 15, BLUE, 2);
	draw_triangles(-57, 5, 2, 15, BLUE, 3);
	draw_triangles(-57, 15, 7, 15, BLUE, 4);

	draw_triangles(-43, 10, 2, 15, RED, 1);
	draw_rect(-38, -5, 4, 1.5, RED);

	draw_triangles(-43, 3, 1, 15, RED, 1);
	draw_rect(-38, -12, 4, 0.5, RED);
  }

  draw_rect(20, -40, 2, 2, fakeWall);

  draw_rect(-10, -42, 2, 2, BLUE);

  if (game_info.getPowerUpCollected(SHRINK)) {
	player_sizex = 1;
	player_sizey = 1;
  }
  
  if (game_info.getPowerUpCollected(PHASE_THROUGH)) {
	fakeWall = game_info.getPowerUpColor(PHASE_THROUGH);
  }
  
  drawLevelCoins();
  drawLevelPowerUps();

  collision(&game_info.coins, dt, options);
}