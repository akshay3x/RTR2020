#include <Windows.h>
#include <stdio.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <math.h>

#include "resource.h"

//library inclusion/linking
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#pragma comment(lib, "winmm.lib") // for PlaySound()

//macro definitions
#define WIN_WIDTH 	800
#define WIN_HIGHT 	600
#define GL_PI		3.1415926535

//window procedure
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};

bool gbFullscreen = false;
bool gbActiveWindow = false;
FILE *gpFile = NULL;

GLfloat moveLetter_I = 1.8f;
GLfloat moveLetter_A = 1.8f;
GLfloat moveLetter_N = 1.8f;
GLfloat moveLetter_I2 = 1.8f;
GLfloat moveLetter_D = 0.0f;
GLfloat movePlanesHor = -2.0f;
GLfloat movePlanesVer = 0.0f;
GLfloat showFlag = 0.0f;


GLint I_flag = 0;
GLint N_flag = 0;
GLint D_flag = 0;
GLint I2_flag = 0;
GLint A_flag = 0;
GLint Planes_flag = 0;
GLint DrawFlag_flag = 0;

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	
	//function declations
	void initialize(void);
	void display(void);
	void uninitialize(void);
	void update (void);

	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("OpenGL Window");
	RECT rect;
	bool bDone = false;

	UINT VerPos;
	UINT HorPos;

	//code
	//Creating log file
	if(fopen_s(&gpFile, "ARC_LOG.TXT", "w") != 0)
	{
		MessageBox(NULL, TEXT("Can Not Open Desired File..."),TEXT("Error"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "DEBUG:Log File Created Successfully\n");
	}
	
	//initializing winndow class
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbWndExtra = 0;
	wndclass.cbClsExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance , MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(hInstance , MAKEINTRESOURCE(MYICON));
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;


	//Registering above class
	RegisterClassEx(&wndclass);
	fprintf(gpFile, "DEBUG:Class Registered Successfully\n");
	
	//SystemParametersInfo
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

	HorPos = (rect.right - WIN_WIDTH) / 2;
	VerPos = (rect.bottom - WIN_HIGHT) / 2;

	//creating window
	hwnd = CreateWindowEx(	WS_EX_APPWINDOW,
							szAppName,
							TEXT("OpenGLWindow"),
							WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
							HorPos,
							VerPos,
							WIN_WIDTH,
							WIN_HIGHT,
							NULL,
							NULL,
							hInstance,
							NULL);

	fprintf(gpFile, "DEBUG:Window Created\n");

	ghwnd = hwnd;
	initialize();
	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	//MessageLoop
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
				update();
			}
		}
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function declarations
	void ToggleFullscreen(void);
	void uninitialize(void);
	void resize(int, int);
	void display(void);
	void playSound(void);

	//code
	switch(iMsg)
	{
		case WM_CREATE:
			fprintf(gpFile, "DEBUG:WM_CREATE Recieved\n");
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
					ToggleFullscreen();
					break;

				case VK_ESCAPE:
					DestroyWindow(hwnd);
					break;

				case 0x47:
				case 0x67:
					moveLetter_I = 1.8f;
					moveLetter_A = 1.8f;
					moveLetter_N = 1.8f;
					moveLetter_I2 = 1.8f;
					moveLetter_D = 0.0f;
					movePlanesHor = -2.0f;
					movePlanesVer = 0.0f;

					I_flag = 0;
					N_flag = 0;
					D_flag = 0;
					I2_flag = 0;
					A_flag = 0;
					Planes_flag = 0;
					DrawFlag_flag = 0;
					playSound();
					break;

				default:
					break;
			}
			break;

		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;

		case WM_DESTROY:
			fprintf(gpFile, "DEBUG:WM_DESTROY Recieved\n");
			uninitialize();
			PostQuitMessage(0);
			break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullscreen(void)
{
	//variable declarations
	MONITORINFO mInfo = {sizeof(MONITORINFO)};

	//code
	if(gbFullscreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if(dwStyle && WS_OVERLAPPEDWINDOW)
		{
			if(GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mInfo))
			{
				SetWindowLong(ghwnd, GWL_STYLE, (dwStyle & ~(WS_OVERLAPPEDWINDOW)));
				SetWindowPos(	ghwnd,
								HWND_TOP,
								mInfo.rcMonitor.left,
								mInfo.rcMonitor.top,
								mInfo.rcMonitor.right - mInfo.rcMonitor.left,
								mInfo.rcMonitor.bottom - mInfo.rcMonitor.top,
								SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
		gbFullscreen = true;
	}

	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd,
					HWND_TOP,
					0,
					0,
					0,
					0,
					SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

				ShowCursor(TRUE);
				gbFullscreen = false;
	}
}

void initialize(void)
{
	//function declarations
	void resize(int, int);
	void playSound(void);
	
	//variable declarations
	PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR)};
	int iPixelFormatIndex;

	//code
	ghdc = GetDC(ghwnd);
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

	//pfd.cDepthBits = 32;

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if(iPixelFormatIndex == 0)
	{
		fprintf(gpFile, "DEBUG:ChoosePixelFormat() Failed\n");
		DestroyWindow(ghwnd);
	}

	if(SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(gpFile, "DEBUG:SetPixelFormat() Failed\n");
		DestroyWindow(ghwnd);
	}
	
	ghrc = wglCreateContext(ghdc);

	if(ghrc == NULL)
	{
		fprintf(gpFile, "DEBUG:wglCreateContext() Failed\n");
		DestroyWindow(ghwnd);
	}

	if(wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFile, "DEBUG:wgl_MakeContext() Failed\n");
		DestroyWindow(ghwnd);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	playSound();

	//WarmUp resize() Call
	resize(WIN_WIDTH, WIN_HIGHT);

}

