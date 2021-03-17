#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <math.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>

#include <GL/gl.h>	//for openGL apis
#include <GL/glu.h>
#include <GL/glx.h> 	//for glx apis // /usr/include->gl folder

#define GL_PI       3.1415926535

//namespace
using namespace std;

//global variable declarations
Display *gpDisplay = NULL;
XVisualInfo *gpXVisualInfo = NULL;
Colormap gColormap;
Window gWindow;

GLXContext gGLXContext;

bool gbFullscreen = false;
int giWindowWidth = 800;
int giWindowHight = 600;

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

//entry point function
int main(void)
{
	//function declarations
	void CreateWindow(void);
	void ToggleFullscreen(void);
	void uninitialize(void);

	void initialize(void);
	void resize(int, int);
	void display(void);	//render, draw
	void update (void);

	//variable declarations
	int winWidth = giWindowWidth;
	int winHight = giWindowHight;

	bool bDone = false;

	//code
	gpFile = fopen("./DEBUG_LOG.TXT", "w");
	if( gpFile == NULL)
	{
		printf("ERROR: Debug File Open Failed\n:");
		exit(0);
	}
	else
	{
		fprintf(gpFile, "DEBUG:Log File Created Successfully\n");
	}

	CreateWindow();
	fprintf(gpFile, "DEBUG:CreateWindow() Successful\n");

	initialize();
	fprintf(gpFile, "DEBUG:initialize() Successful\n");

	//MessageLoop
	XEvent event;
	KeySym keysym;

	fprintf(gpFile, "DEBUG:Message/Game Loop Started\n");

	while(bDone == false)
	{
		while(XPending(gpDisplay))
		{
			XNextEvent(gpDisplay, &event);

			switch(event.type)
			{
				case MapNotify:
				break;

				case KeyPress:
				keysym = XkbKeycodeToKeysym(gpDisplay, event.xkey.keycode, 0, 0);
				switch(keysym)
				{
					case XK_Escape:
					bDone = true;
					break;

					case XK_F:
					case XK_f:
					if(gbFullscreen == false)
					{
						ToggleFullscreen();
						gbFullscreen = true;
					}
					else
					{
						ToggleFullscreen();
						gbFullscreen = false;
					}
					break;

					default:
					break;
				}
				break;

				case ButtonPress:
				switch(event.xbutton.button)
				{
					case 1:
					break;

					case 2:
					break;

					case 3:
					break;

					default:
					break;
					}
				break;

				case MotionNotify:
				break;

				case ConfigureNotify:
				winWidth = event.xconfigure.width;
				winHight = event.xconfigure.height;
				resize(winWidth, winHight);
				break;

				case Expose:
				break;

				case DestroyNotify:
				break;

				case 33:
				bDone = true;
				break;

				default:
				break;
			}
		}
		update();
		display();
	}
	uninitialize();
	return(0);
}

