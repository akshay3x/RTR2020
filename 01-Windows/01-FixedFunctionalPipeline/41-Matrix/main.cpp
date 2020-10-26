#include <Windows.h>
#include <stdio.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <math.h>

#include "resource.h"

//library inclusion/linking
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

//macro definitions
#define WIN_WIDTH 800
#define WIN_HIGHT 600

#define GL_PI 3.14159265359
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

GLfloat angleCube = 0.0f;
GLfloat angleCubeRad = 0.0f;

GLfloat IdentityMatrix[16];
GLfloat TranslatationMatrix[16];
GLfloat ScaleMatrix[16];
GLfloat RoatationMatrixX[16];
GLfloat RoatationMatrixY[16];
GLfloat RoatationMatrixZ[16];

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

	pfd.cDepthBits = 32;

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
		DestroyWindow(ghwnd);//added new
	}

	if(wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFile, "DEBUG:wgl_MakeContext() Failed\n");
		DestroyWindow(ghwnd);
	}
	//IdentityMatrix
	IdentityMatrix[0] = 1;
	IdentityMatrix[1] = 0; 
	IdentityMatrix[2] = 0; 
	IdentityMatrix[3] = 0;  
	
	IdentityMatrix[4] = 0; 
	IdentityMatrix[5] = 1; 
	IdentityMatrix[6] = 0; 
	IdentityMatrix[7] = 0;

	IdentityMatrix[8] = 0; 
	IdentityMatrix[9] = 0; 
	IdentityMatrix[10] = 1; 
	IdentityMatrix[11] = 0;

	IdentityMatrix[12] = 0; 
	IdentityMatrix[13] = 0;
	IdentityMatrix[14] = 0; 
	IdentityMatrix[15] = 1;

	//translation Matrix
	TranslatationMatrix[0] = 1;
	TranslatationMatrix[1] = 0;
	TranslatationMatrix[2] = 0;
	TranslatationMatrix[3] = 0;

	TranslatationMatrix[4] = 0;
	TranslatationMatrix[5] = 1;
	TranslatationMatrix[6] = 0;
	TranslatationMatrix[7] = 0;

	TranslatationMatrix[8] = 0;
	TranslatationMatrix[9] = 0;
	TranslatationMatrix[10] = 1;
	TranslatationMatrix[11] = 0;

	TranslatationMatrix[12] = 0;
	TranslatationMatrix[13] = 0;
	TranslatationMatrix[14] = -4;
	TranslatationMatrix[15] = 1;

	//scale matrix
	ScaleMatrix[0] = 0.40;
	ScaleMatrix[1] = 0.0;
	ScaleMatrix[2] = 0.0;
	ScaleMatrix[3] = 0.0;

	ScaleMatrix[4] = 0.0;
	ScaleMatrix[5] = 0.40;
	ScaleMatrix[6] = 0.0;
	ScaleMatrix[7] = 0.0;

	ScaleMatrix[8] = 0.0;
	ScaleMatrix[9] = 0.0;
	ScaleMatrix[10] = 0.40;
	ScaleMatrix[11] = 0.0;

	ScaleMatrix[12] = 0.0;
	ScaleMatrix[13] = 0.0;
	ScaleMatrix[14] = 0.0;
	ScaleMatrix[15] = 1.0;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// Set background color to black and opaque
	glClearDepth(1.0f);						// Set background depth to farthest
	glEnable(GL_DEPTH_TEST);				// Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);					// Set the type of depth-test
	glShadeModel(GL_SMOOTH);				// Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Nice perspective corrections


	//WarmUp resize() Call
	resize(WIN_WIDTH, WIN_HIGHT);
}

void resize(int width, int hight)
{
	//code
	if(hight == 0)
		hight = 1;

	glViewport(0, 0, GLsizei(width), GLsizei(hight));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,
					(GLfloat)width/(GLfloat)hight,
					0.1f,
					100.0f);

}