void playSound(void)
{
	PlaySound(MAKEINTRESOURCE(IDWAV_AUDIO_1), // ID of WAVE resource
		GetModuleHandle(NULL), 					 // handle of this module, which contains the resource
		SND_RESOURCE | SND_ASYNC);				 // ID is of type resource | play async (i.e. non-blocking)

}

void resize(int width, int hight)
{
	//code
	if(hight == 0)
		hight = 1;

	glViewport(0, 0, GLsizei(width), GLsizei(hight));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width/(GLfloat)hight, 0.1f, 100.0f);

}

void display(void)
{

	//function declarations
	void drawLetterI(void);
	void drawLetterN(void);
	void drawLetterD(void);
	void drawLetterI2(void);
	void drawLetterA(void);
	void drawPlanes(void);
	void drawFlagA(void);

	//code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -3.0f);

	drawLetterI();
	drawLetterA();
	drawLetterN();
	drawLetterI2();
	drawLetterD();
	if(Planes_flag == 1)
		drawPlanes();
	if(DrawFlag_flag == 1)
		drawFlagA();
	SwapBuffers(ghdc);
}


void drawLetterI(void)
{
//----- I ------------------------------------------------------

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.40f, 0.0f);
			glVertex3f(-0.90f - moveLetter_I, 0.30f, 0.0f);
			glVertex3f(-0.75f - moveLetter_I, 0.30f, 0.0f);
			glVertex3f(-0.75f - moveLetter_I, 0.25f, 0.0f);
			glVertex3f(-0.90f - moveLetter_I, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-0.90f - moveLetter_I, -0.30f, 0.0f);
			glVertex3f(-0.75f - moveLetter_I, -0.30f, 0.0f);
			glVertex3f(-0.75f - moveLetter_I, -0.25f, 0.0f);
			glVertex3f(-0.90f - moveLetter_I, -0.25f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.4f, 0.0f);
			glVertex3f(-0.85f - moveLetter_I, 0.3f, 0.0f);
			glVertex3f(-0.80f - moveLetter_I, 0.3f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.80f - moveLetter_I,  0.0f, 0.0f);
			glVertex3f(-0.85f - moveLetter_I, 0.0f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.80f - moveLetter_I, 0.0f, 0.0f);
			glVertex3f(-0.85f - moveLetter_I, 0.0f, 0.0f);
			
		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-0.85f - moveLetter_I, -0.3f, 0.0f);
			glVertex3f(-0.80f - moveLetter_I, -0.3f, 0.0f);
	glEnd();

}
void drawLetterN(void)
{
//-------- N ---------------------------------------------------
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.4f, 0.0f);
			glVertex3f(-0.65f, 0.3f - moveLetter_N, 0.0f);
			glVertex3f(-0.60f, 0.3f - moveLetter_N, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.60f, 0.0f - moveLetter_N, 0.0f);
			glVertex3f(-0.65f, 0.0f - moveLetter_N, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.60f, 0.0f - moveLetter_N, 0.0f);
			glVertex3f(-0.65f, 0.0f - moveLetter_N, 0.0f);
			
		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-0.65f, -0.3f - moveLetter_N, 0.0f);
			glVertex3f(-0.60f, -0.3f - moveLetter_N, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.4f, 0.0f);
			glVertex3f(-0.45f, 0.3f - moveLetter_N, 0.0f);
			glVertex3f(-0.40f, 0.3f - moveLetter_N, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.40f, 0.0f - moveLetter_N, 0.0f);
			glVertex3f(-0.45f, 0.0f - moveLetter_N, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.40f, 0.0f - moveLetter_N, 0.0f);
			glVertex3f(-0.45f, 0.0f - moveLetter_N, 0.0f);
			
		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-0.45f, -0.3f - moveLetter_N, 0.0f);
			glVertex3f(-0.40f, -0.3f - moveLetter_N, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.4f, 0.0f);
			glVertex3f(-0.65f, 0.3f - moveLetter_N, 0.0f);
			glVertex3f(-0.60f, 0.3f - moveLetter_N, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.50f, 0.0f - moveLetter_N, 0.0f);
			glVertex3f(-0.55f, 0.0f - moveLetter_N, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.50f, 0.0f - moveLetter_N, 0.0f);
			glVertex3f(-0.55f, 0.0f - moveLetter_N, 0.0f);
			
		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-0.45f, -0.3f - moveLetter_N, 0.0f);
			glVertex3f(-0.40f, -0.3f - moveLetter_N, 0.0f);
	glEnd();

}
void drawLetterD(void)
{
	glScalef(moveLetter_D, moveLetter_D, moveLetter_D);
//------ D ---------------------------------------------------
//1
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.4f, 0.0f);
			glVertex3f(-0.25f, 0.3f, 0.0f);
			glVertex3f(-0.20f, 0.3f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.20f, 0.0f, 0.0f);
			glVertex3f(-0.25f, 0.0f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.20f, 0.0f, 0.0f);
			glVertex3f(-0.25f, 0.0f, 0.0f);
			
		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-0.25f, -0.3f, 0.0f);
			glVertex3f(-0.20f, -0.3f, 0.0f);
		glEnd();

