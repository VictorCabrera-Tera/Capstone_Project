//used so its easier to input whole numbers instead of decimals like 100 for 1 when using drawing functions
float percent = 0.01;

static void
fill_window(u32 color) {
	//get starting pixel
	u32* pixel = (u32*)render_state.memory;

	//iterate through all the pixels and add the color to it
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel = color;
			pixel++;
		}
	}
}
static void
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel = color;
			pixel++;
		}
	}
}
static void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {
	x *= render_state.height * percent;
	y *= render_state.height * percent;

	half_size_x *= render_state.height * percent;
	half_size_y *= render_state.height * percent;

	//Need to center it, the window's center is at 0,0
	x += render_state.width / 2.f;
	y += render_state.height / 2.f;


	//simple method to get the min and max points
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	draw_rect_in_pixels(x0, y0, x1, y1, color);

}

static void
draw_right_triangle_in_pixels(int x0, int y0, int x1, u32 color) {

	x0 = getWithinBounds(0, render_state.width, x0);
	y0 = getWithinBounds(0, render_state.height, y0);
	x1 = getWithinBounds(0, render_state.width, x1);


	//know how many rows are need to get a right triangle
	int iterations = (x1 - x0);

	int y1 = y0 + (iterations);
	y1 = getWithinBounds(0, render_state.height, y1);


	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel = color;
			pixel++;

		}
		//Will start one more pixel to the right next row
		x0++;
	}
}

static void
draw_right_tri(float start_x, float y, float width, u32 color) {
	start_x *= render_state.height * percent;
	y *= render_state.height * percent;

	width *= render_state.height * percent;

	//Need to center it, the window's center is at 0,0

	start_x += render_state.width / 2.f;
	//width += render_state.width / 2.f;
	y += render_state.height / 2.f;


	int x0 = start_x - width;
	int x1 = start_x + width;


	draw_right_triangle_in_pixels(x0, y, x1, color);

}

static void
draw_triangle_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

	x0 = getWithinBounds(0, render_state.width, x0);
	y0 = getWithinBounds(0, render_state.height, y0);
	x1 = getWithinBounds(0, render_state.width, x1);
	y1 = getWithinBounds(0, render_state.height, y1);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel = color;
			pixel++;
		}
		x1--;
		x0++;
		if (x0 > x1) break; //made the triangle

	}
}
/*
  Will create a triangle, but with a small enough end_y will make a trapezoid
*/
static void
draw_tri(float start_x, float start_y, float width, float height, u32 color) {
	start_x *= render_state.height * percent;
	start_y *= render_state.height * percent;

	width *= render_state.height * percent;
	height *= render_state.height * percent;
	//Need to center it, the window's center is at 0,0

	start_x += render_state.width / 2.f;
	// end_x += render_state.width / 2.f;
	start_y += render_state.height / 2.f;
	// end_y += render_state.height / 2.f;
	int x0 = start_x - width;
	int x1 = start_x + width;
	int y0 = start_y - height;
	int y1 = start_y + height;


	draw_triangle_in_pixels(x0, y0, x1, y1, color);
}
static void         //40    //25    //25    //5
draw_diamond_in_pixels(int x0, int y0, int x1, int y1, u32 color) {
	u32 blue = BLUE;
	x0 = getWithinBounds(0, render_state.width, x0);
	y0 = getWithinBounds(0, render_state.height, y0);
	x1 = getWithinBounds(0, render_state.width, x1);
	y1 = getWithinBounds(0, render_state.height, y1);

	int temp1 = x1;
	int temp0 = x0;

	//normal equilateral triangle
	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + temp0 + y * render_state.width;
		for (int x = temp0; x < temp1; x++)
		{
			*pixel = color;
			pixel++;
		}
		temp1--;
		temp0++;
	}
	temp1 = x1;
	temp0 = x0;

	//inverted equilateral triangle
	for (int y = y0; y * y1 > y1; y--) {
		u32* pixel = (u32*)render_state.memory + temp0 + y * render_state.width;
		//iterations--;
		for (int x = temp0; x < temp1; x++) {
			*pixel = color;
			pixel++;
		}
		temp1--;
		temp0++;
		if (temp0 > temp1) break;
	}

}
static void //40         //15           //15       //5
draw_diamond(float start_x, float start_y, float width, float height, u32 color)
{
	start_x *= render_state.height * percent;
	start_y *= render_state.height * percent;

	width *= render_state.height * percent;
	height *= render_state.height * percent;
	//Need to center it, the window's center is at 0,0

	start_x += render_state.width / 2.f;
	// end_x += render_state.width / 2.f;
	start_y += render_state.height / 2.f;
	// end_y += render_state.height / 2.f;
	int x0 = start_x - width;   //left triangle
	int x1 = start_x + width;  //right of the triangle
	int y0 = start_y - height;
	int y1 = start_y + height;

	draw_diamond_in_pixels(x0, y0, x1, y1, color);
}


