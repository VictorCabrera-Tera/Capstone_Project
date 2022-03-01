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


  for (int y = y0; y < y1; y++) {
	u32* pixel = (u32*)render_state.memory + x0 + y*render_state.width;
	for (int x = x0; x < x1; x++) {
	  *pixel = color;
	  pixel++;
	}
  }
  
}






//used so its easier to input whole numbers instead of decimals like 100 for 1 when using draw rect
global_variable float render_scale = 0.01f;


internal void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color, bool &vacant) {
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
  
  u32* pixel = (u32*)render_state.memory + x1 + y0 * render_state.width;
  if (pixel == nullptr) {
	return;
  }
  if (*pixel == 0x00ffff) {
	vacant = false;
	return;
  }
	vacant = true;

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
draw_right_tri(float start_x, float end_x, float y, u32 color) {
  start_x *= render_state.height * render_scale;
  y *= render_state.height * render_scale;

  end_x *= render_state.height * render_scale;

  //Need to center it, the window's center is at 0,0

  start_x += render_state.width / 2.f;
  end_x += render_state.width / 2.f;
  y += render_state.height / 2.f;


  draw_right_triangle_in_pixels(start_x, y, end_x, color);

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
draw_tri(float start_x, float start_y, float end_x, float end_y ,u32 color) {
  start_x *= render_state.height * render_scale;
  start_y *= render_state.height * render_scale;

  end_x *= render_state.height * render_scale;
  end_y *= render_state.height * render_scale;
  //Need to center it, the window's center is at 0,0

  start_x += render_state.width / 2.f;
  end_x += render_state.width / 2.f;
  start_y += render_state.height / 2.f;
  end_y += render_state.height / 2.f;


  draw_triangle_in_pixels(start_x, start_y, end_x, end_y, color);

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
  int iterations = y0 + (middle/2);
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
  
  iterations = y0 - (middle/2);
  iterations = clamp(0, render_state.height, iterations);
  for (int y = y0; y > iterations; y--) {
	u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
	for (int x = x0; x < x1; x++) {
	  *pixel = color;
	  pixel++;
	}
	x1--;
	x0++;
  }

}
