#include <windows.h>

//winproc declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MYApp");
	
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

	//register above class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(	szAppName,
							TEXT("MyEventWindow:Akshay Chandawale"),
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							NULL,
							NULL,
							hInstance,
							NULL);
	
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//messgaeLoop
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
	
	case WM_CREATE:
		MessageBox(hwnd, TEXT("WM_CREATE Recieved"), TEXT("Message"), MB_OK);
		break;
	
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("WM_LBUTTONDOWN Recieved"), TEXT("MEssage"), MB_OK);
		break;
	
	case WM_RBUTTONDOWN:
		MessageBox(hwnd, TEXT("WM_RBUTTONDOWN Recieved"), TEXT("MESSAGE"), MB_OK);
		break;

	case WM_KEYDOWN:
		MessageBox(hwnd, TEXT("WM_KEYDOWN Recieved"), TEXT("Message"), MB_OK);
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