//2
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.4f, 0.0f);
			glVertex3f(-0.25f, 0.3f, 0.0f);
			glVertex3f(-0.10f, 0.3f, 0.0f);
			glVertex3f(-0.10f, 0.25f, 0.0f);
			glVertex3f(-0.25f, 0.25f, 0.0f);
	glEnd();

//3
	glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-0.25f, -0.3f, 0.0f);
			glVertex3f(-0.10f, -0.3f, 0.0f);
			glVertex3f(-0.10f, -0.25f, 0.0f);
			glVertex3f(-0.25f, -0.25f, 0.0f);
	glEnd();

//4
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.4f, 0.0f);
			glVertex3f(-0.10f,  0.3f, 0.0f);
			glVertex3f(-0.10f,  0.25f, 0.0f);
			glVertex3f( 0.00f,  0.15f, 0.0f);
			glVertex3f( 0.05f,  0.15f, 0.0f);
	glEnd();

//5
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.4f, 0.0f);
			glVertex3f( 0.05f,  0.15f, 0.0f);
			glVertex3f( 0.00f,  0.15f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f( 0.00f,  0.0f, 0.0f);
			glVertex3f( 0.05f,  0.0f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f( 0.05f,  0.0f, 0.0f);
			glVertex3f( 0.00f,  0.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f( 0.00f,  -0.15f, 0.0f);
			glVertex3f( 0.05f,  -0.15f, 0.0f);
	glEnd();

//6
	glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f( 0.00f,  -0.15f, 0.0f);
			glVertex3f( 0.05f,  -0.15f, 0.0f);
			glVertex3f(-0.10f, -0.3f, 0.0f);
			glVertex3f(-0.10f, -0.25f, 0.0f);
	glEnd();


}
void drawLetterI2(void)
{
//----------- I -----------------------------------------------------

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.4f, 0.0f);
			glVertex3f(0.30f, 0.30f + moveLetter_I2, 0.0f);
			glVertex3f(0.15f, 0.30f + moveLetter_I2, 0.0f);
			glVertex3f(0.15f, 0.25f + moveLetter_I2, 0.0f);
			glVertex3f(0.30f, 0.25f + moveLetter_I2, 0.0f);
	glEnd();


	glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.30f, -0.30f + moveLetter_I2, 0.0f);
			glVertex3f(0.15f, -0.30f + moveLetter_I2, 0.0f);
			glVertex3f(0.15f, -0.25f + moveLetter_I2, 0.0f);
			glVertex3f(0.30f, -0.25f + moveLetter_I2, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.4f, 0.0f);
			glVertex3f(0.25f, 0.3f + moveLetter_I2, 0.0f);
			glVertex3f(0.20f, 0.3f + moveLetter_I2, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.20f, 0.0f + moveLetter_I2, 0.0f);
			glVertex3f(0.25f, 0.0f + moveLetter_I2, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.20f, 0.0f + moveLetter_I2, 0.0f);
			glVertex3f(0.25f, 0.0f + moveLetter_I2, 0.0f);
			
		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.25f, -0.3f + moveLetter_I2, 0.0f);
			glVertex3f(0.20f, -0.3f + moveLetter_I2, 0.0f);
	glEnd();

}
void drawLetterA(void)
{
//--------- A --------------------------------------------------------

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.4f, 0.0f);
			glVertex3f(0.50f + moveLetter_A, 0.3f, 0.0f);
			glVertex3f(0.55f + moveLetter_A, 0.3f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.50f + moveLetter_A, 0.0f, 0.0f);
			glVertex3f(0.45f + moveLetter_A, 0.0f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.45f + moveLetter_A, 0.0f, 0.0f);
			glVertex3f(0.50f + moveLetter_A, 0.0f, 0.0f);
			
		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.45f + moveLetter_A, -0.3f, 0.0f);
			glVertex3f(0.40f + moveLetter_A, -0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.4f, 0.0f);
			glVertex3f(0.50f + moveLetter_A, 0.3f, 0.0f);
			glVertex3f(0.55f + moveLetter_A, 0.3f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.60f + moveLetter_A, 0.0f, 0.0f);
			glVertex3f(0.55f + moveLetter_A, 0.0f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.55f + moveLetter_A, 0.0f, 0.0f);
			glVertex3f(0.60f + moveLetter_A, 0.0f, 0.0f);
			
		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.65f + moveLetter_A, -0.3f, 0.0f);
			glVertex3f(0.60f + moveLetter_A, -0.3f, 0.0f);
	glEnd();

}

