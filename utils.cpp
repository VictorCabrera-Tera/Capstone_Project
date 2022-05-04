typedef unsigned int u32;

#define global_variable static
#define internal static
#define M_PI   3.14159265358979323846

int musc = 0;
static int health_points = 3;
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

class Jump {
public:
  void resetJumps();
  void removeJump();
  void addJump();
  int getJumpAvailable();

private:
  bool available[2];
};

void Jump::resetJumps() {
	available[0] = true;
	available[1] = true;
}
void Jump::removeJump() {
	if (available[1] == true) {
		available[1] = false;
	}
	else {
		available[0] = false;
	}

}

void Jump::addJump() {
	if (available[0] == false) {
		available[0] = true;
	}
	else if(available[1] == false) {
		available[1] = true;
	}

}
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
/*
class Score {
public:
  Score() {

	Py_SetProgramName(L"utils");

	Py_Initialize();

	// Load python file
	HANDLE pyFile = CreateFileW(
	  L".\\PyScript.py",
	  GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL
	);


	DWORD pyFileSize = GetFileSize(pyFile, NULL); //returns in bytes
	DWORD memorySize = pyFileSize + 1;
	char* fileStored = new char[memorySize];

	bool fileRead = ReadFile(pyFile, fileStored, pyFileSize, NULL, NULL);
	fileStored[pyFileSize] = '\0'; //adds the null terminator character to the end of the file 

	PyObject* pycompiledCode = nullptr;

	if (fileRead) {

	  pycompiledCode = Py_CompileString(fileStored, "PythonScript.py", Py_file_input); //compiles the python code
	}
	delete[] fileStored;
	CloseHandle(pyFile);

	//......................................................................................................

	pModule = PyImport_ExecCodeModule("PythonScript.py", pycompiledCode);
	pCurrentTime = PyObject_GetAttrString(pModule, "currentTime");
	score = 0;
  }

  void addScore(int amount);
  void resetScore();
  int getScore();
  PyObject* getCurrentTime();
  PyObject* addTimePaused(PyObject* startTime, PyObject* pausedTime);
  int secondsSpent(PyObject* start, PyObject* finish);
  PyObject* pModule;
  PyObject* pCurrentTime;
  PyObject* pStartTime;
  PyObject* pFinishTime;
  PyObject* pPausedTime;

private:
  int score;
 

};
void Score::addScore(int amount) {
  score += amount;
}
int Score::getScore() {
  return score;
}
void Score::resetScore() {
  score = 0;
}
PyObject* Score::getCurrentTime() {
  return PyObject_CallObject(pCurrentTime, NULL);
}
PyObject* Score::addTimePaused(PyObject* startTime, PyObject* pausedTime) {


  PyObject* paddPausedTimeName = PyUnicode_FromString("addTimePaused");
  //PyObject* temp =(pStartTime);
  return PyObject_CallMethodObjArgs(pModule, paddPausedTimeName, startTime, pausedTime, NULL);
  //Py_DECREF(temp);

}
int Score::secondsSpent(PyObject* start, PyObject* finish) {
  PyObject* psecondSpentName = PyUnicode_FromString("secondspent");
  PyObject* ptrResult = PyObject_CallMethodObjArgs(pModule, psecondSpentName, start, finish, NULL);

  int time = _PyLong_AsInt(ptrResult);
  Py_DECREF(ptrResult);
  Py_DECREF(psecondSpentName);
  return time;
}
*/
class gameUtilities {
public:
  ~gameUtilities() {
	
	Py_DECREF(playerScore.pCurrentTime);
	Py_DECREF(playerScore.pModule);
	if (playerScore.pStartTime) {
	  Py_DECREF(playerScore.pStartTime);
	}
	if (playerScore.pFinishTime) {
	  Py_DECREF(playerScore.pFinishTime);
	}
	if (playerScore.pPausedTime) {
	  Py_DECREF(playerScore.pPausedTime);
	}
	Py_Finalize();
	
  }
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
Point gameUtilities::getLevel4Spawn() {
  Point level4(spawn_pos[6], spawn_pos[7]);
  return level4;
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
void gameUtilities::setLevel4Spawn(float x, float y) {
  spawn_pos[6] = x;
  spawn_pos[7] = y;
}

void gameUtilities::setCollectableHeart() {
	for (int i = 0; i < HEART; i++) {
		hearts.heart[i].collected = false;
	}
}

void gameUtilities::heartIsCollected(int heart_index) {
	hearts.heart[heart_index].collected = true;
}

void gameUtilities::setCHpos(Point heart1, Point heart2) {
	heart_pos[0] = heart1;
	heart_pos[1] = heart2;
}

Point gameUtilities::getCHpos(int heart_index) {
	return heart_pos[heart_index];
}
void gameUtilities::setCHcolor(u32 ch1, u32 ch2) {
	hearts.heart[0].color = ch1;
	hearts.heart[1].color = ch2;
}
u32 gameUtilities::getCHcolor(int heart_index) {
	return hearts.heart[heart_index].color;
}

bool gameUtilities::isHeartCollected(int heart_index) {
	return hearts.heart[heart_index].collected;
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

void gameUtilities::setHeart(u32 alive, u32 dead, int life_left) {
  for (int i = 0; i < LIVES; i++) {
	  hp.life[i].lives_left = life_left;
	  if (i < life_left) hp.life[i].heart_color = alive;
	  else hp.life[i].heart_color = dead;
  }
}

void gameUtilities::setLivesLeft(int life_left) {
	for (int i = 0; i < LIVES; i++) {
		hp.life[i].lives_left = life_left;
	}
}
void gameUtilities::setHeartPosition(Point heart1, Point heart2, Point heart3) {
	lives[0] = heart1;
	lives[1] = heart2;
	lives[2] = heart3;
}

Point gameUtilities::getHeartPos(int heart_index) {
  return lives[heart_index];
}

u32 gameUtilities::getHeartColor(int heart_index) {
  return hp.life[heart_index].heart_color;
}

int gameUtilities::getLivesLeft() {
  return hp.life[0].lives_left;
}

