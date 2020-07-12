#include <Windows.h>
#include <stdio.h>

#include "MyWindowWithIcon.h"


//macro definitions
#define MY_WINDOW_WIDTH		800U
#define MY_WINDOW_HIGHT		600U

//global variable declarations

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};
bool gbFullScreen = false;
HWND ghwnd = NULL;
FILE *gpFile = NULL;

//winproc declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
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

	//Opening File
	if(fopen_s(&gpFile, "ARC_LOG.TXT", "w") != 0)
	{
		MessageBox(NULL, TEXT("Can Not Create Desired File..."), TEXT("Error"), MB_OK);
		exit(0);
	}


	//code
	//initialization of wndclass
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
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
	hwnd = CreateWindow(	szAppName,
							TEXT("MyWindowWithIcon: Akshay"),
							WS_OVERLAPPEDWINDOW,
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

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);


	//Message Loop
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//closing File
	fclose(gpFile);
	gpFile = NULL;

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function declarations
	void ToggleFullScreen(void);

	//variable declarations
	HDC hdc;
	RECT rc;
	TCHAR str[] = TEXT("Hello World !!!");


	//code
	switch(iMsg)
	{
		case WM_CREATE:
			//Wrinting In File
			fprintf(gpFile, "India Is My Country.\n");
			break;

		case WM_PAINT:
			GetClientRect(hwnd, &rc);
			hdc =GetDC(hwnd);
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(0, 255, 0));
			DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			ReleaseDC(hwnd, hdc);
		break; 

		case WM_KEYDOWN:
				switch(wParam)
				{
					case 0x46:
					case 0x66:
						ToggleFullScreen();
						break;

					default:
						break;
				}
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