void drawPlanes(void)
{

	movePlanesHor = movePlanesHor + 0.003;
	movePlanesVer = movePlanesVer + 0.003;

	if((movePlanesVer >= 0.8)&& (movePlanesHor < 1.00))
		movePlanesVer = 0.8;

	if(movePlanesHor > 0.90)
	{
		movePlanesVer = movePlanesVer + 0.0005;
		DrawFlag_flag = 1;
	}
	glColor3f(0.23f, 0.28f, 0.27f);

//---------------------------------------------
	glBegin(GL_TRIANGLES);
		glVertex3f(movePlanesHor - 0.1,  0.80 - movePlanesVer, 0);
		glVertex3f(movePlanesHor + 0.2,  0.85 - movePlanesVer, 0);
		glVertex3f(movePlanesHor + 0.2,  0.75 - movePlanesVer, 0);

		glVertex3f(movePlanesHor + 0.2,  0.85 - movePlanesVer, 0);
		glVertex3f(movePlanesHor + 0.2,  0.75 - movePlanesVer, 0);
		glVertex3f(movePlanesHor + 0.3,  0.80 - movePlanesVer, 0);

		glVertex3f(movePlanesHor -0.10,  0.80 - movePlanesVer, 0);
		glVertex3f(movePlanesHor -0.15,  0.85 - movePlanesVer, 0);
		glVertex3f(movePlanesHor -0.15,  0.75 - movePlanesVer, 0);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(movePlanesHor - 0.04,  1.00 - movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.08,  1.00 - movePlanesVer, 0);

		glVertex3f(movePlanesHor + 0.02,  0.80 - movePlanesVer, 0);
		glVertex3f(movePlanesHor + 0.08,  0.80 - movePlanesVer, 0);

		glVertex3f(movePlanesHor + 0.02,  0.80 - movePlanesVer, 0);
		glVertex3f(movePlanesHor + 0.08,  0.80 - movePlanesVer, 0);

		glVertex3f(movePlanesHor - 0.04,  0.60 - movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.08,  0.60 - movePlanesVer, 0);
	glEnd();
//-------------------------------------------------
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.4f, 0.0f);
		glVertex3f(movePlanesHor - 0.15,  0.85 - movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.15,  0.82 - movePlanesVer, 0);

		glVertex3f(movePlanesHor - 0.40,  0.82 - movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.40,  0.85 - movePlanesVer, 0);

	glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(movePlanesHor - 0.15,  0.82 - movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.15,  0.79 - movePlanesVer, 0);

		glVertex3f(movePlanesHor - 0.40,  0.79 - movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.40,  0.82 - movePlanesVer, 0);

	glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(movePlanesHor - 0.15,  0.79 - movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.15,  0.76 - movePlanesVer, 0);

		glVertex3f(movePlanesHor - 0.40,  0.76 - movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.40,  0.79 - movePlanesVer, 0);
	glEnd();

