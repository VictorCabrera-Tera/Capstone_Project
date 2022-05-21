#include <windows.h>
#include "utils.cpp"
#include "platform_common.cpp"
#include "math.h"
#define _USE_MATH_DEFINES
#include <cmath>
#pragma comment(lib,"winmm.lib")
#include <string>
bool running = true;

bool pause = false;
int pause_count = 0;
class Render_State
{
public:
	BITMAPINFO bitmap_info;
	int width;
	int height;
	void* memory;
};

Render_State render_state;

gameUtilities game_info;

#include "renderer.cpp"
#include "movement.cpp"
#include "text.cpp"

#include "game.cpp"
#include "level1.cpp"
#include "levelSelect.cpp"
#include "level2.cpp"
#include "level3.cpp"
#include "level4.cpp"
#include "mainMenu.cpp"
#include "FinalScreen.cpp"
#include "pauseMenu.cpp"


/**
	Will update a button's state
	@param button is the button that is being updated
	@param input holds information about the state of each key, and if its being pressed
	@param is_down is the value given by the window message WM_KEYUP & WM_KEYDOWN
**/
void update_button(int button, Input& input, bool is_down) {

  //if the recorded state for a key is different than what the window says it is, then the state has been changed
 
  input.buttons[button].changed = is_down != input.buttons[button].is_down;
  //record what the window message says the state is
  input.buttons[button].is_down = is_down;
;
}





//Callback function using the window documentation
LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	//Expected to process messages
	//Whenever a message is dispatched, will do the default behavior

	switch (uMsg)
	{

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

	case(WM_MOVE): {
		if (game_info.started_level)
		{
			game_info.pause = true;
			//game_info.playerScore.pPausedTime = game_info.playerScore.getCurrentTime();
		}
	}break;
	 //If the message is either a WM_CLOSE or WM_DESTROY (from clicking the X on the window) then set running to false
	case(WM_CLOSE): {
	  running = false;
	}break;
	case(WM_DESTROY): {
	  running = false;
	}break;
	//any other message
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	};
	return 0;
};


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	float cpu_cycles_per_sec;
	{
	  //Will initialize perf, then use function that wil get how many cycles the cpu does in a sec
	  LARGE_INTEGER perf;
	  QueryPerformanceFrequency(&perf);
	  cpu_cycles_per_sec = (float)perf.QuadPart;
	}

	//initialize the counter used
	//Use it at the start and end of each frame to know how much time passed
	LARGE_INTEGER frame_start_time;

	//The time when the frame starts
	QueryPerformanceCounter(&frame_start_time);

	//To keep track how much time elapsed for the first frame (assume 60 secs) 1 / 60 = 0.01666666666

	float dt = 0.01666666666;


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
	HWND window = CreateWindow(window_class.lpszClassName, L"Cubed World",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
		1280, 720, 0, 0, hInstance, 0);

	//obtain the device context of the window
	//known as a handle, which is what windows use in order to to draw to it
	HDC hdc = GetDC(window);


	game_info.pause = false;
	game_info.started_level = false;
	game_info.set = false;

	Input input = {};

	//Game Loop to keep window open
	while (running)
	{
		//Input

		//Ask windows if there is a message for us
		int i = 0;
		while (i < BUTTON_COUNT) {
		  input.buttons[i].changed = false;
		  i++;
		}

		MSG message;

		//Get all the messages we didn't read so far, and process them individually
		//takes a location of the message, the window, filter (don't care here), flags is to remove the message to read message once
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

			switch (message.message) {
			case(WM_KEYDOWN):
			case(WM_KEYUP): {
				u32 vk_code = (u32)message.wParam;
				//bit 31 hold the transition state of the key
				u32 transition_state = (message.lParam & (1 << 31));
				bool is_down = (transition_state == 0);


				switch (vk_code) {
				  case (VK_UP): {
					update_button(BUTTON_UP, input, is_down);
				  } break;
				  case (VK_DOWN): {
					update_button(BUTTON_DOWN, input, is_down);
				  } break; 
				  case (VK_LEFT): {
					update_button(BUTTON_LEFT, input, is_down);
				  } break;
				  case (VK_RIGHT): {
					update_button(BUTTON_RIGHT, input, is_down);
				  } break;
				  case (VK_SPACE): {
					update_button(BUTTON_SPACEBAR, input, is_down);
				  } break;
				  case (VK_RETURN): {
					update_button(BUTTON_ENTER, input, is_down);
				  } break;
				  case (VK_ESCAPE): {
					update_button(BUTTON_ESCAPE, input, is_down);
				  } break;
				}
			} break;
			default:
				TranslateMessage(&message);
				DispatchMessage(&message);
			}

		}


		if (input.buttons[BUTTON_ESCAPE].changed && input.buttons[BUTTON_ESCAPE].is_down) {
			if (game_info.started_level && game_over == false) {
				game_info.pause = !game_info.pause;
				pause_selected = 1; //for resume to be the first to be highlighted red
			}
		}
		if (health_points < 1 && levelInfoSet) //levelInfoSet allows us to know if player started a level
		{
			game_over = true;
		}

		if (game_info.pause == false && game_over == false) {//play through the game
			simulate_game(&input, dt);
			mciSendString(L"resume lvl1", NULL, 0, 0);
			mciSendString(L"resume lvl2", NULL, 0, 0);
			mciSendString(L"resume lvl3", NULL, 0, 0);
		}
		else if (game_over)
		{
			game_over_menu(&input); //game over screen
			mciSendString(L"stop lvl2", NULL, 0, 0);
			mciSendString(L"stop lvl3", NULL, 0, 0);
			mciSendString(L"stop lvl1", NULL, 0, 0);

			//mciSendString(L"play gameover from 0", NULL, 0, 0);
		}
		else if (game_info.pause)
		{
			pauseMenu(&input); //pause screen
			mciSendString(L"pause lvl1", NULL, 0, 0);
			mciSendString(L"pause lvl2", NULL, 0, 0);
			mciSendString(L"pause lvl3", NULL, 0, 0);
		}

		//Render

		//Send the memory to the window so it can use it

		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height,
			render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);


		LARGE_INTEGER frame_finish_time;
		//time for when the frame ends
		QueryPerformanceCounter(&frame_finish_time);

		/*
		(frame_end_time.QuadPart - frame_begin_time.QuadPart) will give cycles / frame
		performance_frequency is cycles / sec
		diving gives you sec / frame, which is needed for the speed of the game
		*/
		float cycles_took = (float)(frame_finish_time.QuadPart - frame_start_time.QuadPart);
		dt = cycles_took / cpu_cycles_per_sec;

		frame_start_time = frame_finish_time;

	}
	ReleaseDC(window, hdc);
};