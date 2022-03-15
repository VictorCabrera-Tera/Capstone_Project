#include "utils.cpp"
#include <windows.h>
#include "platform_common.cpp"
#include "math.h"


global_variable bool running = true;



struct Render_State
{
  void* memory;
  int width;
  int height;
  //int render_state.size = 0;
  BITMAPINFO bitmap_info;
};

global_variable Render_State render_state;





#include "renderer.cpp"
#include "text.cpp"
#include "game.cpp"



internal void
DrawScene(HWND hwnd, LPPAINTSTRUCT lpPS) {
  char string[] = "Level 1";
  RECT rect;
  SetRect(&rect, render_state.width/2, 20, render_state.width, 0);
  SetBkMode(lpPS->hdc, TRANSPARENT);
  DrawTextA(lpPS->hdc, string, -1, &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}


//Callback function using the window documentation
LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  //Expected to process messages
  //Whenever a message is dispatched, will do the default behavior

  switch(uMsg)
  {
	//If the message is either a WM_CLOSE or WM_DESTROY (from clicking the X on the window) then set running to false
	case(WM_CLOSE):
	case(WM_DESTROY): {
	  running = false;
	}
	  break;
	//message that window changed size
	case(WM_SIZE): {

	  RECT rect;

	  /*
		obtains the window dimensions by storing the coordinates
		of the upper left and lower right ccoordinates into a
		rectangle specified
	  */
	  GetClientRect(hwnd, &rect);

	  //calculate the width and height of window by using rect
	  render_state.width = rect.right - rect.left;
	  render_state.height = rect.bottom - rect.top;

	  //Need to create a buffer, so need to know how big to make it

	  int size = render_state.width * render_state.height * sizeof(unsigned int);

	  //Release the memory if there was already memory allocated to the previous buffer
	  if (render_state.memory)  VirtualFree(render_state.memory, 0, MEM_RELEASE);



	  //virtualAlloc will allocate memory using:
	  //address, size to alllocate, type, and whether wish read/write from page
	  //BELOW IS SAYING: at address zero, allocate a readable and writable memory of buffer size
	  //MEM_RESERVE will  reserve virtual addre ss space without allocating any actual physical storage
	  //MEM_COMMIT Allocates memory charges (from the overall size of memory and the paging files on disk) for the specified reserved memory pages. 
	  render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);


	  //The buffer memory is a void pointer since it will point to somewhere in memory and we don't care about the type

	  //Best place to set up the bitmapinfo object
	  //This object is needed for the windo to properly copy to the video card
	  render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader); //knoww what version ur using
	  render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
	  render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
	  render_state.bitmap_info.bmiHeader.biPlanes = 1; //For some reason it has to be 1 
	  render_state.bitmap_info.bmiHeader.biBitCount = 32; //The bits for the colors
	  render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;


	} 
	  break;
	//Otherwise, do the default behavior for the message
	case(WM_PAINT): {
	  PAINTSTRUCT ps;
	  //PAINTSTRUCT::fErase;
	  BeginPaint(hwnd, &ps);
	  DrawScene(hwnd, &ps); 
	  EndPaint(hwnd, &ps);
	 
	}break;
	
	//Includes moving the window, minimizing, reshaping
	default:
	  return DefWindowProc(hwnd, uMsg, wParam, lParam);
  };
	return 0;
};


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  //Create a window class
  WNDCLASS window_class = {};

  //Redraw the window virtically and horizontally whenever need to
  window_class.style = CS_HREDRAW | CS_VREDRAW;

  window_class.lpszClassName = L"Game Window Class";


  //This is based on the windows documentation.
  //This will allow the window to send a message whenever something important
  //Change size, active, recieves user input, minimized, etc. 
  window_class.lpfnWndProc = window_callback;


  
  //Register Class
  
  //To register the class based on microsoft windows, you just need to pass the address of the window class object
  RegisterClass(&window_class);

  //Call Create Window

  //the A in createWindowA states that the window name will have non-special characters
  //If you remove that then it will decide which to call
  //Creating an object of HWND will allow us to create the window, and also process the messages from that window
  HWND window = CreateWindow(window_class.lpszClassName, L"My First Game!",
				WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME| WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 
				1280, 720, 0,0,hInstance,0);

  //obtain the device context of the window
  //known as a handle, which is what windows use in order to to draw to it
  HDC hdc = GetDC(window);

  Input input = {};

  //To keep track how much time elapsed for the first frame (assume 60 secs)

  float delta_time = 0.016666f;


  //initialize the counter used
  //Use it at the start and end of each frame to know how much time passed
  LARGE_INTEGER frame_begin_time;


  //The time when the frame starts
  QueryPerformanceCounter(&frame_begin_time);



  float performance_frequency;
  {
	//Will initialize perf, then use function that wil get how many cycles the cpu does in a sec
	LARGE_INTEGER perf;
	QueryPerformanceFrequency(&perf);
	performance_frequency = (float)perf.QuadPart;
  }

  //PlaySound(L"C:\\Users\\steve\\Desktop\\My_First_Cpp_Game\\My_First_Cpp_Game\\Satorl_Marsh2.wav", 0, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
  //C:\Users\steve\Desktop\My_First_Cpp_Game\My_First_Cpp_Game\\Satorl_Marsh_Night.wav
  

  Coin_State coins = {};

  



  //Game Loop to keep window open
  while (running)
  {
	//Input
	
	//Ask windows if there is a message for us

	for (int i = 0; i < BUTTON_COUNT; i++) {
	  input.buttons[i].changed = false;
	}
	
	MSG message;

	//Get all the messages we didn't read so far, and process them individually
	//takes a location of the message, the window, filter (don't care here), flags is to remove the message to read message once
	while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

	  switch(message.message) {
		case(WM_KEYUP):
		case(WM_KEYDOWN): {
		  u32 vk_code = (u32)message.wParam;
		  //bit 31 hold the transition state of the key
		  bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b,vk)\
case (vk): {\
input.buttons[b].changed = is_down != input.buttons[b].is_down;\
input.buttons[b].is_down = is_down;\
} break;

		   
		  switch (vk_code) {
			process_button(BUTTON_UP, VK_UP);
			process_button(BUTTON_DOWN, VK_DOWN);
			process_button(BUTTON_LEFT, VK_LEFT);
			process_button(BUTTON_RIGHT, VK_RIGHT);
			process_button(BUTTON_SPACEBAR, VK_SPACE);
			process_button(BUTTON_ENTER, VK_RETURN);
		  case(VK_ESCAPE):
		  {
			InvalidateRect(window, NULL, TRUE);
		  }
		  }
		} break;
		default:
		  TranslateMessage(&message);
		  DispatchMessage(&message);
	  }
  
	}

	//Simulate
	
	//draw_rect(0,0,20,20,0x00ff22);//x,y,halfx,halfy and color

	simulate_game(&input, delta_time, &coins, window);
	//draw_rect(0, 0, 1, 1, 0x00ff22);

	//if (input.buttons[BUTTON_ENTER].is_down) {

	//}
	
	//Render

	//Send the memory to the window so it can use it

	StretchDIBits(hdc,0,0, render_state.width,render_state.height,0,0,render_state.width, render_state.height,
				  render_state.memory, &render_state.bitmap_info,DIB_RGB_COLORS,SRCCOPY);


	LARGE_INTEGER frame_end_time;
	//time for when the frame ends
	QueryPerformanceCounter(&frame_end_time);
	 
	/*
	(frame_end_time.QuadPart - frame_begin_time.QuadPart) will give cycles / frame
	performance_frequency is cycles / sec
	diving gives you sec / frame, which is needed for the speed of the game
	*/

	delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;

	frame_begin_time = frame_end_time;
	
  }
  ReleaseDC(window, hdc);
};