#include <Windows.h>
#include <stdio.h>

#include "MyOGL_Template.h"


//macro definitions
#define MY_WINDOW_WIDTH		800U
#define MY_WINDOW_HIGHT		600U

//global variable declarations
DWORD dwStyle;
HWND ghwnd = NULL;
FILE *gpFile = NULL;

bool gbFullScreen = false;
bool gbActiveWindow = false;

WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};

//winproc declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//function declaration
	void initialize(void);
	void display(void);

	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	RECT rect;

	UINT WinHeight = 0;
	UINT WinWidth = 0;
	UINT VerPos = 0;
	UINT HorPos = 0;

	bool bDone = false;

	//Opening File
	if(fopen_s(&gpFile, "ARC_LOG.TXT", "w") != 0)
	{
		MessageBox(NULL, TEXT("Can Not Create Desired File..."), TEXT("Error"), MB_OK);
		exit(0);
	}


	//code
	//initialization of wndclass
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	//Register above Class
	RegisterClassEx(&wndclass);

	//BOOL SystemParametersInfo( UINT  uiAction, UINT  uiParam, PVOID pvParam, UINT  fWinIni);
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

	WinWidth = (rect.right);
	WinHeight = (rect.bottom);

	//calculating positions for window top and left
	HorPos = (WinWidth - MY_WINDOW_WIDTH ) / 2;
	VerPos = (WinHeight - MY_WINDOW_HIGHT) / 2;


	//Create Window
	hwnd = CreateWindowEx(	WS_EX_APPWINDOW,
							szAppName,
							TEXT("MyOGL_Template: Akshay"),
							WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
							HorPos,
							VerPos,
							MY_WINDOW_WIDTH,
							MY_WINDOW_HIGHT,
							NULL,
							NULL,
							hInstance,
							NULL
						);

	ghwnd = hwnd;

	initialize();

	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	//Message Loop
	while(bDone == false)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				bDone = true;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if(gbActiveWindow == true)
			{
			//HERE YOU SHOULD CALL UPDATE FUNCTION FOR OPENGL RENDERING
			//HERE YOU SHOULD CALL DISPLAY FUNCTION FOR OPENGL RENDERING
			display();
			}
		}
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function declarations
	void ToggleFullScreen(void);
	void uninitialize(void);
	void resize(int, int);

	//variable declarations

	//code
	switch(iMsg)
	{
		case WM_CREATE:
			//Wrinting In File
			fprintf(gpFile, "India Is My Country.\n");
			break;

		case WM_SETFOCUS:
			gbActiveWindow = true;
				break;

		case WM_KILLFOCUS:
			gbActiveWindow = false;
				break;

		case WM_ERASEBKGND:
				return(0);
				
		case WM_SIZE:
			resize(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_KEYDOWN:
				switch(wParam)
				{
					case 0x46:
					case 0x66:
						ToggleFullScreen();
						break;

					case VK_ESCAPE:
					DestroyWindow(hwnd);
						break;

					default:
						break;
				}
				break;

		case WM_CLOSE:
				DestroyWindow(hwnd);
				break;

		case WM_QUIT:
			uninitialize();
			PostQuitMessage(0);
			break;

		case WM_DESTROY:
			//Writing In File
			fprintf(gpFile, "Jai Hind.\n");
			PostQuitMessage(0);
			break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullScreen(void)
{
	//variable declarations
	MONITORINFO mInfo = {sizeof(MONITORINFO)};

	//code
	if(gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

		if(dwStyle && WS_OVERLAPPEDWINDOW)
		{
			if(GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, 
										MONITORINFOF_PRIMARY), &mInfo))
			{
				SetWindowLong(ghwnd, GWL_STYLE, (dwStyle & ~(WS_OVERLAPPEDWINDOW)));
				SetWindowPos(	ghwnd, HWND_TOP, 
								mInfo.rcMonitor.left, 
								mInfo.rcMonitor.top,
								mInfo.rcMonitor.right - mInfo.rcMonitor.left,
								mInfo.rcMonitor.bottom - mInfo.rcMonitor.top,
								SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
		gbFullScreen = true;
	}

	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(	ghwnd, 
						HWND_TOP, 
						0, 
						0,
						0,
						0,
						SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER |
						SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
		gbFullScreen = false;
	}
}

void initialize(void)
{
	//function declarations
	void resize(int, int);

	//variable declarations

	//code
	resize(MY_WINDOW_WIDTH, MY_WINDOW_HIGHT);
}

void resize(int width, int hight)
{
	//code
	if(hight == 0)
		hight = 1;
}

void display(void)
{
	//code
	
}

void uninitialize(void)
{
	//closing File
	if(gpFile)
	{
		fclose(gpFile);
		gpFile = NULL;
	}
}
