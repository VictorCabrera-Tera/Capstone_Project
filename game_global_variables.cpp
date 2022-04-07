#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!(input->buttons[b].is_down) && input->buttons[b].changed)

float player_posX = 0.f;
float player_posY = 0.f;
float player_posX2 = 100.f;
float player_posY2 = 500.f;

float player_sizex = 2;
float player_sizey = 2;
//Needed to keep track of previous pos for collision
float old_X;
float old_Y;
float old_X2;
float old_Y2;

bool vacancy = true;
bool clear = true;

u32 color1 = RED;
u32 color2 = BLACK;
u32 color3 = BLACK;

int delta = 1;
int count = 0;
int max = 630;
int min = 0;

int delta2 = 1;
int count2 = 0;
int max2 = 300;
int min2 = -600;

float yvelocity;
float xvelocity = 0;
float accel = 50.0;
float enemy_x = -38;
float enemy_y = -15;


float enemy_x2 = 32;

float enemy_y2 = 22;

bool bottom = TRUE;
bool left = TRUE;
bool right = TRUE;
bool top = TRUE;

bool leftclear = FALSE;
bool rightclear = FALSE;

bool levelInfoSet = false;
bool freemode = false;
bool played = false;

//pause variables
int pause_selected = 1;
//bool first_pause = true;
u32 P_color = RED;
u32 P_color1 = YELLOW;
u32 P_color2 = YELLOW;

bool enemy_touched = false;