static void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color, bool& vacant, bool& bottom, bool& left, bool& right, bool& top, bool& enemy_touched, bool& touched, Coin_State* coins, HeartInc* hearts) {
	//Change to pixels
	//get the percentage of the screen relative to the current dimensions


	x *= render_state.height * percent;
	y *= render_state.height * percent;

	half_size_x *= render_state.height * percent;
	half_size_y *= render_state.height * percent;

	//Need to center it, the window's center is at 0,0

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;


	//simple method to get the min and max points
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;


	x0 = getWithinBounds(0, render_state.width, x0);
	y0 = getWithinBounds(0, render_state.height, y0);
	x1 = getWithinBounds(0, render_state.width, x1);
	y1 = getWithinBounds(0, render_state.height, y1);
	///////


	for (int i = x0; i < x1; i++) {
		u32* bottom_pixels = (u32*)render_state.memory + i + y0 * render_state.width;
		if (*bottom_pixels == RED || *bottom_pixels == DARKORANGE || *bottom_pixels == PURPLE || *bottom_pixels == DARKGREEN)
		{
			bottom = FALSE;
			break;
		}
		bottom_pixels++;



	}

	//if left side touches red set left set left to false
	for (int i = (y0 + 1); i < (y1 - 1); i++) {
		u32* left_pixels = (u32*)render_state.memory + x0 + i * render_state.width;
		if (*left_pixels == RED || *left_pixels == DARKORANGE || *left_pixels == PURPLE || *left_pixels == DARKGREEN)
		{
			left = FALSE;
			break;
		}
		left_pixels++;

	}
	//  if right side touches red set right to false
	for (int i = (y0 + 1); i < (y1 - 1); i++) {
		u32* right_pixels = (u32*)render_state.memory + (x1 - 1) + i * render_state.width;
		if (*right_pixels == RED || *right_pixels == DARKORANGE || *right_pixels == PURPLE || *right_pixels == DARKGREEN)
		{
			right = FALSE;
			break;
		}
		right_pixels++;

	}

	for (int i = (x0 + 2); i < (x1 - 2); i++) {
		u32* top_pixels = (u32*)render_state.memory + i + y1 * render_state.width;
		if (*top_pixels == RED || *top_pixels == DARKORANGE || *top_pixels == PURPLE || *top_pixels == DARKGREEN)
		{
			top = FALSE;
			break;
		}
		//*top_pixels = BLUE;
		top_pixels++;
	}

	for (int i = y0; i < y1; i++) {
		u32* lowerL_pixel = (u32*)render_state.memory + x0 + i * render_state.width;

		for (int x = x0; x < x1; x++) {
			if (*lowerL_pixel == RED || *lowerL_pixel == DARKORANGE || *lowerL_pixel == PURPLE || *lowerL_pixel == DARKGREEN)
			{
				vacant = false;
				return;
			}
			if (*lowerL_pixel == coins->coin[0].color && coins->coin[0].collected == false)
			{
				game_info.playerScore.addScore(100);
				coins->coin[0].collected = true;
			}
			if (*lowerL_pixel == coins->coin[1].color && coins->coin[1].collected == false)
			{
				game_info.playerScore.addScore(100);
				coins->coin[1].collected = true;
			}
			if (*lowerL_pixel == coins->coin[2].color && coins->coin[2].collected == false)
			{
				game_info.playerScore.addScore(100);
				coins->coin[2].collected = true;
			}

			if ((*lowerL_pixel == hearts->heart[0].color)) {
				hearts->heart[0].collected = true;
			}

			if ((*lowerL_pixel == hearts->heart[1].color)) {
				hearts->heart[1].collected = true;
			}

			if ((*lowerL_pixel == BLUE)) {
			  enemy_touched = true;
			}
			if (*lowerL_pixel == game_info.getPowerUpColor(SHRINK)) {
				game_info.setPowerUpCollected(SHRINK, true);
			}
			if (*lowerL_pixel == game_info.getPowerUpColor(PHASE_THROUGH)) {
				game_info.setPowerUpCollected(PHASE_THROUGH, true);
			}
			if (*lowerL_pixel == game_info.getPowerUpColor(IMMUNITY)) {
				game_info.setPowerUpCollected(IMMUNITY, true);
			}
			if (*lowerL_pixel == BLACK) {
				touched = true;
			}
			lowerL_pixel++;
		}
	}
	bottom = TRUE;
	left = TRUE;
	top = TRUE;
	right = TRUE;
	vacant = true;
	draw_rect_in_pixels(x0, y0, x1, y1, color);


}

