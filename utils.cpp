typedef unsigned int u32;

#define M_PI   3.14159265358979323846

int musc = 0;
static int health_points = 3;

//returns the input depending if its between min and max
int getWithinBounds(int min, int max, int input) {
  if (input < min) {
	return min;
  }
  if (input > max) {
	return max;
  }
  return input;
}


struct Collectables {
  bool collected;
  u32 color;
};

enum Coins {
  Coin1,
  Coin2,
  Coin3,
  AMOUNT,
};


struct Coin_State {
  Collectables coin[AMOUNT];
};

enum Collectable_Heart {
	heart1, heart2, HEART
};

struct HeartInc {
	Collectables heart[HEART];
};


enum Abilities {
  PHASE_THROUGH,
  IMMUNITY,
  SHRINK,
  ABILITY_AMOUNT,
};

struct Ability_State {
  Collectables ability[ABILITY_AMOUNT];
  bool includedInLevel[ABILITY_AMOUNT];
};

enum GAMEMODE {
  MAINMENU,
  LEVELSELECT,
  LEVEL1,
  LEVEL2,
  LEVEL3,
  LEVEL4,
  FINALSCREEN,
};

struct Hearts {
  int lives_left;
  u32 heart_color;
};

enum lives {
	life1, life2, life3, LIVES
};

struct Lives {
  Hearts life[LIVES];
};

class Point {
public:
  Point(float x = 0, float y = 0) {
	Point::x = x;
	Point::y = y;
  }

  float x;
  float y;
};
class Timer {
public:
  int getTime();
  void resetTime();
  void addTime(float added);
private:
  float timeElapsed;

};

// returns how much time elapsed
int Timer::getTime() {
  return timeElapsed;
}
//resets the timer
void Timer::resetTime() {
  timeElapsed = 0;
}
//add the timer by parameter
void Timer::addTime(float added) {
  timeElapsed += added;
}
class Jump {
public:
  void resetJumps();
  void removeJump();
  void addJump();
  int getJumpAvailable();

private:
  bool available[2];
};

//resets the jumps, so they are all available
void Jump::resetJumps() {
	available[0] = true;
	available[1] = true;
}
//remove a jump
void Jump::removeJump() {
	if (available[1] == true) {
		available[1] = false;
	}
	else {
		available[0] = false;
	}

}

//adds a jump back for the player
void Jump::addJump() {
	if (available[0] == false) {
		available[0] = true;
	}
	else if(available[1] == false) {
		available[1] = true;
	}

}

/**
	Will return how many jumps the player has
	@return the amount of jumps left
**/
int Jump::getJumpAvailable() {
	if (available[1] == true && available[0] == true) {
		return 2;
	}
	else if (available[1] == false && available[0] == true) {
		return 1;
	}
	else if (available[1] == false && available[0] == false) {
		return 0;
	}
	
}

class Score {
public:


  void addScore(int amount);
  void resetScore();
  int getScore();


private:
  int score;
 

};
//add the score by a specified amount
void Score::addScore(int amount) {
  score += amount;
}
//returns the score
int Score::getScore() {
  return score;
}
//resets the score
void Score::resetScore() {
  score = 0;
}


class gameUtilities {
public:

  bool started_level;
  bool pause;
  bool set;
  bool shrunk;
  Point getLevel1Spawn();
  Point getLevel2Spawn();
  Point getLevel3Spawn();
  Point getLevel4Spawn();

  void setLevel1Spawn(float x, float y);
  void setLevel2Spawn(float x, float y);
  void setLevel3Spawn(float x, float y);
  void setLevel4Spawn(float x, float y);

  void setCoinsColor(u32 coin1color, u32 coin2color, u32 coin3color);
  void resetCoinsCollected();
  void setCoinsPositions(Point coin1Pos, Point coin2Pois, Point coin3Pos);

  Point getCoinPos(int coinNumber);
  u32 getCoinColor(int coinNumber);
  bool getCoinCollected(int coinNumber);
  Coin_State coins = {};

  void setPowerUpColor(Abilities ability_name, u32 color);
  void resetPowerUpInfo();
  void setPowerUpPosition(Abilities ability_name, Point ability_pos);
  void setPowerUpCollected(Abilities ability_name, bool collected);

  Point getPowerUpPos(Abilities ability_name);
  u32 getPowerUpColor(Abilities ability_name);
  bool getPowerUpCollected(Abilities ability_name);
  bool getPowerUpInLevel(Abilities ability_name);

