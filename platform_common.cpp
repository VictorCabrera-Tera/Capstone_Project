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
  BUTTON_COUNT, //Should be the last item, used for keeping track for array of buttons
};

enum COLORDIRECTION{
  INCREMENT,
  DECREMENT,
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