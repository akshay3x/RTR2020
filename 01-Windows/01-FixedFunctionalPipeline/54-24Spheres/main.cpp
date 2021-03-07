#include <Windows.h>
#include <stdio.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#include "resource.h"
#include "materials.h"

//library inclusion/linking
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

//macro definitions
#define WIN_WIDTH 800
#define WIN_HIGHT 600

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

GLfloat angle = 0.0f;

bool gbLight = false;
GLfloat lightAmbientZero[]  = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat lightDiffuseZero[]  = {1.0f, 1.0f, 1.0f, 1.0f};//white
GLfloat lightPositionZero[] = {0.0f, 3.0f, 3.0f, 0.0f};//Directional light

GLfloat glLight_model_Ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat glLight_model_local_viewer[] = {0.0f};

GLfloat AngleForXRotation = 0.0f;
GLfloat AngleForYRotation = 0.0f;
GLfloat AngleForZRotation = 0.0f;

GLUquadric *quadric[24];

GLint keyPressed = 0;

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

				case 'L':
				case 'l':
					if(gbLight == false)
					{
						glEnable(GL_LIGHTING);
						gbLight = true; 
					}
					else
					{
						glDisable(GL_LIGHTING);
						gbLight = false;
					}
					break;

				case 'X':
				case 'x':
				keyPressed = 1;
				AngleForXRotation = 1;
				break;

				case 'Y':
				case 'y':
				keyPressed = 2;
				AngleForYRotation = 1;
				break;

				case 'Z':
				case 'z':
				keyPressed = 3;
				AngleForZRotation = 1;
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
	bool LoadGLTexture(GLuint *texture, TCHAR resourceID[]);

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

	//Set background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//Set background depth to farthest
	glClearDepth(1.0f);
	//Enable depth testing for z-culling
	glEnable(GL_DEPTH_TEST);
	//Set the type of depth-test
	glDepthFunc(GL_LEQUAL);
	//Enable smooth shading
	glShadeModel(GL_SMOOTH);
	//Nice perspective corrections
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glLight_model_Ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, glLight_model_local_viewer);

	glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbientZero);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuseZero);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositionZero);
	glEnable(GL_LIGHT0);

	for(int i = 0; i < 24; i++)
	{
		quadric[i] = gluNewQuadric();
	}

	glEnable(GL_LIGHT0);

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f); //Dark Grey

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

	if(width <= hight)
	{
		glOrtho( 0.0f,
				 15.5f,
				 0.0f ,
				 15.5f * ((GLfloat)hight/(GLfloat)width),
				-10.0f,
				 10.0f);
	}
	else
	{
		glOrtho( 0.0f, 
				 15.5f * ((GLfloat)width/(GLfloat)hight),
				 0.0f,
				 15.5f,
				-10.0f,
				 10.0f);
	}

}

void display(void)
{
	//function declarations
	void draw24Sphere(void);

	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(keyPressed == 1)
	{
		glRotatef(AngleForXRotation, 1.0f, 0.0f , 0.0f);
		lightPositionZero[1] = AngleForXRotation;
	}

	else if(keyPressed == 2)
	{
		glRotatef(AngleForYRotation, 0.0f, 1.0f, 0.0f);
		lightPositionZero[2] = AngleForYRotation;
	}

	else if(keyPressed == 3)
	{
		glRotatef(AngleForZRotation, 0.0f, 0.0f, 1.0f);
		lightPositionZero[0] = AngleForZRotation;
	}

	glLightfv(GL_LIGHT0, GL_POSITION, lightPositionZero);

	draw24Sphere();

	SwapBuffers(ghdc);
}