  Lives hp = {};
  void setHeart(u32 alive, u32 dead, int life_left);
  void setHeartPosition(Point heart1, Point heart2, Point heart3);
  void setLivesLeft(int life_left);
  Point getHeartPos(int heart_index);
  u32 getHeartColor(int heart_index);
  int getLivesLeft();

  void setCollectableHeart();
  void heartIsCollected(int heart_index);
  void setCHpos(Point heart1, Point heart2);
  void setCHcolor(u32 collected, u32 notCollected);
  u32 getCHcolor(int heart_index);
  Point getCHpos(int heart_index);
  bool isHeartCollected(int heart_index);
  HeartInc hearts = {};


  void setImmunityColors(u32 color1, u32 color2);
  u32 getImmunityColor(int color);
  void swapImmunityColors();
  bool getImmunColorSwapped();
  void setImmunColorSwapped(bool set);

  bool ply_game_over_musc = false;
  u32 borderColor;
  u32 bkgColor;
  Timer timer = {};
  
  Point enemy_pos[10];
  Score playerScore = {};
  Jump jumps = {};
private:
  float spawn_pos[8];
  Point coin_pos[3];
  Point ability_pos[3];
  Ability_State PowerUps = {};
  Point lives[3];
  Point heart_pos[2];
  u32 immunityColor[2];
  bool immunityColorSwapped;

};

//returns coordinates for level 1
Point gameUtilities::getLevel1Spawn() {
  Point level1(spawn_pos[0], spawn_pos[1]);
  return level1;
}
//returns coordinates for level 2
Point gameUtilities::getLevel2Spawn() {
  Point level2(spawn_pos[2], spawn_pos[3]);
  return level2;
}
//returns coordinates for level 3
Point gameUtilities::getLevel3Spawn() {
  Point level3(spawn_pos[4], spawn_pos[5]);
  return level3;
}
//returns coordinates for level 4
Point gameUtilities::getLevel4Spawn() {
  Point level4(spawn_pos[6], spawn_pos[7]);
  return level4;
}

//sets coordinates for  level 1 spawnpoint
void gameUtilities::setLevel1Spawn(float x, float y) {
  spawn_pos[0] = x;
  spawn_pos[1] = y;
}

//sets coordinates for  level 2 spawnpoint
void gameUtilities::setLevel2Spawn(float x, float y) {
  spawn_pos[2] = x;
  spawn_pos[3] = y;
}

//sets coordinates for  level 3 spawnpoint
void gameUtilities::setLevel3Spawn(float x, float y) {
  spawn_pos[4] = x;
  spawn_pos[5] = y;
}

//sets coordinates for  level 4 spawnpoint
void gameUtilities::setLevel4Spawn(float x, float y) {
  spawn_pos[6] = x;
  spawn_pos[7] = y;
}

//sets all collectable hearts as uncollected
void gameUtilities::setCollectableHeart() {
	for (int i = 0; i < HEART; i++) {
		hearts.heart[i].collected = false;
	}
}

//sets a specific heart as collected
void gameUtilities::heartIsCollected(int heart_index) {
	hearts.heart[heart_index].collected = true;
}

//sets the position of both collectable hearts 
void gameUtilities::setCHpos(Point heart1, Point heart2) {
	heart_pos[0] = heart1;
	heart_pos[1] = heart2;
}

//returns the position of a collectable heart
Point gameUtilities::getCHpos(int heart_index) {
	return heart_pos[heart_index];
}
//sets the color of both collectable hearts
void gameUtilities::setCHcolor(u32 ch1, u32 ch2) {
	hearts.heart[0].color = ch1;
	hearts.heart[1].color = ch2;
}
//returns the color of a  collectable heart
u32 gameUtilities::getCHcolor(int heart_index) {
	return hearts.heart[heart_index].color;
}

//returns whether a collectable heart has been collected
bool gameUtilities::isHeartCollected(int heart_index) {
	return hearts.heart[heart_index].collected;
}

//marks all coins as uncollected
void gameUtilities::resetCoinsCollected() {
  for (int i = 0; i < AMOUNT; i++) {
	coins.coin[i].collected = false;
  }
}

//sets the color of all three coins
void gameUtilities::setCoinsColor(u32 coin1color, u32 coin2color, u32 coin3color) {

  coins.coin[0].color = coin1color;
  coins.coin[1].color = coin2color;
  coins.coin[2].color = coin3color;
}

