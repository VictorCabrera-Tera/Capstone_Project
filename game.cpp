//#define is_down(b) input->buttons[b].is_down
//#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
//#define released(b) (!(input->buttons[b].is_down) && input->buttons[b].changed)


#include "game_global_variables.cpp"

void simulateLevel1(Input* input, float& dt);
void simulateMainMenu(Input* input, float& dt);
void simulateLevel2(Input* input, float& dt);
void simulateLevel3(Input* input, float& dt);
void simulateLevel4(Input* input, float& dt);
void simulateLevelSelect(Input* input, float& dt);
void simulateFinalScreen(Input* input, float& dt);

internal void
restart_pos(GAMEMODE Level) {
	switch (Level) {
	case(LEVEL1): {
		player_posX = game_info.getLevel1Spawn().x;
		player_posY = game_info.getLevel1Spawn().y;
	}break;
	case(LEVEL2): {
		player_posX = game_info.getLevel2Spawn().x;
		player_posY = game_info.getLevel2Spawn().y;
	}break;
	case(LEVEL3):
	{
		player_posX = game_info.getLevel3Spawn().x;
		player_posY = game_info.getLevel3Spawn().y;
	}break;
	case(LEVEL4):
	{
		player_posX = game_info.getLevel4Spawn().x;
		player_posY = game_info.getLevel4Spawn().y;
	}break;
	}

}






internal void
drawColletableHearts() {
	int collected_coins = 0;
	static int cc = 0;
	mciSendString(L"open ..\\sound\\coin.wav type waveaudio alias coin", NULL, 0, 0);


	if (game_info.isHeartCollected(0) == false) {
		draw_heart(game_info.getCHpos(0).x, game_info.getCHpos(0).y, 2, game_info.getCHcolor(0));
	}
	else if (game_info.isHeartCollected(0) == true) {
		collected_coins++;
	}

	if (game_info.isHeartCollected(1) == false) {
		draw_heart(game_info.getCHpos(1).x, game_info.getCHpos(1).y, 2, game_info.getCHcolor(1));
	}
	else if (game_info.isHeartCollected(1) == true) {
		collected_coins++;
	}

	//beeps once when coin is collected
	if (collected_coins != cc) {
		mciSendString(L"play coin from 1", NULL, 0, 0);

		if (game_info.getLivesLeft() < 3) {
			game_info.setHeart(WHITE, BLACK, game_info.getLivesLeft() + 1);
			//health_points--;
			health_points++;


		}
		cc = collected_coins;
	}
	if (game_info.isHeartCollected(1) || game_info.isHeartCollected(0))
	{
		heart_collected = true;
	}
}

internal void
hearts() {
	//game_info.setHeart(WHITE, BLACK, 3);
	game_info.setLivesLeft(health_points);
	game_info.setHeart(WHITE, BLACK, game_info.getLivesLeft());
	Point heart1Pos(74, 47.5);
	Point heart2Pos(78.5, 47.5);
	Point heart3Pos(83, 47.5);
	game_info.setHeartPosition(heart1Pos, heart2Pos, heart3Pos);
}

internal void
draw_hearts() {
	for (int i = 0; i < 3; i++) {
		draw_heart(game_info.getHeartPos(i).x, game_info.getHeartPos(i).y, 2, game_info.getHeartColor(i));
	}
}


internal void
collision(Coin_State* coins, float dt, GAMEMODE Level) {


	draw_rect(player_posX, player_posY, player_sizex, player_sizey, GREEN, vacancy, bottom, left, right, top, enemy_touched, touched, coins, &game_info.hearts);
	if (!vacancy) {
		if (enemy_touched) {
			enemy_touched = false;
			restart_pos(Level);
			health_points--;
			game_info.setHeart(WHITE, BLACK, health_points);
			//health_points--;
		}
		else {

			clear = false;

			if (bottom == false) {
				yvelocity = 0;
				accel = 0;
			}
			if (left == false) {
				leftclear = false;
				xvelocity = 0;
			}
			else {
				leftclear = true;
			}
			if (right == false) {
				rightclear = false;
				xvelocity = 0;
			}
			else {
				rightclear = true;
			}

			if (top == false) {
				yvelocity = 0;

			}
			//xvelocity = 0;
			player_posX = old_X;
			player_posX2 = old_X2;
			player_posY = old_Y;
			player_posY2 = old_Y2;
			draw_rect(player_posX, player_posY, player_sizex, player_sizey, GREEN);
		}
	}
	else {
		clear = true;
		accel = -70.0;
		yvelocity += accel * dt;

	}
}




