/**
	Will draw the screen to a specified color
	@param color is the color wished to draw the screen
**/
internal void
clear_screen(u32 color) {
  u32* pixel = (u32*)render_state.memory;

  for (int y = 0; y < render_state.height; y++) {
	for (int x = 0; x < render_state.width; x++) {
	  *pixel = color;
	  pixel++;
	}
  }
}


internal void
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

  x0 = clamp(0, render_state.width, x0);
  y0 = clamp(0, render_state.height, y0);
  x1 = clamp(0, render_state.width, x1);
  y1 = clamp(0, render_state.height, y1);

  int temp = (x1 - x0);
  int left = (int)(temp / 4);
  int right = left + left + left;
  int ys = (int)(y0 + y1) / 2;

  for (int y = y0; y < y1; y++) {
	u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
	for (int x = x0; x < x1; x++) {
	  if ((y == ys) || (y == ys + 1) || (y == ys - 1)) {
		if (x == (x0 + left) || x == (x0 + right)) {
		  *pixel = 0x000000;
		}
		else {
		  *pixel = color;
		}
	  }
	  else {
		*pixel = color;
	  }
	  pixel++;
	}
  }

}







//used so its easier to input whole numbers instead of decimals like 100 for 1 when using draw rect
global_variable float render_scale = 0.01f;


internal void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color, bool& vacant, Coin_State* coins) {
  //Change to pixels
  //get the percentage of the screen relative to the current dimensions


  x *= render_state.height * render_scale;
  y *= render_state.height * render_scale;

  half_size_x *= render_state.height * render_scale;
  half_size_y *= render_state.height * render_scale;

  //Need to center it, the window's center is at 0,0

  x += render_state.width / 2.f;
  y += render_state.height / 2.f;


  //simple method to get the min and max points
  int x0 = x - half_size_x;
  int x1 = x + half_size_x;
  int y0 = y - half_size_y;
  int y1 = y + half_size_y;


  x0 = clamp(0, render_state.width, x0);
  y0 = clamp(0, render_state.height, y0);
  x1 = clamp(0, render_state.width, x1);
  y1 = clamp(0, render_state.height, y1);


  
  for (int i = y0; i < y1; i++) {
	u32* lowerL_pixel = (u32*)render_state.memory + x0 + i * render_state.width;

	for (int x = x0; x < x1; x++) {
	  if ((*lowerL_pixel == 0xffff22) || (*lowerL_pixel == 0x00ffff) || (*lowerL_pixel == RED))
	  {
		vacant = false;
		return;
	  }
	  if (*lowerL_pixel == coins->coin[0].color)
	  {
		coins->coin[0].collected = true;
	  }
	  if (*lowerL_pixel == coins->coin[1].color)
	  {
		coins->coin[1].collected = true;
	  }
	  if (*lowerL_pixel == coins->coin[2].color)
	  {
		coins->coin[2].collected = true;
	  }
	  lowerL_pixel++;
	}
  }



  vacant = true;
  draw_rect_in_pixels(x0, y0, x1, y1, color);


}