static void
draw_enemy_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

	x0 = getWithinBounds(0, render_state.width, x0);
	y0 = getWithinBounds(0, render_state.height, y0);
	x1 = getWithinBounds(0, render_state.width, x1);
	y1 = getWithinBounds(0, render_state.height, y1);

	int temp1 = x1;
	int temp0 = x0;

	int middle = (x1 + x0) / 2;
	middle = middle - x0;
	int iterations = y0 + (middle / 2);
	iterations = getWithinBounds(0, render_state.height, iterations);
	for (int y = y0; y < iterations; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel = color;
			pixel++;
		}
		x1--;
		x0++;
	}

	iterations = y0 - (middle / 2);
	iterations = getWithinBounds(0, render_state.height, iterations);
	for (int y = y0 - 1; y > iterations; y--) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel = color;
			pixel++;
		}
		x1--;
		x0++;
	}
}


static void
draw_enemy(int start_x, int start_y, int width, int height, u32 color) //  Coin_State* Coins, int counter 
{

	start_x *= render_state.height * percent;
	start_y *= render_state.height * percent;

	width *= render_state.height * percent;
	height *= render_state.height * percent;
	//Need to center it, the window's center is at 0,0

	start_x += render_state.width / 2.f;
	//x1 += render_state.width / 2.f;
	start_y += render_state.height / 2.f;
	//y1 += render_state.height / 2.f;

	int x0 = start_x - width;
	int x1 = start_x + width;
	int y0 = start_y - height;
	int y1 = start_y + height;

	draw_enemy_in_pixels(x0, y0, x1, y1, color);

}



