#include <Windows.h>

//winproc declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	UINT WinHeight = 0;
	UINT WinWidth = 0;

	UINT VerPos = 0;
	UINT HorPos = 0;

	//code
	//initialization of wndclass
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//Register above Class
	RegisterClassEx(&wndclass);

	//get system hight and width
	WinWidth = GetSystemMetrics(SM_CXSCREEN);
	WinHeight = GetSystemMetrics(SM_CYSCREEN);

	//calculating positions for window
	VerPos = (WinHeight / 2) - 300;
	HorPos = (WinWidth / 2) - 400;

	//Create Window
	hwnd = CreateWindow(	szAppName,
							TEXT("MyCenteredWindow:Akshay"),
							WS_OVERLAPPEDWINDOW,
							HorPos,
							VerPos,
							800,
							600,
							NULL,
							NULL,
							hInstance,
							NULL
						);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//Message Loop
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
