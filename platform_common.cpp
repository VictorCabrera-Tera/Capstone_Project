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
  BUTTON_COUNT, //Should be the last item, used for keeping track for array of buttons
};

struct Input {
  Button_State buttons[BUTTON_COUNT];
};