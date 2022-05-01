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

int delta = 0;

int delta1 = 1;
int delta2 = 1;
int delta3 = 0; 
int delta4 = 0;
int delta5 = 1;
int delta6 = 0;

int delta7 = 1;
int delta8 = 0;
int delta9 = 0;
int delta10 = 0;
int delta11 = 0;
int delta12 = 1;
int delta13 = 0;
int delta14 = 1;
int delta15 = 0;
int delta16 = 0;

bool isjumping = false;

float jumptime = 0;

float yvelocity = 0;
float xvelocity = 0;
//float accel = 140.0;
float accel = -50;

bool bottom = TRUE;
bool left = TRUE;
bool right = TRUE;
bool top = TRUE;
bool touched = FALSE;

bool leftclear = FALSE;
bool rightclear = FALSE;

bool levelInfoSet = false;
bool freemode = false;
bool played = false;

//pause variables
int pause_selected = 1;
u32 P_color = RED;
u32 P_color1 = YELLOW;
u32 P_color2 = YELLOW;

//game_over varaibles
int over_selected = 1;
bool game_over = false;
bool heart_collected = false; 
u32 G_color = WHITE;
u32 G_color1 = BLUE;
u32 G_color2 = BLUE;


bool enemy_touched = false;
u32 fakeWall = RED;
