#include <Windows.h>
#include <stdio.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#include "resource.h"
#include "OGL.h"

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

GLuint MarbleTexture;
bool gbLight = false;
bool gbTexture = false;
bool gbAnimate = false;

GLfloat lightAmbientZero[]  = {   0.0f,   0.0f,    0.0f, 1.0f};
GLfloat lightDiffuseZero[]  = {   1.0f,   1.0f,    1.0f, 1.0f};
GLfloat lightSpecularZero[] = {   1.0f,   1.0f,    1.0f, 1.0f};
GLfloat lightPositionZero[] = { 100.0f, 100.0f, 1000.0f, 1.0f};//light position


GLfloat materialAmbient[]  = { 0.0f, 0.0f, 0.0f, 1.0f};
GLfloat materialDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat MaterialShininess  = 50.0f;



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

				case 'A':
				case 'a':
					if(gbAnimate == false)
						gbAnimate = true; 
					else
						gbAnimate = false;
					break;

				case 'T':
				case 't':
					if(gbTexture == false)
					{
						glEnable(GL_TEXTURE_2D);
						gbTexture = true; 
					}
					else
					{
						glDisable(GL_TEXTURE_2D);
						gbTexture = false;
					}
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


	LoadGLTexture(&MarbleTexture, MAKEINTRESOURCE(MARBLE_BITMAP));

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbientZero);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuseZero);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecularZero);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositionZero);
	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT,  GL_SHININESS, MaterialShininess);

	//WarmUp resize() Call
	resize(WIN_WIDTH, WIN_HIGHT);
}

bool LoadGLTexture(GLuint *texture, TCHAR resourceID[])
{
	//variable declarations
	bool bResult = false;
	HBITMAP hBitmap = NULL;
	BITMAP bmp;

	//code
/*	HANDLE LoadImageW
	( 
	HINSTANCE	hInst,
	LPCWSTR		name,
	UINT		type,
	int			cx,
	int			cy,
	UINT		fuLoad 
	);
*/
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), resourceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if(hBitmap) //if(hBitmap != NULL)
	{
		bResult = true;
		GetObject(hBitmap, sizeof(BITMAP), &bmp);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
	}
	
	return bResult;
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

	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef( 0.0f, 0.0f , -1.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, MarbleTexture);

	glBegin(GL_TRIANGLES);
		for(int i = 0; i < ((sizeof(face_indicies)/sizeof(face_indicies[0]))); i++ )
		{
			for(int j = 0; j < 3; j++)
			{
				int vi = face_indicies[i][j];
				int ni = face_indicies[i][j+3];
				int ti = face_indicies[i][j+6];

				glNormal3f(normals[ni][0], normals[ni][1], normals[ni][2]);
				glTexCoord2f(textures[ti][0],textures[ti][1]);
				glVertex3f( vertices[vi][0], vertices[vi][1], vertices[vi][2]);
			}
		}
	glEnd();

	SwapBuffers(ghdc);
}


void update(void)
{
	//code
	if(gbAnimate == true)
	{
		angle = angle + 1.0f;
		if(angle >= 360.0f)
			angle = 0.0f;
	}
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

	glDeleteTextures(1, &MarbleTexture);

	//closing log file
	if(gpFile)
	{
		fprintf(gpFile, "DEBUG:Log File Closed\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
