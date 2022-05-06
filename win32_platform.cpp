#include <Python.h>
#include <windows.h>
#include "utils.cpp"
#include "platform_common.cpp"
#include "math.h"
#define _USE_MATH_DEFINES
#include <cmath>
#pragma comment(lib,"winmm.lib")
#include <string>
global_variable bool running = true;

bool pause = false;
int pause_count = 0;
struct Render_State
{
	void* memory;
	int width;
	int height;
	//int render_state.size = 0;
	BITMAPINFO bitmap_info;
};

global_variable Render_State render_state;

global_variable gameUtilities game_info;

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







//Callback function using the window documentation
LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	//Expected to process messages
	//Whenever a message is dispatched, will do the default behavior

	switch (uMsg)
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

	case(WM_MOVE): {
		if (game_info.started_level)
		{
			game_info.pause = true;
			//game_info.playerScore.pPausedTime = game_info.playerScore.getCurrentTime();
		}
	}break;
		//Includes moving the window, minimizing, reshaping
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	};
	return 0;
};


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	//Py_Initialize();
	//Py_Finalize();
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
	HWND window = CreateWindow(window_class.lpszClassName, L"Cube World",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
		1280, 720, 0, 0, hInstance, 0);

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



	game_info.pause = false;
	game_info.started_level = false;
	game_info.set = false;

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

			switch (message.message) {
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
					process_button(BUTTON_ESCAPE, VK_ESCAPE);

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
				/*
				if (!game_info.pause) {
					 game_info.playerScore.pFinishTime = game_info.playerScore.getCurrentTime();
					int time = game_info.playerScore.secondsSpent(game_info.playerScore.pStartTime, game_info.playerScore.pFinishTime);
					game_info.playerScore.pStartTime = game_info.playerScore.addTimePaused(game_info.playerScore.pStartTime, game_info.playerScore.pPausedTime);
					time = game_info.playerScore.secondsSpent(game_info.playerScore.pStartTime, game_info.playerScore.pFinishTime);
					int x = time;
				}
				else {
					game_info.playerScore.pPausedTime = game_info.playerScore.getCurrentTime();

				}
				*/
			}
		}
		if (health_points < 1 && levelInfoSet)
		{
			game_over = true;
		}

		if (game_info.pause == false && game_over == false) {
			simulate_game(&input, delta_time);
			//mciSendString(L"resume bgm", NULL, 0, 0);
			mciSendString(L"resume lvl1", NULL, 0, 0);
			mciSendString(L"resume lvl2", NULL, 0, 0);
			mciSendString(L"resume lvl3", NULL, 0, 0);
		}
		else if (game_over)
		{
			game_over_menu(&input);
			mciSendString(L"stop lvl2", NULL, 0, 0);
			mciSendString(L"stop lvl3", NULL, 0, 0);
			//mciSendString(L"play gameover from 0", NULL, 0, 0);
		}
		else if (game_info.pause)
		{
			pauseMenu(&input);
			mciSendString(L"pause lvl1", NULL, 0, 0);
			mciSendString(L"pause lvl2", NULL, 0, 0);
			mciSendString(L"pause lvl3", NULL, 0, 0);
		}

		//Render

		//Send the memory to the window so it can use it

		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height,
			render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);


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