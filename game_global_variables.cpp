float player_posX = 0.f;
float player_posY = 0.f;
float player_posX2 = 100.f;
float player_posY2 = 500.f;

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

int delta1 = 0;

bool isjumping = false;

float jumptime = 0 ;

float yvelocity = 0;
float xvelocity = 0;
float accel = -35.0;
float enemy_x = -38;
float enemy_y = -15;


float enemy_x2 = 32;

float enemy_y2 = 25;

bool bottom = TRUE;
bool left = TRUE;
bool right = TRUE;
bool top = TRUE;

bool leftclear = FALSE;
bool rightclear = FALSE;

bool levelInfoSet = false;
bool played = false;

//pause button variables


bool enemy_touched = false;