//sets the positions of all three coins
void gameUtilities::setCoinsPositions(Point coin1Pos, Point coin2Pos, Point coin3Pos) {
  coin_pos[0] = coin1Pos;
  coin_pos[1] = coin2Pos;
  coin_pos[2] = coin3Pos;
}

//returns the position of a coin
Point gameUtilities::getCoinPos(int coinNumber) {
  return coin_pos[coinNumber];
}

//returns the color of a coin 
u32 gameUtilities::getCoinColor(int coinNumber) {
  return  coins.coin[coinNumber].color;
}

//returns whether a coin has been collected
bool gameUtilities::getCoinCollected(int coinNumber) {
  return  coins.coin[coinNumber].collected;
}

//marks all power ups as uncollected
//marks all power ups as not used within a level(needed when drawing a powerUp)
void gameUtilities::resetPowerUpInfo() {
  for (int i = 0; i < AMOUNT; i++) {
	PowerUps.ability[i].collected = false;
	PowerUps.includedInLevel[i] = false;
  }
}

//set a specified power up's color
void gameUtilities::setPowerUpColor(Abilities ability_name, u32 color) {
  PowerUps.ability[ability_name].color = color;
}

//sets a power ups color
//also marks a power up as included within a level
void gameUtilities::setPowerUpPosition(Abilities ability_name, Point coordinate) {
  ability_pos[ability_name] = coordinate;
  PowerUps.includedInLevel[ability_name] = true;
}

//marks a power up as collected
void gameUtilities::setPowerUpCollected(Abilities ability_name, bool collected) {
   PowerUps.ability[ability_name].collected = collected;
}

//returns the position of a power up
Point gameUtilities::getPowerUpPos(Abilities ability_name) {
  return ability_pos[ability_name];
}

//returns the color of a power up
u32 gameUtilities::getPowerUpColor(Abilities ability_name) {
  return  PowerUps.ability[ability_name].color;
}

//returns whether a power up was collected
bool gameUtilities::getPowerUpCollected(Abilities ability_name) {
  return  PowerUps.ability[ability_name].collected;
}
//returns whether a power up was included in a level
bool gameUtilities::getPowerUpInLevel(Abilities ability_name) {
  return PowerUps.includedInLevel[ability_name];
}

//Stores how many lives are left for the player
//Depending on how many are left, there will be a certain amount of alive hearts and dead hearts
void gameUtilities::setHeart(u32 alive, u32 dead, int life_left) {
  for (int i = 0; i < LIVES; i++) {
	  hp.life[i].lives_left = life_left;
	  if (i < life_left) hp.life[i].heart_color = alive;
	  else hp.life[i].heart_color = dead;
  }
}
//stores how many lives the player has
void gameUtilities::setLivesLeft(int life_left) {
	for (int i = 0; i < LIVES; i++) {
		hp.life[i].lives_left = life_left;
	}
}
//sets the position for the hearts (lives)
void gameUtilities::setHeartPosition(Point heart1, Point heart2, Point heart3) {
	lives[0] = heart1;
	lives[1] = heart2;
	lives[2] = heart3;
}

//gets the position of the hearts representing lives
Point gameUtilities::getHeartPos(int heart_index) {
  return lives[heart_index];
}

//gets the color of the hearts meaning lives
u32 gameUtilities::getHeartColor(int heart_index) {
  return hp.life[heart_index].heart_color;
}

//returns how many lives are left
int gameUtilities::getLivesLeft() {
  return hp.life[0].lives_left;
}

//Sets what two colors the Immunity ability is going to use 
//color1 is for the first batch of enemies
//color2 is for the second batch of enemies
//one of them will be active, and the other is inactive
void gameUtilities::setImmunityColors(u32 color1, u32 color2) {
  immunityColor[0] = color1;
  immunityColor[1] = color2;

}
//returns one of the colors immunity uses to mark wether something is active or inactive
u32 gameUtilities::getImmunityColor(int color) {
  return immunityColor[color];
}
//swaps the colors immunity uses
//swaping will make it so whatever shape was using one color, will now be drawn with the other
void gameUtilities::swapImmunityColors() {
  u32 temp = immunityColor[0];
  immunityColor[0] = immunityColor[1];
  immunityColor[1] = temp;
}

//returns whether the swap occurred
bool gameUtilities::getImmunColorSwapped() {
  return immunityColorSwapped;
}
//sets the value of the swap variable
void gameUtilities::setImmunColorSwapped(bool set) {
  immunityColorSwapped = set;
}