static void
draw_coin_in_pixels(int x0, int y0, int x1, int y1, u32 color) {



	x0 = getWithinBounds(0, render_state.width, x0);
	y0 = getWithinBounds(0, render_state.height, y0);
	x1 = getWithinBounds(0, render_state.width, x1);
	y1 = getWithinBounds(0, render_state.height, y1);


	int temp1 = x1;
	int temp0 = x0;


	int middle = ((x1 + x0) / 2);
	middle = middle - x0;
	int iterations = y0 + (middle / 2);
	iterations = getWithinBounds(0, render_state.height, iterations);

	for (int y = y0; y < iterations; y++) {
		u32* pixel = (u32*)render_state.memory + temp0 + y * render_state.width;
		for (int x = temp0; x < temp1; x++) {
			*pixel = color;
			pixel++;
		}
		temp1--;
		temp0++;
	}

	temp1 = x1;
	temp0 = x0;

	iterations = y0 - (middle / 2);
	iterations = getWithinBounds(0, render_state.height, iterations);

	for (int y = y0 - 1; y > iterations; y--) {
		u32* pixel = (u32*)render_state.memory + temp0 + y * render_state.width;
		for (int x = temp0; x < temp1; x++) {
			*pixel = color;
			pixel++;
		}
		temp1--;
		temp0++;
	}

}

static void
draw_coin(int start_x, int start_y, int width, int height, u32 color) //  Coin_State* Coins, int counter 
{

	//Coins->coin[counter].collected= false;
	start_x *= render_state.height * percent;
	start_y *= render_state.height * percent;

	width *= render_state.height * percent;
	height *= render_state.height * percent;
	//Need to center it, the window's center is at 0,0

	start_x += render_state.width / 2.f;
	//x1 += render_state.width / 2.f;
	start_y += render_state.height / 2.f;
	//y1 += render_state.height / 2.f;

	int x0 = start_x - width;
	int x1 = start_x + width;
	int y0 = start_y - height;
	int y1 = start_y + height;

	draw_coin_in_pixels(x0, y0, x1, y1, color);

}



static void
draw_ticket_in_pixels(int x0, int y0, int x1, int y1, u32 color) {



	x0 = getWithinBounds(0, render_state.width, x0);
	y0 = getWithinBounds(0, render_state.height, y0);
	x1 = getWithinBounds(0, render_state.width, x1);
	y1 = getWithinBounds(0, render_state.height, y1);


	int temp1 = x1;
	int temp0 = x0;


	int middle = ((x1 + x0) / 2);
	middle = middle - x0;
	int iterations = y0 + (middle / 2);
	iterations = getWithinBounds(0, render_state.height, iterations);

	for (int y = iterations - 1; y > y0; y--) {
		u32* pixel = (u32*)render_state.memory + temp0 + y * render_state.width;
		for (int x = temp0; x < temp1; x++) {
			*pixel = color;
			pixel++;
		}
		temp1--;
		temp0++;
	}

	temp1 = x1;
	temp0 = x0;

	iterations = y0 + (middle / 2);
	iterations = getWithinBounds(0, render_state.height, iterations);

	for (int y = y0; y < iterations; y++) {
		u32* pixel = (u32*)render_state.memory + temp0 + y * render_state.width;
		for (int x = temp0; x < temp1; x++) {
			*pixel = color;
			pixel++;
		}
		temp1--;
		temp0++;
	}

}


static void
draw_ticket(int start_x, int start_y, int width, int height, u32 color) {
	start_x *= render_state.height * percent;
	start_y *= render_state.height * percent;

	width *= render_state.height * percent;
	height *= render_state.height * percent;
	//Need to center it, the window's center is at 0,0

	start_x += render_state.width / 2.f;
	start_y += render_state.height / 2.f;


	int x0 = start_x - width;
	int x1 = start_x + width;
	int y0 = start_y - height;
	int y1 = start_y + height;

	draw_ticket_in_pixels(x0, y0, x1, y1, color);
}



static void
draw_circle_in_pixels(int x0, int y0, int x1, int y1, int radius, int centerX, int centerY, u32 color) {

	x0 = getWithinBounds(0, render_state.width, x0);
	y0 = getWithinBounds(0, render_state.height, y0);
	x1 = getWithinBounds(0, render_state.width, x1);
	y1 = getWithinBounds(0, render_state.height, y1);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {

			if (abs(int((int)sqrt((pow(x - centerX, 2) + pow(y - centerY, 2))))) < radius) {
				*pixel = color;
			}
			pixel++;

		}
	}

}