void display(void)
{
	//function declarations
	void drawCube(void);
	void rotateCubeX(void);
	void rotateCubeY(void);
	void rotateCubeZ(void);

	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(IdentityMatrix);
	glMultMatrixf(TranslatationMatrix);
	glMultMatrixf(ScaleMatrix);

	angleCubeRad = (GLfloat)(angleCube * (GL_PI/180));

	rotateCubeX();
	glMultMatrixf(RoatationMatrixX);
	rotateCubeY();
	glMultMatrixf(RoatationMatrixY);
	rotateCubeZ();
	glMultMatrixf(RoatationMatrixZ);

	drawCube();

	SwapBuffers(ghdc);
}

void drawCube(void)
{
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f( 1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f,  1.0f);
		glVertex3f( 1.0f, 1.0f,  1.0f);

		// Bottom face (y = -1.0f)
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);

		// Front face  (z = 1.0f)
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f( 1.0f,  1.0f, 1.0f);
		glVertex3f(-1.0f,  1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f( 1.0f, -1.0f, 1.0f);

		// Back face (z = -1.0f)
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);

		// Left face (x = -1.0f)
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		
		// Right face (x = 1.0f)
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f,  1.0f, -1.0f);
		glVertex3f(1.0f,  1.0f,  1.0f);
		glVertex3f(1.0f, -1.0f,  1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

}

void rotateCubeX(void)
{
	//code
	RoatationMatrixX[0] = 1;
	RoatationMatrixX[1] = 0; 
	RoatationMatrixX[2] = 0; 
	RoatationMatrixX[3] = 0;  
	
	RoatationMatrixX[4] = 0; 
	RoatationMatrixX[5] = cos(angleCubeRad); 
	RoatationMatrixX[6] = sin(angleCubeRad); 
	RoatationMatrixX[7] = 0;

	RoatationMatrixX[8] = 0; 
	RoatationMatrixX[9] = -sin(angleCubeRad); 
	RoatationMatrixX[10] = cos(angleCubeRad); 
	RoatationMatrixX[11] = 0;

	RoatationMatrixX[12] = 0; 
	RoatationMatrixX[13] = 0;
	RoatationMatrixX[14] = 0; 
	RoatationMatrixX[15] = 1;
}
void rotateCubeY(void)
{

	//code
	RoatationMatrixY[0] = cos(angleCubeRad);;
	RoatationMatrixY[1] = 0; 
	RoatationMatrixY[2] = -sin(angleCubeRad); 
	RoatationMatrixY[3] = 0;  
	
	RoatationMatrixY[4] = 0; 
	RoatationMatrixY[5] = 1; 
	RoatationMatrixY[6] = 0; 
	RoatationMatrixY[7] = 0;

	RoatationMatrixY[8] = sin(angleCubeRad); 
	RoatationMatrixY[9] = 0; 
	RoatationMatrixY[10] = cos(angleCubeRad); 
	RoatationMatrixY[11] = 0;

	RoatationMatrixY[12] = 0; 
	RoatationMatrixY[13] = 0;
	RoatationMatrixY[14] = 0; 
	RoatationMatrixY[15] = 1;


}
void rotateCubeZ(void)
{
	//code
	RoatationMatrixZ[0] = cos(angleCubeRad);
	RoatationMatrixZ[1] = sin(angleCubeRad); 
	RoatationMatrixZ[2] = 0; 
	RoatationMatrixZ[3] = 0;  
	
	RoatationMatrixZ[4] = -sin(angleCubeRad); 
	RoatationMatrixZ[5] = cos(angleCubeRad); 
	RoatationMatrixZ[6] = 0; 
	RoatationMatrixZ[7] = 0;
    
	RoatationMatrixZ[8] = 0; 
	RoatationMatrixZ[9] = 0; 
	RoatationMatrixZ[10] = 1; 
	RoatationMatrixZ[11] = 0;
    
	RoatationMatrixZ[12] = 0; 
	RoatationMatrixZ[13] = 0;
	RoatationMatrixZ[14] = 0; 
	RoatationMatrixZ[15] = 1;

}


void update(void)
{
	angleCube = angleCube + 5.0f;

	if(angleCube >= 360.0f)
		angleCube = 0.0f;

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