//-----------------------------------------------

//----------------------------------------------
	glColor3f(0.23f, 0.28f, 0.27f);
	glBegin(GL_TRIANGLES);
		glVertex3f(movePlanesHor - 0.1,  0.00, 0);
		glVertex3f(movePlanesHor + 0.2,  0.05, 0);
		glVertex3f(movePlanesHor + 0.2, -0.05, 0);

		glVertex3f(movePlanesHor + 0.2,  0.05, 0);
		glVertex3f(movePlanesHor + 0.2, -0.05, 0);
		glVertex3f(movePlanesHor + 0.3,  0.0, 0);

		glVertex3f(movePlanesHor -0.10,  0.00, 0);
		glVertex3f(movePlanesHor -0.15,  0.05, 0);
		glVertex3f(movePlanesHor -0.15, -0.05, 0);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(movePlanesHor  -0.04,  0.20, 0);
		glVertex3f(movePlanesHor  -0.08,  0.20, 0);

		glVertex3f(movePlanesHor + 0.02,  0.00, 0);
		glVertex3f(movePlanesHor + 0.08,  0.00, 0);

		glVertex3f(movePlanesHor + 0.02,  0.00, 0);
		glVertex3f(movePlanesHor + 0.08,  0.00, 0);

		glVertex3f(movePlanesHor - 0.04,  -0.20, 0);
		glVertex3f(movePlanesHor - 0.08,  -0.20, 0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.4f, 0.0f);
		glVertex3f(movePlanesHor - 0.15,  0.05, 0);
		glVertex3f(movePlanesHor - 0.15,  0.02, 0);

		glVertex3f(movePlanesHor - 0.40,  0.02, 0);
		glVertex3f(movePlanesHor - 0.40,  0.05, 0);

	glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(movePlanesHor - 0.15,  0.02, 0);
		glVertex3f(movePlanesHor - 0.15, -0.01, 0);

		glVertex3f(movePlanesHor - 0.40, -0.01, 0);
		glVertex3f(movePlanesHor - 0.40,  0.02, 0);

	glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(movePlanesHor - 0.15, -0.01, 0);
		glVertex3f(movePlanesHor - 0.15, -0.04, 0);

		glVertex3f(movePlanesHor - 0.40, -0.04, 0);
		glVertex3f(movePlanesHor - 0.40, -0.01, 0);
	glEnd();

//--------------------------------------------

//--------------------------------------------
	glColor3f(0.23f, 0.28f, 0.27f);
	glBegin(GL_TRIANGLES);
		glVertex3f(movePlanesHor - 0.1,  -0.80 + movePlanesVer, 0);
		glVertex3f(movePlanesHor + 0.2,  -0.85 + movePlanesVer, 0);
		glVertex3f(movePlanesHor + 0.2,  -0.75 + movePlanesVer, 0);

		glVertex3f(movePlanesHor + 0.2, -0.85 + movePlanesVer, 0);
		glVertex3f(movePlanesHor + 0.2, -0.75 + movePlanesVer, 0);
		glVertex3f(movePlanesHor + 0.3, -0.80 + movePlanesVer, 0);

		glVertex3f(movePlanesHor -0.10,  -0.80 + movePlanesVer, 0);
		glVertex3f(movePlanesHor -0.15,  -0.85 + movePlanesVer, 0);
		glVertex3f(movePlanesHor -0.15,  -0.75 + movePlanesVer, 0);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(movePlanesHor  -0.04,  -0.60 + movePlanesVer, 0);
		glVertex3f(movePlanesHor  -0.08,  -0.60 + movePlanesVer, 0);

		glVertex3f(movePlanesHor + 0.02,  -0.80 + movePlanesVer, 0);
		glVertex3f(movePlanesHor + 0.08,  -0.80 + movePlanesVer, 0);

		glVertex3f(movePlanesHor + 0.02,  -0.80 + movePlanesVer, 0);
		glVertex3f(movePlanesHor + 0.08,  -0.80 + movePlanesVer, 0);

		glVertex3f(movePlanesHor - 0.04,  -1.00 + movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.08,  -1.00 + movePlanesVer, 0);
	glEnd();

