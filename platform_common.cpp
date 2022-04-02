struct Button_State {
  bool is_down;
  bool changed;
};

enum {
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_LEFT,
  BUTTON_RIGHT,

  BUTTON_SPACEBAR,
  BUTTON_ENTER,
  BUTTON_ESCAPE,
  BUTTON_COUNT, //Should be the last item, used for keeping track for array of buttons
};



enum COLORS {
  RED = 0xFF0000,
  BLUE = 0x0000FF,
  GREEN = 0x00FF00,
  BLACK = 0x000000,
  WHITE = 0xFFFFFF,
  YELLOW = 0xFFFF00,
  GOLD = 0xFFD700,
};

struct Input {
  Button_State buttons[BUTTON_COUNT];
};


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


enum charType {
  alpha,
  symbol,
  integer,
  neither,
};

enum Font {
  square,
  circle,
  triangle,
  ticket,
};


const char* alphabet[26][7] = {
	"   *   ",
	" *   * ",
	"*     *",
	"*******",
	"*     *",
	"*     *",
	"*     *",

	"****** ",
	"*     *",
	"*     *",
	"****** ",
	"*     *",
	"*     *",
	"****** ",

	" ***** ",
	"*     *",
	"*      ",
	"*      ",
	"*      ",
	"*     *",
	" ***** ",

	"****** ",
	"*     *",
	"*     *",
	"*     *",
	"*     *",
	"*     *",
	"****** ",

	"*******",
	"*      ",
	"*      ",
	"*******",
	"*      ",
	"*      ",
	"*******",

	"*******",
	"*      ",
	"*      ",
	"*******",
	"*      ",
	"*      ",
	"*      ",

	" ***** ",
	"*     *",
	"*      ",
	"*  ****",
	"*     *",
	"*     *",
	" ***** ",

	"*     *",
	"*     *",
	"*     *",
	"*******",
	"*     *",
	"*     *",
	"*     *",

	"*******",
	"   *   ",
	"   *   ",
	"   *   ",
	"   *   ",
	"   *   ",
	"*******",

	"*******",
	"   *   ",
	"    *  ",
	"    *  ",
	"    *  ",
	"*   *  ",
	" ***   ",


	"*     *",
	"*   *  ",
	"* *    ",
	"**     ",
	"* *    ",
	"*   *  ",
	"*     *",

	"*      ",
	"*      ",
	"*      ",
	"*      ",
	"*      ",
	"*      ",
	"*******",


	"*     *",
	"* * * *",
	"*  *  *",
	"*     *",
	"*     *",
	"*     *",
	"*     *",


	"*     *",
	"**    *",
	"* *   *",
	"*  *  *",
	"*   * *",
	"*    **",
	"*     *",


	"*******",
	"*     *",
	"*     *",
	"*     *",
	"*     *",
	"*     *",
	"*******",

	"****** ",
	"*     *",
	"*     *",
	"****** ",
	"*      ",
	"*      ",
	"*      ",


	"*******",
	"*     *",
	"*     *",
	"*     *",
	"*  *  *",
	"*******",
	"      *",

	"****** ",
	"*     *",
	"*     *",
	"****** ",
	"*  *   ",
	"*   *  ",
	"*    * ",

	"*******",
	"*      ",
	"*      ",
	"*******",
	"      *",
	"      *",
	"*******",

	"*******",
	"   *   ",
	"   *   ",
	"   *   ",
	"   *   ",
	"   *   ",
	"   *   ",


	"*     *",
	"*     *",
	"*     *",
	"*     *",
	"*     *",
	"*     *",
	"*******",

	"*     *",
	"*     *",
	"*     *",
	"*     *",
	" *   * ",
	"  * *  ",
	"   *   ",

	"*     *",
	"*     *",
	"*     *",
	"*     *",
	"*  *  *",
	"* * * *",
	"*     *",

	"*     *",
	" *   * ",
	"  * *  ",
	"   *   ",
	"  * *  ",
	" *   * ",
	"*     *",


	"*     *",
	" *   * ",
	"  * *  ",
	"   *   ",
	"   *   ",
	"   *   ",
	"   *   ",

	"*******",
	"     * ",
	"    *  ",
	"   *   ",
	"  *    ",
	" *     ",
	"*******",

};

const char* symbols[15][7] = {
  " *  ",
  " *  ",
  " *  ",
  " *  ",
  "    ",
  "*** ",
  "*** ",


  "*  *  ",
  "*  *  ",
  "*  *  ",
  " *  * ",
  "      ",
  "      ",
  "      ",

  " *   * ",
  " *   * ",
  "*******",
  " *   * ",
  "*******",
  " *   * ",
  " *   * ",

  "   *   ",
  "*******",
  "*  *   ",
  "*******",
  "   *  *",
  "*******",
  "   *   ",

  "***   *",
  "* *  * ",
  "*** *  ",
  "   *   ",
  "  * ***",
  " *  * *",
  "*   ***",


  " ***     ",
  "*   *    ",
  " *  *    ",
  "  **     ",
  " *  *    ",
  "*   * *  ",
  " ***   * ",



  "  * ",
  "  * ",
  "  * ",
  " *  ",
  "    ",
  "    ",
  "    ",


  "   * ",
  "  *  ",
  " *   ",
  " *   ",
  " *   ",
  "  *  ",
  "   * ",

  " *   ",
  "  *  ",
  "   * ",
  "   * ",
  "   * ",
  "  *  ",
  " *   ",

  "       ",
  "       ",
  " * * * ",
  "  ***  ",
  " * * * ",
  "       ",
  "       ",

  "       ",
  "       ",
  "   *   ",
  " ***** ",
  "   *   ",
  "       ",
  "       ",


  "    ",
  "    ",
  "    ",
  "    ",
  " *  ",
  " *  ",
  "*   ",

  "       ",
  "       ",
  "       ",
  " ***** ",
  "       ",
  "       ",
  "       ",

  "    ",
  "    ",
  "    ",
  "    ",
  "    ",
  "*** ",
  "*** ",


  "      *",
  "     * ",
  "    *  ",
  "   *   ",
  "  *    ",
  " *     ",
  "*      ",
};

const char* numbers[8][5] = {
  "****",
  "*  *",
  "*  *",
  "*  *",
  "****",

  "*** ",
  "  * ",
  "  * ",
  "  * ",
  "****",

  "****",
  "   *",
  "****",
  "*   ",
  "****",

  "****",
  "   *",
  "****",
  "   *",
  "****",

  "*  *",
  "*  *",
  "****",
  "   *",
  "   *",

  "****",
  "*   ",
  "****",
  "   *",
  "****",

  "*   ",
  "*   ",
  "****",
  "*  *",
  "****",

  "****",
  "   *",
  "   *",
  "   *",
  "   *",
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
  Point(float x, float y) {
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

  void setCoins(Coin_State* coins, u32 coin1color, u32 coin2color, u32 coin3color);
  
private:
  float spawn_pos[6];
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


void gameUtilities::setCoins(Coin_State* coins, u32 coin1color, u32 coin2color, u32 coin3color) {
  for (int i = 0; i < AMOUNT; i++) {
	coins->coin[i].collected = false;
  }
  coins->coin[0].color = coin1color;
  coins->coin[1].color = coin2color;
  coins->coin[2].color = coin3color;
}
