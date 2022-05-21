#include "game_global_variables.cpp"

void simulateLevel1(Input* input, float& dt);
void simulateMainMenu(Input* input, float& dt);
void simulateLevel2(Input* input, float& dt);
void simulateLevel3(Input* input, float& dt);
void simulateLevel4(Input* input, float& dt);
void simulateLevelSelect(Input* input, float& dt);
void simulateFinalScreen(Input* input, float& dt);

/**
   Will reset the player's pos to a spawnpoint
   @param Level is the current level being played
   @post player's position will be changed to the current level's spawnpoint
**/
static void
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





/**
   Will draw the collectable hearts in the level
**/
static void
drawColletableHearts() {
	int collected_coins = 0;
	static int cc = 0;
	mciSendString(L"open ..\\sound\\coin.wav type waveaudio alias coin", NULL, 0, 0);

	//checks if the heart has been collected
	if (game_info.isHeartCollected(0) == false) { //not collected
	  //draw heart at the heart's coordinates using its designated color
		draw_heart(game_info.getCHpos(0).x, game_info.getCHpos(0).y, 2, game_info.getCHcolor(0));
	}
	else if (game_info.isHeartCollected(0) == true) { 
		collected_coins++; //variable that keeps track if something has been collected, so sound effect plays once
	}

	if (game_info.isHeartCollected(1) == false) {
		draw_heart(game_info.getCHpos(1).x, game_info.getCHpos(1).y, 2, game_info.getCHcolor(1));
	}
	else if (game_info.isHeartCollected(1) == true) {
		collected_coins++;
	}

	//beeps once when heart is collected
	if (collected_coins != cc) { 
		mciSendString(L"play coin from 1", NULL, 0, 0); //plays sound effect

		if (game_info.getLivesLeft() < 3) {
		  //if player is missing any lives, replenish a life by setting +1 hearts to white
			game_info.setHeart(WHITE, BLACK, game_info.getLivesLeft() + 1); 
			//health_points--;
			health_points++; //add the extra life


		}
		cc = collected_coins;
	}
	if (game_info.isHeartCollected(1) || game_info.isHeartCollected(0))
	{
		heart_collected = true;
	}
}

/**
   Will set the player's lives on top top right
   @post sets the amount of lives a player has when they begin a level
   @post sets all of their remaining lives with White hearts
   @post sets the hearts at their designated positions
**/
static void
hearts() {
	//game_info.setHeart(WHITE, BLACK, 3);
	game_info.setLivesLeft(health_points);
	game_info.setHeart(WHITE, BLACK, game_info.getLivesLeft());
	Point heart1Pos(74, 47.5);
	Point heart2Pos(78.5, 47.5);
	Point heart3Pos(83, 47.5);
	game_info.setHeartPosition(heart1Pos, heart2Pos, heart3Pos);
}

/**
   Will draw the hearts on the top right of the border
**/
static void
draw_hearts() {
	for (int i = 0; i < 3; i++) {
		draw_heart(game_info.getHeartPos(i).x, game_info.getHeartPos(i).y, 2, game_info.getHeartColor(i));
	}
}

/**
   Will control where a player is allowed to move
   @param coins is pointer to a coin_state object, which holds 
		  information about the coin's colors and whether its been collected
   @param dt is the delta time of the game, meaning how much time the game is taking for a single frame
   @param Level is the current level of the game
**/
static void
collision(Coin_State* coins, float dt, GAMEMODE Level) {


	//attemps to draw the player at a position, while also checking if the player collected coins or power-Ups
	draw_rect(player_posX, player_posY, player_sizex, player_sizey, GREEN, vacancy, bottom, left, right, top, enemy_touched, touched, coins, &game_info.hearts);
	if (!vacancy) { //if encountered a wall, platform, or enemy
		if (enemy_touched) {
			enemy_touched = false;
			restart_pos(Level); //go back to spawn
			health_points--;
			game_info.setHeart(WHITE, BLACK, health_points); //set on of the hearts to black 
			//health_points--;
		}
		else {

			clear = false;
			//found a wall or platform 
			//depending on what side, stop movement
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
			//redraw the shape at the last free space
			player_posX = old_X;
			player_posX2 = old_X2;
			player_posY = old_Y;
			player_posY2 = old_Y2;
			draw_rect(player_posX, player_posY, player_sizex, player_sizey, GREEN);
		}
	}
	else {
	  //was able to draw the player at the spot, so apply gravity
		clear = true;
		accel = -70.0;
		yvelocity += accel * dt;

	}
}



