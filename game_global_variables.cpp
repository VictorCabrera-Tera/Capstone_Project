
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

int delta = 1;
int count = 0;
int max = 100;
int min = 0;

int delta2 = 1;
int count2 = 0;
int max2 = 100;
int min2 = 0;

float yvelocity;
float xvelocity = 0;
float accel = 15.0;
float enemy_x = 10;
float enemy_y = 10;


float enemy_x2 = 20;

float enemy_y2 = 20;

bool bottom = TRUE;
bool left = TRUE;
bool right = TRUE;
bool top = TRUE;

bool leftclear = FALSE;
bool rightclear = FALSE;



bool coins_set = false;
bool played = false;