static void
draw_circle(int centerX, int centerY, int radius, u32 color) {

	centerX *= render_state.height * percent;
	centerY *= render_state.height * percent;


	centerX += render_state.width / 2.f;
	centerY += render_state.height / 2.f;

	float r0 = radius * render_state.height * percent;

	int x0 = centerX - r0;
	int x1 = centerX + r0;
	int y0 = centerY - r0;
	int y1 = centerY + r0;


	draw_circle_in_pixels(x0, y0, x1, y1, r0, centerX, centerY, color);

}
static void
draw_heart_in_pixels(int x0, int y0, int x1, int y1, int start_x, int start_y, float n, u32 color) {

	x0 = getWithinBounds(0, render_state.width, x0);
	y0 = getWithinBounds(0, render_state.height, y0);
	x1 = getWithinBounds(0, render_state.width, x1);
	y1 = getWithinBounds(0, render_state.height, y1);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {

			if (pow(pow(x + start_x, 2) + pow(y - start_y, 2) - pow(n, 2), 3) <= n * pow(x + start_x, 2) * pow(y - start_y, 3)) {
				*pixel = color;
			}
			pixel++;

		}
	}

}

static void
draw_heart(float x, float y, float a, u32 color) {
	x *= -render_state.height * percent;
	y *= render_state.height * percent;
	a *= render_state.height * percent; //size of the heart

	x -= render_state.width / 2.f;
	y += render_state.height / 2.f;

	float x0 = -a * 1.14 - x;
	float x1 = a * 1.14 - x;
	float y0 = a * -1 + y;
	float y1 = a * 1.24 + y;

	draw_heart_in_pixels(x0, y0, x1, y1, x, y, a, color);
}


//type = 1 facing left
//type = 2 facing right
//type = 3 facing down
//type = 4 facing up
//type = 5 full diamond

static void
draw_triangles_in_pixels(int x0, int y0, int x1, int y1, u32 color, int type) {
	x0 = getWithinBounds(0, render_state.width, x0);
	y0 = getWithinBounds(0, render_state.height, y0);
	x1 = getWithinBounds(0, render_state.width, x1);
	y1 = getWithinBounds(0, render_state.height, y1);

	int temp1 = x1;
	int temp0 = x0;

	//normal equilateral triangle
	if (type != 3) {
		for (int y = y0; y < y1; y = y++) {
			u32* pixel = (u32*)render_state.memory + temp0 + y * render_state.width;
			for (int x = temp0; x < temp1; x = x + 1)
			{
				*pixel = color;
				pixel++;
			}
			if (type == 2 || type == 4 || type == 5)
				temp1 = temp1 - 1; // higher decrements make asharper triangle but is scuffed

			if (type == 1 || type == 4 || type == 5)
				temp0++;
		}
	}
	//inverted equilateral triangle
	if (type != 4) {
		for (int y = y0; y * y1 > y1; y--) {
			u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
			//iterations--;
			for (int x = x0; x < x1; x = x + 1) {
				*pixel = color;
				pixel++;
			}
			if (type == 2 || type == 3 || type == 5)
				x1 = x1 - 1; // -2 for sharper triangle


			if (type == 1 || type == 3 || type == 5)
				x0++;
			//if (temp0 > temp1) break;
		}
	}
}

static void
draw_triangles(float start_x, float start_y, float width, float height, u32 color, int type)
{
	start_x *= render_state.height * percent;
	start_y *= render_state.height * percent;

	width *= render_state.height * percent;
	height *= render_state.height * percent;
	//Need to center it, the window's center is at 0,0

	start_x += render_state.width / 2.f;
	start_y += render_state.height / 2.f;

	int x0 = start_x - width;   //left triangle
	int x1 = start_x + width;  //right of the triangle
	int y0 = start_y - height;
	int y1 = start_y + height;

	draw_triangles_in_pixels(x0, y0, x1, y1, color, type);
}