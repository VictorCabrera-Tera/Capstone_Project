
/**
   Will play Level 1

   @param input points to an Input object containing information about what key's state has been modified and if it is pressed
   @param dt is the amount of time it took for 1 frame in the game
**/
static void simulateLevel1(Input* input, float& dt) {
	mciSendString(L"stop bgm", NULL, 0, 0); //stop any music
	mciSendString(L"stop over", NULL, 0, 0);
	//print wording throughout the border
	printLevelText("Level 1", -10, 49, WHITE); 
	printLevelText("Lives ", 50, 49, WHITE);
	printLevelText("Coins ", -90, 49, WHITE);

	printLevelText("Score ", -90, -46, WHITE);
	//print score
	printLevelText(std::to_string(game_info.playerScore.getScore()).c_str(), -65, -46, WHITE);

	if (!levelInfoSet) {//sets the values needed to begin the level. only done in the first frame
	  game_info.borderColor = DARKGREEN;  //sets colors of border and background
	  game_info.bkgColor = LIGHTGREEN;

	  game_info.jumps.resetJumps(); //make sure all jumps are available
	  game_info.resetCoinsCollected(); //makes all coins' collected variable to false
	  Point coin1Pos(-39, -36);
	  Point coin2Pos(-76, -12);
	  Point coin3Pos(30, 30);
	  game_info.setCoinsPositions(coin1Pos, coin2Pos, coin3Pos); //stores the position of the coins

	  game_info.setCHcolor(0xDA189C, RED); //set the collectable hearts colors
	  game_info.setCollectableHeart(); //set all the collectable hearts as uncollected
	  Point chPos1(74, -25);
	  Point chPos2(74, -40);
	  game_info.setCHpos(chPos1, chPos2); //set their positions

	  player_posX = game_info.getLevel1Spawn().x; //get the spawnpoint
	  player_posY = game_info.getLevel1Spawn().y;
	  mciSendString(L"play lvl1 from 0", NULL, 0, 0); //play the music
	  musc = 0;

	  hearts(); //set the values of the hearts representing the lives 
	  Point enemy1Pos(-38, 20), enemy2Pos(32, 22);
	  game_info.enemy_pos[0] = enemy1Pos;
	  game_info.enemy_pos[1] = enemy2Pos;

	  game_info.playerScore.resetScore(); //resets the score

	  game_info.timer.resetTime(); //start the timer over. Timer to keep track how long level has been going on for
	  levelInfoSet = true;
	}

	// unit / second * second/ frame = unit / frame

	if (leftclear == true) {
		if (is_down(BUTTON_LEFT)) {

			xvelocity = -40; //player is going to move left
		}
	}

	if (released(BUTTON_LEFT)) {
		xvelocity = 0; //stop movement 

	}

	if (rightclear == true) { //no obstacle
		if (is_down(BUTTON_RIGHT)) { 
			xvelocity = 40; //move right

		}
	}

	if (released(BUTTON_RIGHT)) {
		xvelocity = 0; //stop movement

	}

	if (pressed(BUTTON_SPACEBAR) && game_info.jumps.getJumpAvailable()>0) 
	{
		game_info.jumps.removeJump(); //used a jump
		yvelocity += 3500 * 0.0166; //jump movement
		dtadd = 0;
	}

	if (game_info.jumps.getJumpAvailable() < 2) {
		dtadd += dt; //timer that will know when a second passes
		if (dtadd > 1) {
			game_info.jumps.resetJumps(); //gain jumps back
			dtadd = 0;
		}
	}
	


	old_Y = player_posY; //store values of previous movement
	old_X = player_posX;

	//apply velocity and acceleration to the player positions
	player_posY += ((yvelocity * dt) + (accel * dt * dt * 0.5)); 
	player_posX += xvelocity * dt; 
	yvelocity += accel * dt;




	//movement functions for enemies
	move_vertical(&game_info.enemy_pos[0].y, &delta, dt, 10, -15, 26);

	move_sideways(&game_info.enemy_pos[1].x, &delta1, dt, 20, -65, 71);


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

	drawLevelCoins(); //draw coins scattered in level 
	drawColletableHearts(); //draw any hearts available to collect
	collision(&game_info.coins, dt, options); //draws the player and checks if the player collides with anything or collects anything
	draw_hearts(); //draw lives left
	drawJumps(); //draws the players available jumps

	if (game_info.getCoinCollected(0) && game_info.getCoinCollected(1) && game_info.getCoinCollected(2)) {
		//set the goal to a color when interacted, will make options to level2, thus going to next level
		//options = LEVEL2;
		draw_triangles(69, 25, 1.6, 1.6, YELLOW, 1);
		draw_rect(71, 20, 0.5, 7, YELLOW);
		game_info.timer.addTime(dt); // add time for frame
		if ((player_posX >= 70 && player_posX <= 72) && (player_posY >= 14 && player_posY <= 16)) { //;evel completed
			float time = game_info.timer.getTime(); //get how much time it took for player to complete level


			game_info.playerScore.addScore(500 * ((float)20 / (float)time));
			game_info.setCHcolor(0xDA189C, 0xDA189D); //reset the heart color since level 1 only had 1 heart with appropriate color 
			options = LEVEL2; //move to next level
			levelInfoSet = false;
			if (heart_collected) {
				health_points--;
				heart_collected = false;

			}



		}
	}
	else {
		game_info.timer.addTime(dt); //add how much time passed for that frame
	}
}