internal void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {
  x *= render_state.height * render_scale;
  y *= render_state.height * render_scale;

  half_size_x *= render_state.height * render_scale;
  half_size_y *= render_state.height * render_scale;

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



internal void
draw_right_triangle_in_pixels(int x0, int y0, int x1, u32 color) {

  x0 = clamp(0, render_state.width, x0);
  y0 = clamp(0, render_state.height, y0);
  x1 = clamp(0, render_state.width, x1);


  //know how many rows are need to get a right triangle
  int iterations = (x1 - x0);

  int y1 = y0 + (iterations);
  y1 = clamp(0, render_state.height, y1);


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


internal void
draw_right_tri(float start_x, float y, float width, u32 color) {
  start_x *= render_state.height * render_scale;
  y *= render_state.height * render_scale;

  width *= render_state.height * render_scale;

  //Need to center it, the window's center is at 0,0

  start_x += render_state.width / 2.f;
  //width += render_state.width / 2.f;
  y += render_state.height / 2.f;


  int x0 = start_x - width;
  int x1 = start_x + width;


  draw_right_triangle_in_pixels(x0, y, x1, color);

}



internal void
draw_triangle_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

  x0 = clamp(0, render_state.width, x0);
  y0 = clamp(0, render_state.height, y0);
  x1 = clamp(0, render_state.width, x1);
  y1 = clamp(0, render_state.height, y1);

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
internal void
draw_tri(float start_x, float start_y, float width, float height, u32 color) {
  start_x *= render_state.height * render_scale;
  start_y *= render_state.height * render_scale;

  width *= render_state.height * render_scale;
  height *= render_state.height * render_scale;
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

internal void
draw_enemy(int x0, int y0, int x1, int y1, u32 color) {

  x0 = clamp(0, render_state.width, x0);
  y0 = clamp(0, render_state.height, y0);
  x1 = clamp(0, render_state.width, x1);
  y1 = clamp(0, render_state.height, y1);

  int temp1 = x1;
  int temp0 = x0;

  int middle = (x1 + x0) / 2;
  middle = middle - x0;
  int iterations = y0 + (middle / 2);
  iterations = clamp(0, render_state.height, iterations);
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
  iterations = clamp(0, render_state.height, iterations);
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



internal void
draw_coin_in_pixels(int x0, int y0, int x1, int y1, u32 color) {



  x0 = clamp(0, render_state.width, x0);
  y0 = clamp(0, render_state.height, y0);
  x1 = clamp(0, render_state.width, x1);
  y1 = clamp(0, render_state.height, y1);


  int temp1 = x1;
  int temp0 = x0;


  int middle = ((x1 + x0) / 2);
  middle = middle - x0;
  int iterations = y0 + (middle / 2);
  iterations = clamp(0, render_state.height, iterations);

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
  iterations = clamp(0, render_state.height, iterations);

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

internal void
draw_coin(int start_x, int start_y, float width, float height, u32 color) //  Coin_State* Coins, int counter 
{

  //Coins->coin[counter].collected= false;
  start_x *= render_state.height * render_scale;
  start_y *= render_state.height * render_scale;

  width *= render_state.height * render_scale;
  height *= render_state.height * render_scale;
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


/**
	Draws the ticket
	@param x0 is the starting pixel for the x axis
	@param x1 is the ending pixel for the x axis
	@param y0 is the starting pixel for the y axis
	@param y1 is the ending pixel for the y axis

	@param color is the color of the ticket
**/
internal void
draw_ticket_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

  //make sure the parameters are usuable values

  x0 = clamp(0, render_state.width, x0);
  y0 = clamp(0, render_state.height, y0);
  x1 = clamp(0, render_state.width, x1);
  y1 = clamp(0, render_state.height, y1);


  int pixel_x1 = x1; //will store the values 
  int pixel_x0 = x0;


  int middle = ((x1 + x0) / 2); //obtain the average
  middle = middle - x0; //will obtain the distance between the middle and x0

  //Adding y0 by mid/2 will give how many iterations is necessary 
  //The goal is to draw an upside-down trapezoid
  int iterations = y0 + (middle / 2);
  iterations = clamp(0, render_state.height, iterations); //make sure the value is within bounds 


  for (int y = iterations - 1; y > y0; y--) { //start with iterations - 1 since render_state.height is one too high from the limit
	//Each loop will access one row lower
	u32* pixel = (u32*)render_state.memory + pixel_x0 + y * render_state.width;
	for (int x = pixel_x0; x < pixel_x1; x++) {
	  *pixel = color;
	  pixel++;
	}
	pixel_x1--; //decerement the x1 so the for loop will occur one less
	pixel_x0++; //increment so the for loop will start one further and access a pixel further next time
	//Will result in a shorter row below the previous one
  }

  pixel_x1 = x1; //reset the pixels
  pixel_x0 = x0;

  iterations = y0 + (middle / 2);
  iterations = clamp(0, render_state.height, iterations);



  for (int y = y0; y < iterations; y++) {
	//Each loop will access a pixel 1 row above 
	u32* pixel = (u32*)render_state.memory + pixel_x0 + y * render_state.width;
	for (int x = pixel_x0; x < pixel_x1; x++) {
	  //same as previous for loop
	  *pixel = color;
	  pixel++;
	}
	pixel_x1--; //Will result in a shorter row above the previous one
	pixel_x0++;//Will result in a shorter row above the previous one

  }

}

/**
	Caller Function
	Will first adjust the parameters to pixels, then call a function to draw
	@param start_x is the x coordinate for the center of the ticket
	@param start_y is the y coordinate for the center of the ticket
	@param width is the width of the ticket
	@param height is the height of the ticket
	@param color is the color of the ticket
**/
internal void
draw_ticket(int start_x, int start_y, float width, float height, u32 color) {

  //render_scale is so people could use the function without using decimals
  //Will adjust the parameters to a pixel
  start_x *= render_state.height * render_scale;
  start_y *= render_state.height * render_scale;

  width *= render_state.height * render_scale;
  height *= render_state.height * render_scale;

  //Need to center it, the window's center is at 0,0
  start_x += render_state.width / 2.f;
  start_y += render_state.height / 2.f;


  int x0 = start_x - width;
  int x1 = start_x + width;
  int y0 = start_y - height;
  int y1 = start_y + height;

  draw_ticket_in_pixels(x0, y0, x1, y1, color);
}


/**
	Draws the circle
	@param x0 is the starting pixel for the x axis
	@param x1 is the ending pixel for the x axis
	@param y0 is the starting pixel for the y axis
	@param y1 is the ending pixel for the y axis
	@param radius is the circle's radius
	@param centerX is the x coordinate for the center of the circle in pixels
	@param centerY is the y coordinate for the center of the circle in pixels
	@param color is the color of the circle
**/
internal void
draw_circle_in_pixels(int x0, int y0, int x1, int y1, int radius, int centerX, int centerY, u32 color) {

  //makes sure the parameters are usuable values
  x0 = clamp(0, render_state.width, x0);
  y0 = clamp(0, render_state.height, y0);
  x1 = clamp(0, render_state.width, x1);
  y1 = clamp(0, render_state.height, y1);

  for (int y = y0; y < y1; y++) {
	u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width; //get the pixel
	for (int x = x0; x < x1; x++) {
	  //uses the distance formula & equation of a circle 
	  if (abs(int((int)sqrt((pow(x - centerX, 2) + pow(y - centerY, 2))))) < radius) {
		*pixel = color;
	  }
	  pixel++; //access the next pixel

	}
  }

}



/**
	Caller Function
	Will first adjust the parameters to pixels, then call a function to draw
	@param centerX is the x coordinate for the center of the circle
	@param centerY is the y coordinate for the center of the circle
	@param radius is the circle's radius
	@param color is the color of the circle
**/
internal void
draw_circle(int centerX, int centerY, float radius, u32 color) {

  //render_scale is so people could use the function without using decimals
  //Will adjust the centerX and centerY to a pixel
  centerX *= render_state.height * render_scale;
  centerY *= render_state.height * render_scale;

  //Adding by width/height divided by 2 will center it
  centerX += render_state.width / 2.f;
  centerY += render_state.height / 2.f;


  float r0 = radius * render_state.height * render_scale;


  //Get the necessary x0,x1,y0,y1 so we know where to draw the circle
  int x0 = centerX - r0;
  int x1 = centerX + r0;
  int y0 = centerY - r0;
  int y1 = centerY + r0;


  draw_circle_in_pixels(x0, y0, x1, y1, r0, centerX, centerY, color);

}