/**
   Will draw the coins in a level
**/
static void
drawLevelCoins() {
	int collected_coins = 0;
	static int cc = 0;
	mciSendString(L"open ..\\sound\\coin.wav type waveaudio alias coin", NULL, 0, 0);

	//check if a coin has been collected
	if (game_info.getCoinCollected(0) == false) { //not collected
		draw_circle(game_info.getCoinPos(0).x, game_info.getCoinPos(0).y, 3, game_info.getCoinColor(0)); //draw coin at its positions with its color
		draw_circle(-69, 48, 2, WHITE); //draw the coin slot at the top left border as white
	}
	else if (game_info.getCoinCollected(0) == true) { //collected coin
		draw_circle(-69, 48, 2, game_info.getCoinColor(0)); //draw the coin at the top left border
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

/**
   Will draw any power ups that are within a level
**/
static void
drawLevelPowerUps() {

  //checks if a powerUp is a part of the level design and if it has not been collected yet
	if (game_info.getPowerUpCollected(PHASE_THROUGH) == false && game_info.getPowerUpInLevel(PHASE_THROUGH)) {
	  //draw power up
		draw_ticket(game_info.getPowerUpPos(PHASE_THROUGH).x, game_info.getPowerUpPos(PHASE_THROUGH).y, 3, 3, game_info.getPowerUpColor(PHASE_THROUGH));
	}

	if (game_info.getPowerUpCollected(IMMUNITY) == false && game_info.getPowerUpInLevel(IMMUNITY)) {
		draw_ticket(game_info.getPowerUpPos(IMMUNITY).x, game_info.getPowerUpPos(IMMUNITY).y, 3, 3, game_info.getPowerUpColor(IMMUNITY));
	}

	if (game_info.getPowerUpCollected(SHRINK) == false && game_info.getPowerUpInLevel(SHRINK)) {
		draw_ticket(game_info.getPowerUpPos(SHRINK).x, game_info.getPowerUpPos(SHRINK).y, 3, 3, game_info.getPowerUpColor(SHRINK));
	}


}

/**
	Draws the Jump text and diamonds signifying how many jumps are left
**/
static void
drawJumps() {
	printLevelText("Jumps ", 25, -46, WHITE);
	//White means its available, black if for a jump that is not used
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




GAMEMODE options = MAINMENU;  //used for switching between the screen
int selected = 1;

float speed = 50.f; //unit per second



static void
simulate_game(Input* input, float& dt) {
	//sets the default border to be red, and background color to be white
	if (!game_info.started_level) { 
	  game_info.borderColor = RED; 
	  game_info.bkgColor = WHITE;
	}
	fill_window(game_info.borderColor); //draws the border by filling the screen
	draw_rect(0, 0, 90, 45, game_info.bkgColor); //draws the background ontop of border


	if (game_info.set == false) { 
	  //set values shared across the game
	  //coin colors, collectable heart colors, spawns, and player not being shrunken down
		game_info.setCHcolor(0xDA189C, 0xDA189D);
		game_info.setCoinsColor(0xFFD800, 0xFFD900, 0xFFDA00);
		game_info.setLevel1Spawn(-82, -41);
		game_info.setLevel2Spawn(0, 41);
		game_info.setLevel3Spawn(-85, -41);
		game_info.setLevel4Spawn(0, 5);
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