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

//debug file
FILE *gpFile = NULL;

GLfloat angleTri = 0.0f;
GLfloat angleCir = 360.0f;
GLfloat xMove = 0.0f;
GLfloat yMove = 0.0f;
GLfloat zMove = 0.0f;

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

	XStoreName(gpDisplay, gWindow, "XWindow Deathly Hallows");

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
	void drawWand(void);
	void drawCloak(void);
	void drawStone(void);

	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-2.0f + xMove,-2.0f + xMove, -3.0f);
	glRotatef(-angleTri, 0.0, 1.0f, 0.0f);
	drawCloak();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(2.0f - yMove, -2.0f + yMove, -3.0f);
	glRotatef(angleCir, 0.0, 1.0f, 0.0f);
	glPointSize(1.0f);
	drawStone();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 2.0f - zMove, -3.0f);
	drawWand();

	glXSwapBuffers(gpDisplay, gWindow);
}

void drawWand(void)
{
	glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, (sin(GLfloat(GL_PI * 7.0/6.0))), 0.0f);
	glEnd();
}

void drawCloak(void)
{
	//code
	glLineWidth(2.0f);

	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f((cos(GLfloat(GL_PI * 7.0/6.0))), sin(GLfloat(GL_PI * 7.0/6.0)), 0.0f);

			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f((cos(GLfloat(GL_PI * 11.0/6.0))), sin(GLfloat(GL_PI * 11/6.0)), 0.0f);

			glVertex3f((cos(GLfloat(GL_PI * 7.0/6.0))), sin(GLfloat(GL_PI * 7.0/6.0)), 0.0f);
			glVertex3f((cos(GLfloat(GL_PI * 11.0/6.0))), sin(GLfloat(GL_PI * 11/6.0)), 0.0f);
	glEnd();
}

void drawStone(void)
{
	//variable declarations
	float i;

	//code
	glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 0.0f);
		for(i = 0; i < 6.28; i = i + 0.0001f )
		{
			glVertex3f((GLfloat((1.0f)+sin(GLfloat(GL_PI * 7.0/6.0))) * float(cos(i))),
			(GLfloat((1.0f)+(sin(GLfloat(GL_PI * 7.0/6.0)))) * float(sin(i))),
			0.0f);
		}
	glEnd();
}

void update(void)
{
	//code
	xMove = xMove + 0.01f;
	if(xMove >=2.0f)
		xMove = 2.0f;

	zMove = zMove + 0.01f;
	if(zMove >=2.0f)
		zMove = 2.0f;

	yMove = yMove + 0.01f;
	if(yMove >=2.0f)
		yMove = 2.0f;

	angleTri = angleTri + 4.0f;
	if(angleTri >= 360.0f)
		angleTri = 0.0f;

	angleCir = angleCir - 4.0f;
	if(angleCir <= 0.0f)
		angleCir = 360.0f;
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