void draw24Sphere(void)
{
	GLfloat materialAmbient[4];
	GLfloat materialDiffuse[4];
	GLfloat materialSpecular[4];
	GLfloat materialShininess;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//-----------------------------------------------------------
	materialAmbient[0] = materialAmbient01[0];
	materialAmbient[1] = materialAmbient01[1];
	materialAmbient[2] = materialAmbient01[2];
	materialAmbient[3] = materialAmbient01[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse01[0];
	materialDiffuse[1] = materialDiffuse01[1];
	materialDiffuse[2] = materialDiffuse01[2];
	materialDiffuse[3] = materialDiffuse01[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular01[0];
	materialSpecular[1] = materialSpecular01[1];
	materialSpecular[2] = materialSpecular01[2];
	materialSpecular[3] = materialSpecular01[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess01;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(3.5f, 12.0f, 0.0f);

	quadric[0] = gluNewQuadric(); 
	gluSphere(quadric[0], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient02[0];
	materialAmbient[1] = materialAmbient02[1];
	materialAmbient[2] = materialAmbient02[2];
	materialAmbient[3] = materialAmbient02[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse02[0];
	materialDiffuse[1] = materialDiffuse02[1];
	materialDiffuse[2] = materialDiffuse02[2];
	materialDiffuse[3] = materialDiffuse02[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular02[0];
	materialSpecular[1] = materialSpecular02[1];
	materialSpecular[2] = materialSpecular02[2];
	materialSpecular[3] = materialSpecular02[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess02;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[1] = gluNewQuadric(); 
	gluSphere(quadric[1], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient03[0];
	materialAmbient[1] = materialAmbient03[1];
	materialAmbient[2] = materialAmbient03[2];
	materialAmbient[3] = materialAmbient03[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse03[0];
	materialDiffuse[1] = materialDiffuse03[1];
	materialDiffuse[2] = materialDiffuse03[2];
	materialDiffuse[3] = materialDiffuse03[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular03[0];
	materialSpecular[1] = materialSpecular03[1];
	materialSpecular[2] = materialSpecular03[2];
	materialSpecular[3] = materialSpecular03[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess03;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[2] = gluNewQuadric(); 
	gluSphere(quadric[2], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient04[0];
	materialAmbient[1] = materialAmbient04[1];
	materialAmbient[2] = materialAmbient04[2];
	materialAmbient[3] = materialAmbient04[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse04[0];
	materialDiffuse[1] = materialDiffuse04[1];
	materialDiffuse[2] = materialDiffuse04[2];
	materialDiffuse[3] = materialDiffuse04[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular04[0];
	materialSpecular[1] = materialSpecular04[1];
	materialSpecular[2] = materialSpecular04[2];
	materialSpecular[3] = materialSpecular04[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess04;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[3] = gluNewQuadric(); 
	gluSphere(quadric[3], 1.0, 30, 30);

//-------------------------------------------------------------------------
	materialAmbient[0] = materialAmbient05[0];
	materialAmbient[1] = materialAmbient05[1];
	materialAmbient[2] = materialAmbient05[2];
	materialAmbient[3] = materialAmbient05[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse05[0];
	materialDiffuse[1] = materialDiffuse05[1];
	materialDiffuse[2] = materialDiffuse05[2];
	materialDiffuse[3] = materialDiffuse05[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular05[0];
	materialSpecular[1] = materialSpecular05[1];
	materialSpecular[2] = materialSpecular05[2];
	materialSpecular[3] = materialSpecular05[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess05;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(6.5f, 12.0f, 0.0f);

	quadric[4] = gluNewQuadric(); 
	gluSphere(quadric[4], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient06[0];
	materialAmbient[1] = materialAmbient06[1];
	materialAmbient[2] = materialAmbient06[2];
	materialAmbient[3] = materialAmbient06[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse06[0];
	materialDiffuse[1] = materialDiffuse06[1];
	materialDiffuse[2] = materialDiffuse06[2];
	materialDiffuse[3] = materialDiffuse06[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular06[0];
	materialSpecular[1] = materialSpecular06[1];
	materialSpecular[2] = materialSpecular06[2];
	materialSpecular[3] = materialSpecular06[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess06;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[5] = gluNewQuadric(); 
	gluSphere(quadric[5], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient07[0];
	materialAmbient[1] = materialAmbient07[1];
	materialAmbient[2] = materialAmbient07[2];
	materialAmbient[3] = materialAmbient07[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse07[0];
	materialDiffuse[1] = materialDiffuse07[1];
	materialDiffuse[2] = materialDiffuse07[2];
	materialDiffuse[3] = materialDiffuse07[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular07[0];
	materialSpecular[1] = materialSpecular07[1];
	materialSpecular[2] = materialSpecular07[2];
	materialSpecular[3] = materialSpecular07[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess07;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[6] = gluNewQuadric(); 
	gluSphere(quadric[6], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient08[0];
	materialAmbient[1] = materialAmbient08[1];
	materialAmbient[2] = materialAmbient08[2];
	materialAmbient[3] = materialAmbient08[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse08[0];
	materialDiffuse[1] = materialDiffuse08[1];
	materialDiffuse[2] = materialDiffuse08[2];
	materialDiffuse[3] = materialDiffuse08[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular08[0];
	materialSpecular[1] = materialSpecular08[1];
	materialSpecular[2] = materialSpecular08[2];
	materialSpecular[3] = materialSpecular08[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess08;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[7] = gluNewQuadric(); 
	gluSphere(quadric[7], 1.0, 30, 30);

//-------------------------------------------------------------------------
	materialAmbient[0] = materialAmbient09[0];
	materialAmbient[1] = materialAmbient09[1];
	materialAmbient[2] = materialAmbient09[2];
	materialAmbient[3] = materialAmbient09[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse09[0];
	materialDiffuse[1] = materialDiffuse09[1];
	materialDiffuse[2] = materialDiffuse09[2];
	materialDiffuse[3] = materialDiffuse09[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular09[0];
	materialSpecular[1] = materialSpecular09[1];
	materialSpecular[2] = materialSpecular09[2];
	materialSpecular[3] = materialSpecular09[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess09;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glTranslatef(0.0f, -2.5f, 0.0f);
	glTranslatef(9.5f, 12.0f, 0.0f);

	quadric[8] = gluNewQuadric(); 
	gluSphere(quadric[8], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient10[0];
	materialAmbient[1] = materialAmbient10[1];
	materialAmbient[2] = materialAmbient10[2];
	materialAmbient[3] = materialAmbient10[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse10[0];
	materialDiffuse[1] = materialDiffuse10[1];
	materialDiffuse[2] = materialDiffuse10[2];
	materialDiffuse[3] = materialDiffuse10[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular10[0];
	materialSpecular[1] = materialSpecular10[1];
	materialSpecular[2] = materialSpecular10[2];
	materialSpecular[3] = materialSpecular10[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess10;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[9] = gluNewQuadric(); 
	gluSphere(quadric[9], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient11[0];
	materialAmbient[1] = materialAmbient11[1];
	materialAmbient[2] = materialAmbient11[2];
	materialAmbient[3] = materialAmbient11[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse11[0];
	materialDiffuse[1] = materialDiffuse11[1];
	materialDiffuse[2] = materialDiffuse11[2];
	materialDiffuse[3] = materialDiffuse11[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular11[0];
	materialSpecular[1] = materialSpecular11[1];
	materialSpecular[2] = materialSpecular11[2];
	materialSpecular[3] = materialSpecular11[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess11;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[10] = gluNewQuadric(); 
	gluSphere(quadric[10], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient12[0];
	materialAmbient[1] = materialAmbient12[1];
	materialAmbient[2] = materialAmbient12[2];
	materialAmbient[3] = materialAmbient12[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse12[0];
	materialDiffuse[1] = materialDiffuse12[1];
	materialDiffuse[2] = materialDiffuse12[2];
	materialDiffuse[3] = materialDiffuse12[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular12[0];
	materialSpecular[1] = materialSpecular12[1];
	materialSpecular[2] = materialSpecular12[2];
	materialSpecular[3] = materialSpecular12[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess12;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[11] = gluNewQuadric(); 
	gluSphere(quadric[11], 1.0, 30, 30);
//-------------------------------------------------------------------------
	materialAmbient[0] = materialAmbient13[0];
	materialAmbient[1] = materialAmbient13[1];
	materialAmbient[2] = materialAmbient13[2];
	materialAmbient[3] = materialAmbient13[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse13[0];
	materialDiffuse[1] = materialDiffuse13[1];
	materialDiffuse[2] = materialDiffuse13[2];
	materialDiffuse[3] = materialDiffuse13[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular13[0];
	materialSpecular[1] = materialSpecular13[1];
	materialSpecular[2] = materialSpecular13[2];
	materialSpecular[3] = materialSpecular13[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess13;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(12.5f, 12.0f, 0.0f);

	quadric[12] = gluNewQuadric(); 
	gluSphere(quadric[12], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient14[0];
	materialAmbient[1] = materialAmbient14[1];
	materialAmbient[2] = materialAmbient14[2];
	materialAmbient[3] = materialAmbient14[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse14[0];
	materialDiffuse[1] = materialDiffuse14[1];
	materialDiffuse[2] = materialDiffuse14[2];
	materialDiffuse[3] = materialDiffuse14[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular14[0];
	materialSpecular[1] = materialSpecular14[1];
	materialSpecular[2] = materialSpecular14[2];
	materialSpecular[3] = materialSpecular14[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess14;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[13] = gluNewQuadric(); 
	gluSphere(quadric[13], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient15[0];
	materialAmbient[1] = materialAmbient15[1];
	materialAmbient[2] = materialAmbient15[2];
	materialAmbient[3] = materialAmbient15[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse15[0];
	materialDiffuse[1] = materialDiffuse15[1];
	materialDiffuse[2] = materialDiffuse15[2];
	materialDiffuse[3] = materialDiffuse15[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular15[0];
	materialSpecular[1] = materialSpecular15[1];
	materialSpecular[2] = materialSpecular15[2];
	materialSpecular[3] = materialSpecular15[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess15;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[14] = gluNewQuadric(); 
	gluSphere(quadric[14], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient16[0];
	materialAmbient[1] = materialAmbient16[1];
	materialAmbient[2] = materialAmbient16[2];
	materialAmbient[3] = materialAmbient16[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse16[0];
	materialDiffuse[1] = materialDiffuse16[1];
	materialDiffuse[2] = materialDiffuse16[2];
	materialDiffuse[3] = materialDiffuse16[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular16[0];
	materialSpecular[1] = materialSpecular16[1];
	materialSpecular[2] = materialSpecular16[2];
	materialSpecular[3] = materialSpecular16[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess16;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[15] = gluNewQuadric(); 
	gluSphere(quadric[15], 1.0, 30, 30);
//-------------------------------------------------------------------------
	materialAmbient[0] = materialAmbient17[0];
	materialAmbient[1] = materialAmbient17[1];
	materialAmbient[2] = materialAmbient17[2];
	materialAmbient[3] = materialAmbient17[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse17[0];
	materialDiffuse[1] = materialDiffuse17[1];
	materialDiffuse[2] = materialDiffuse17[2];
	materialDiffuse[3] = materialDiffuse17[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular17[0];
	materialSpecular[1] = materialSpecular17[1];
	materialSpecular[2] = materialSpecular17[2];
	materialSpecular[3] = materialSpecular17[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess17;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(15.5f, 12.0f, 0.0f);

	quadric[16] = gluNewQuadric(); 
	gluSphere(quadric[16], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient18[0];
	materialAmbient[1] = materialAmbient18[1];
	materialAmbient[2] = materialAmbient18[2];
	materialAmbient[3] = materialAmbient18[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse18[0];
	materialDiffuse[1] = materialDiffuse18[1];
	materialDiffuse[2] = materialDiffuse18[2];
	materialDiffuse[3] = materialDiffuse18[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular18[0];
	materialSpecular[1] = materialSpecular18[1];
	materialSpecular[2] = materialSpecular18[2];
	materialSpecular[3] = materialSpecular18[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess18;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[17] = gluNewQuadric(); 
	gluSphere(quadric[17], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient19[0];
	materialAmbient[1] = materialAmbient19[1];
	materialAmbient[2] = materialAmbient19[2];
	materialAmbient[3] = materialAmbient19[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse19[0];
	materialDiffuse[1] = materialDiffuse19[1];
	materialDiffuse[2] = materialDiffuse19[2];
	materialDiffuse[3] = materialDiffuse19[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular19[0];
	materialSpecular[1] = materialSpecular19[1];
	materialSpecular[2] = materialSpecular19[2];
	materialSpecular[3] = materialSpecular19[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess19;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[18] = gluNewQuadric(); 
	gluSphere(quadric[18], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient20[0];
	materialAmbient[1] = materialAmbient20[1];
	materialAmbient[2] = materialAmbient20[2];
	materialAmbient[3] = materialAmbient20[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse20[0];
	materialDiffuse[1] = materialDiffuse20[1];
	materialDiffuse[2] = materialDiffuse20[2];
	materialDiffuse[3] = materialDiffuse20[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular20[0];
	materialSpecular[1] = materialSpecular20[1];
	materialSpecular[2] = materialSpecular20[2];
	materialSpecular[3] = materialSpecular20[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess20;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[19] = gluNewQuadric(); 
	gluSphere(quadric[1], 1.0, 30, 30);
//-------------------------------------------------------------------------
	materialAmbient[0] = materialAmbient21[0];
	materialAmbient[1] = materialAmbient21[1];
	materialAmbient[2] = materialAmbient21[2];
	materialAmbient[3] = materialAmbient21[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse21[0];
	materialDiffuse[1] = materialDiffuse21[1];
	materialDiffuse[2] = materialDiffuse21[2];
	materialDiffuse[3] = materialDiffuse21[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular21[0];
	materialSpecular[1] = materialSpecular21[1];
	materialSpecular[2] = materialSpecular21[2];
	materialSpecular[3] = materialSpecular21[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess21;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(18.5f, 12.0f, 0.0f);

	quadric[20] = gluNewQuadric(); 
	gluSphere(quadric[20], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient22[0];
	materialAmbient[1] = materialAmbient22[1];
	materialAmbient[2] = materialAmbient22[2];
	materialAmbient[3] = materialAmbient22[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse22[0];
	materialDiffuse[1] = materialDiffuse22[1];
	materialDiffuse[2] = materialDiffuse22[2];
	materialDiffuse[3] = materialDiffuse22[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular22[0];
	materialSpecular[1] = materialSpecular22[1];
	materialSpecular[2] = materialSpecular22[2];
	materialSpecular[3] = materialSpecular22[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess22;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[21] = gluNewQuadric(); 
	gluSphere(quadric[21], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient23[0];
	materialAmbient[1] = materialAmbient23[1];
	materialAmbient[2] = materialAmbient23[2];
	materialAmbient[3] = materialAmbient23[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse23[0];
	materialDiffuse[1] = materialDiffuse23[1];
	materialDiffuse[2] = materialDiffuse23[2];
	materialDiffuse[3] = materialDiffuse23[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular23[0];
	materialSpecular[1] = materialSpecular23[1];
	materialSpecular[2] = materialSpecular23[2];
	materialSpecular[3] = materialSpecular23[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess23;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[22] = gluNewQuadric(); 
	gluSphere(quadric[22], 1.0, 30, 30);

	materialAmbient[0] = materialAmbient24[0];
	materialAmbient[1] = materialAmbient24[1];
	materialAmbient[2] = materialAmbient24[2];
	materialAmbient[3] = materialAmbient24[3];
	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);

	materialDiffuse[0] = materialDiffuse24[0];
	materialDiffuse[1] = materialDiffuse24[1];
	materialDiffuse[2] = materialDiffuse24[2];
	materialDiffuse[3] = materialDiffuse24[3];
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);

	materialSpecular[0] = materialSpecular24[0];
	materialSpecular[1] = materialSpecular24[1];
	materialSpecular[2] = materialSpecular24[2];
	materialSpecular[3] = materialSpecular24[3];
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);

	materialShininess = materialShininess24;
	glMaterialf(GL_FRONT,  GL_SHININESS, materialShininess);

	glTranslatef(0.0f, -2.5f, 0.0f);

	quadric[23] = gluNewQuadric(); 
	gluSphere(quadric[23], 1.0, 30, 30);

}

void update(void)
{
	//code
	if(keyPressed == 1)
		AngleForXRotation = AngleForXRotation + 5.0f;

	else if(keyPressed == 2)
		AngleForYRotation = AngleForYRotation + 5.0f;

	else if(keyPressed == 3)
	AngleForZRotation = AngleForZRotation + 5.0f;
}

void uninitialize(void)
{
	//code
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

	if(quadric)
	{
		for(int i = 0; i < 24; i++)
		{
			gluDeleteQuadric(quadric[i]);
			quadric[i] = NULL;
		}
	}

	//closing log file
	if(gpFile)
	{
		fprintf(gpFile, "DEBUG:Log File Closed\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