void CreateWindow(void)
{
	//function declarations
	void uninitialize(void);

	//variable declarations
	XSetWindowAttributes winAttribs;
	int defaultScreen;
	int styleMask;

	static int frameBufferAttributes[] = { GLX_RGBA,
						GLX_RED_SIZE,   8,
						GLX_GREEN_SIZE, 8,
						GLX_BLUE_SIZE,  8,
						GLX_ALPHA_SIZE, 8,
						GLX_DOUBLEBUFFER, True,
						GLX_DEPTH_SIZE, 24,
						None		// can write as digit 0 also
						};

	//code
	gpDisplay = XOpenDisplay(NULL);
	if(gpDisplay == NULL)
	{
		fprintf(gpFile, "ERROR: Unable to open X display \nExiting now..\n");
		uninitialize();
		exit(1);
	}

	defaultScreen = XDefaultScreen(gpDisplay);

	gpXVisualInfo = glXChooseVisual(gpDisplay, defaultScreen, frameBufferAttributes);

	if(gpXVisualInfo == NULL)
	{
		fprintf(gpFile, "ERROR:Unable to get a visual info.\nExiting now..\n");
		uninitialize();
		exit(1);
	}

	winAttribs.border_pixel = 0;
	winAttribs.background_pixmap = 0;
	winAttribs.colormap = XCreateColormap(gpDisplay,
						RootWindow(gpDisplay, gpXVisualInfo->screen),
						gpXVisualInfo->visual, AllocNone);

	gColormap = winAttribs.colormap;

	winAttribs.background_pixel = BlackPixel(gpDisplay, defaultScreen);

	winAttribs.event_mask =ExposureMask |
				VisibilityChangeMask |
				ButtonPressMask |
				KeyPressMask |
				PointerMotionMask |
				StructureNotifyMask;

	styleMask = CWBorderPixel | CWBackPixel | CWEventMask | CWColormap;

	gWindow = XCreateWindow(gpDisplay, RootWindow(gpDisplay, gpXVisualInfo->screen),
							0,
							0,
							giWindowWidth,
							giWindowHight,
							0,
							gpXVisualInfo->depth,
							InputOutput,
							gpXVisualInfo->visual,
							styleMask,
							&winAttribs);

	if(!gWindow)
	{
		fprintf(gpFile, "ERROR: Failed to create main window.\n Exiting...\n");
		uninitialize();
		exit(1);
	}

	XStoreName(gpDisplay, gWindow, "XWindow Dynamic India");

	Atom windowManagerDelete = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(gpDisplay, gWindow, &windowManagerDelete, 1);

	XMapWindow(gpDisplay, gWindow);
}

void ToggleFullscreen(void)
{
	//variable declarations
	Atom wm_state;
	Atom fullscreen;
	XEvent xev = {0};

	//code
	wm_state = XInternAtom(gpDisplay, "_NET_WM_STATE", False);
	memset(&xev, 0, sizeof(xev));

	xev.type = ClientMessage;
	xev.xclient.window = gWindow;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = gbFullscreen ? 0 : 1;

	fullscreen = XInternAtom(gpDisplay, "_NET_WM_STATE_FULLSCREEN", False);

	xev.xclient.data.l[1] = fullscreen;

	XSendEvent( gpDisplay,
		    RootWindow(gpDisplay, gpXVisualInfo->screen),
		    False,
		    StructureNotifyMask,
		    &xev);
}

void initialize(void)
{
	//function declarations
	void resize(int, int);

	//code
	gGLXContext = glXCreateContext(gpDisplay, gpXVisualInfo, NULL, GL_TRUE);
	glXMakeCurrent(gpDisplay, gWindow, gGLXContext);

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

	//warmup resize call
	resize(giWindowWidth, giWindowHight);
}

void resize(int width, int hight)
{
	//code
	if(hight <= 0)
		hight = 1;

	glViewport(0, 0, GLsizei(width), GLsizei(hight));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(	45.0f,
			(GLfloat)width/(GLfloat)hight,
			0.1f,
			100.0f);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

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

	glXSwapBuffers(gpDisplay, gWindow);
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
//----------------------------------------------
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
	//variable declarations
	GLXContext currentGLXContext;

	//code
	currentGLXContext = glXGetCurrentContext();
	if(currentGLXContext)
	{
		glXMakeCurrent(gpDisplay, 0, 0);
		glXDestroyContext(gpDisplay, currentGLXContext);
	}
	
	if(gWindow)
	{
		XDestroyWindow(gpDisplay, gWindow);
	}

	if(gColormap)
	{
		XFreeColormap(gpDisplay, gColormap);
	}

	if(gpXVisualInfo)
	{
		free(gpXVisualInfo);
		gpXVisualInfo = NULL;
	}

	if(gpDisplay)
	{
		XCloseDisplay(gpDisplay);
		gpDisplay = NULL;
	}

	if(gpFile)
	{
		fprintf(gpFile, "DEBUG:Log File Closed Successfully\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}