internal void
drawLevelCoins() {
	int collected_coins = 0;
	static int cc = 0;
	mciSendString(L"open ..\\sound\\coin.wav type waveaudio alias coin", NULL, 0, 0);

	if (game_info.getCoinCollected(0) == false) {
		draw_circle(game_info.getCoinPos(0).x, game_info.getCoinPos(0).y, 3, game_info.getCoinColor(0));
		draw_circle(-69, 48, 2, WHITE);
	}
	else if (game_info.getCoinCollected(0) == true) {
		draw_circle(-69, 48, 2, game_info.getCoinColor(0));
		collected_coins++;
	}


	if (game_info.getCoinCollected(1) == false) {
		draw_circle(game_info.getCoinPos(1).x, game_info.getCoinPos(1).y, 3, game_info.getCoinColor(1));
		draw_circle(-65, 48, 2, WHITE);
	}
	else if (game_info.getCoinCollected(1) == true) {
		draw_circle(-65, 48, 2, game_info.getCoinColor(1));
		collected_coins++;
	}

	if (game_info.getCoinCollected(2) == false) {
		draw_circle(game_info.getCoinPos(2).x, game_info.getCoinPos(2).y, 3, game_info.getCoinColor(2));
		draw_circle(-61, 48, 2, WHITE);
	}
	else if (game_info.getCoinCollected(2) == true) {
		draw_circle(-61, 48, 2, game_info.getCoinColor(2));
		collected_coins++;
	}

	//beeps once when coin is collected
	if (collected_coins != cc) {
		mciSendString(L"play coin from 1", NULL, 0, 0);
		cc = collected_coins;
	}

}

internal void
drawLevelPowerUps() {


	if (game_info.getPowerUpCollected(PHASE_THROUGH) == false && game_info.getPowerUpInLevel(PHASE_THROUGH)) {
		draw_ticket(game_info.getPowerUpPos(PHASE_THROUGH).x, game_info.getPowerUpPos(PHASE_THROUGH).y, 3, 3, game_info.getPowerUpColor(PHASE_THROUGH));
	}

	if (game_info.getPowerUpCollected(IMMUNITY) == false && game_info.getPowerUpInLevel(IMMUNITY)) {
		draw_ticket(game_info.getPowerUpPos(IMMUNITY).x, game_info.getPowerUpPos(IMMUNITY).y, 3, 3, game_info.getPowerUpColor(IMMUNITY));
	}

	if (game_info.getPowerUpCollected(SHRINK) == false && game_info.getPowerUpInLevel(SHRINK)) {
		draw_ticket(game_info.getPowerUpPos(SHRINK).x, game_info.getPowerUpPos(SHRINK).y, 3, 3, game_info.getPowerUpColor(SHRINK));
	}


}

internal void
drawJumps() {
	printLevelText("Jumps ", 25, -46, WHITE);
	if (game_info.jumps.getJumpAvailable() == 2 ) {

		draw_diamond(50, -45.5, 2, 2, WHITE); 
		draw_diamond(55, -45.5, 2, 2, WHITE);
	}
	if (game_info.jumps.getJumpAvailable() == 1) {

		draw_diamond(50, -45.5, 2, 2, WHITE);
		draw_diamond(55, -45.5, 2, 2, BLACK);
	}
	if (game_info.jumps.getJumpAvailable() == 0) {

		draw_diamond(50, -45.5, 2, 2, BLACK);
		draw_diamond(55, -45.5, 2, 2, BLACK);
	}
}




GAMEMODE options = MAINMENU;
int selected = 1;

float speed = 50.f; //unit per second



internal void
simulate_game(Input* input, float& dt) {
	clear_screen(RED);
	draw_rect(0, 0, 90, 45, LIGHTPINK);


	if (game_info.set == false) {
		game_info.setCHcolor(0xDA189C, 0xDA189D);
		game_info.setCoinsColor(0xFFD800, 0xFFD900, 0xFFDA00);
		game_info.setLevel1Spawn(-82, -41);
		game_info.setLevel2Spawn(0, 41);
		game_info.setLevel3Spawn(-85, -41);
		game_info.setLevel4Spawn(0, 0);
		game_info.shrunk = false;
		game_info.set = true;
	}
	if (options == LEVEL1) {
		
		simulateLevel1(input, dt);
	}
	else if (options == MAINMENU) {
		
		simulateMainMenu(input, dt);
	}
	else if (options == LEVELSELECT) {
		
		simulateLevelSelect(input, dt);
	}
	else if (options == LEVEL2) {
		
		simulateLevel2(input, dt);
	}
	else if (options == LEVEL3) {
		game_info.setLevel3Spawn(-85, -41);
		simulateLevel3(input, dt);
	}
	else if (options == LEVEL4) {
		
		simulateLevel4(input, dt);
	}
	else if (options == FINALSCREEN) {
		
		simulateFinalScreen(input, dt);
	}
}