//-------------------------------------------------
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(movePlanesHor - 0.15,  -0.85 + movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.15,  -0.82 + movePlanesVer, 0);

		glVertex3f(movePlanesHor - 0.40,  -0.82 + movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.40,  -0.85 + movePlanesVer, 0);

	glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(movePlanesHor - 0.15,  -0.82 + movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.15,  -0.79 + movePlanesVer, 0);

		glVertex3f(movePlanesHor - 0.40,  -0.79 + movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.40,  -0.82 + movePlanesVer, 0);


	glColor3f(1.0f, 0.4f, 0.0f);
		glVertex3f(movePlanesHor - 0.15,  -0.79 + movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.15,  -0.76 + movePlanesVer, 0);

		glVertex3f(movePlanesHor - 0.40,  -0.76 + movePlanesVer, 0);
		glVertex3f(movePlanesHor - 0.40,  -0.79 + movePlanesVer, 0);
	glEnd();

//-----------------------------------------------



}

void drawFlagA(void)
{
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.4f, 0.0f);
			glVertex3f(0.51f, 0.045f, 0.0f);
			glVertex3f(0.50f, 0.015f, 0.0f);

			glVertex3f(0.55f, 0.015f, 0.0f);
			glVertex3f(0.54f, 0.045f, 0.0f);


		glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.50f , 0.015f, 0.0f);
			glVertex3f(0.49f , -0.015f, 0.0f);

			glVertex3f(0.56f, -0.015f, 0.0f);
			glVertex3f(0.55f, 0.015f, 0.0f);


		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.49f , -0.015f, 0.0f);
			glVertex3f(0.48f , -0.045f, 0.0f);

			glVertex3f(0.57f, -0.045f, 0.0f);
			glVertex3f(0.56f, -0.015f, 0.0f);

	glEnd();

}

void update(void)
{
	moveLetter_I = moveLetter_I - 0.02f;
	if(moveLetter_I <= 0.0f)
	{
		moveLetter_I = 0.0f;
		I_flag = 1;
	}

	if(N_flag == 1)
	{
		moveLetter_N = moveLetter_N - 0.02f;
		{
			if(moveLetter_N <= 0.0f)
			{
				moveLetter_N = 0.0f;
				I2_flag = 1;
			}
		}
	}

	if(D_flag == 1)
	{
		moveLetter_D = moveLetter_D + 0.02f;
		if(moveLetter_D >= 1.0f)
		{
			moveLetter_D = 1.0f;
			Planes_flag = 1;
		}
	}

if(I2_flag == 1)
	{
		moveLetter_I2 = moveLetter_I2 - 0.02f;
		{
			if(moveLetter_I2 <= 0.0f)
			{
				moveLetter_I2 = 0.0f;
				D_flag = 1;
			}
		}
	}

	if(I_flag == 1)
	{
		moveLetter_A = moveLetter_A - 0.02f;
		{
			if(moveLetter_A <= 0.0f)
			{
				moveLetter_A = 0.0f;
				N_flag = 1;
			}
		}
	}
//	DrawFlag_flag
	if(Planes_flag == 1)
	{
		showFlag = showFlag + 0.02f;
		if(showFlag >= 1.0f)
		{
			showFlag = 1.0f;
		}
	}

}

void uninitialize(void)
{

	if(gbFullscreen == true)
	{
		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPos(ghwnd,
					HWND_TOP,
					0,
					0,
					0,
					0,
					SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}

	//deselecting rendering context
	if(wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	//releasing rendering context handle
	if(ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}
	
	//releasing device context handle
	if(ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	//closing log file
	if(gpFile)
	{
		fprintf(gpFile, "DEBUG:Log File Closed\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
