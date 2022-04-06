typedef unsigned int u32;

#define global_variable static
#define internal static
#define M_PI   3.14159265358979323846


inline int 
clamp(int min, int max, int value) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
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
class gameUtilities {
public:
  bool started_level;
  bool pause;
  bool set;
  Point getLevel1Spawn();
  Point getLevel2Spawn();
  Point getLevel3Spawn();

  void setLevel1Spawn(float x, float y);
  void setLevel2Spawn(float x, float y);
  void setLevel3Spawn(float x, float y);

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



private:
  float spawn_pos[6];
  Point coin_pos[3];
  Point ability_pos[3];
  Ability_State PowerUps = {};

};


Point gameUtilities::getLevel1Spawn() {
  Point level1(spawn_pos[0], spawn_pos[1]);
  return level1;
}
Point gameUtilities::getLevel2Spawn() {
  Point level2(spawn_pos[2], spawn_pos[3]);
  return level2;
}
Point gameUtilities::getLevel3Spawn() {
  Point level3(spawn_pos[4], spawn_pos[5]);
  return level3;
}

void gameUtilities::setLevel1Spawn(float x, float y) {
  spawn_pos[0] = x;
  spawn_pos[1] = y;
}
void gameUtilities::setLevel2Spawn(float x, float y) {
  spawn_pos[2] = x;
  spawn_pos[3] = y;
}
void gameUtilities::setLevel3Spawn(float x, float y) {
  spawn_pos[4] = x;
  spawn_pos[5] = y;
}

void gameUtilities::resetCoinsCollected() {
  for (int i = 0; i < AMOUNT; i++) {
	coins.coin[i].collected = false;
  }
}

void gameUtilities::setCoinsColor(u32 coin1color, u32 coin2color, u32 coin3color) {

  coins.coin[0].color = coin1color;
  coins.coin[1].color = coin2color;
  coins.coin[2].color = coin3color;
}

void gameUtilities::setCoinsPositions(Point coin1Pos, Point coin2Pos, Point coin3Pos) {
  coin_pos[0] = coin1Pos;
  coin_pos[1] = coin2Pos;
  coin_pos[2] = coin3Pos;
}

Point gameUtilities::getCoinPos(int coinNumber) {
  return coin_pos[coinNumber];
}

u32 gameUtilities::getCoinColor(int coinNumber) {
  return  coins.coin[coinNumber].color;
}

bool gameUtilities::getCoinCollected(int coinNumber) {
  return  coins.coin[coinNumber].collected;
}


void gameUtilities::resetPowerUpInfo() {
  for (int i = 0; i < AMOUNT; i++) {
	PowerUps.ability[i].collected = false;
	PowerUps.includedInLevel[i] = false;
  }
}


void gameUtilities::setPowerUpColor(Abilities ability_name, u32 color) {
  PowerUps.ability[ability_name].color = color;
}

void gameUtilities::setPowerUpPosition(Abilities ability_name, Point coordinate) {
  ability_pos[ability_name] = coordinate;
  PowerUps.includedInLevel[ability_name] = true;
}

void gameUtilities::setPowerUpCollected(Abilities ability_name, bool collected) {
   PowerUps.ability[ability_name].collected = collected;
}

Point gameUtilities::getPowerUpPos(Abilities ability_name) {
  return ability_pos[ability_name];
}

u32 gameUtilities::getPowerUpColor(Abilities ability_name) {
  return  PowerUps.ability[ability_name].color;
}


bool gameUtilities::getPowerUpCollected(Abilities ability_name) {
  return  PowerUps.ability[ability_name].collected;
}

bool gameUtilities::getPowerUpInLevel(Abilities ability_name) {
  return PowerUps.includedInLevel[ability_name];
}