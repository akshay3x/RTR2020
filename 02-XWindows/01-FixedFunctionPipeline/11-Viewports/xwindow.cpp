#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>

#include <GL/gl.h>	//for openGL apis
#include <GL/glu.h>
#include <GL/glx.h> 	//for glx apis // /usr/include->gl folder

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

GLfloat angle = 0.0f;

unsigned int gVx = 0;
unsigned int gVy = 0;

unsigned int gWidth;
unsigned int gHight;

unsigned int gVwidth = giWindowWidth;
unsigned int gVhight = giWindowHight;

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

	XWindowAttributes window_attributes_return;

	char keys[26];

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
				XGetWindowAttributes(gpDisplay, gWindow, &window_attributes_return);

				gHight = window_attributes_return.height;
				gWidth = window_attributes_return.width;
				XLookupString(&event.xkey, keys, sizeof(keys), NULL, NULL);
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

				switch(keys[0])
				{
					case '0':
						gVx = 0;
						gVy = 0;
						gVwidth = gWidth;
						gVhight = gHight;
						break;

					case XK_1:
						gVx = 0;
						gVy = GLsizei(gHight)/2.0f;
						gVwidth = GLsizei(gWidth)/2.0f;
						gVhight = GLsizei(gHight)/2.0f;
						break;

					case XK_2:
						gVx = GLsizei(gWidth)/2.0f;
						gVy = GLsizei(gHight)/2.0f;
						gVwidth = GLsizei(gWidth)/2.0f;
						gVhight = GLsizei(gHight)/2.0f;
						break;

					case XK_3:
						gVx = GLsizei(gWidth)/2.0f;
						gVy = 0;
						gVwidth = GLsizei(gWidth)/2.0f;
						gVhight = GLsizei(gHight)/2.0f;
						break;

					case XK_4:
						gVx = 0;
						gVy = 0;
						gVwidth = GLsizei(gWidth)/2.0f;
						gVhight = GLsizei(gHight)/2.0f;
						break;

					case XK_5:
						gVx = 0;
						gVy = 0;
						gVwidth = GLsizei(gWidth)/2.0f;
						gVhight = GLsizei(gHight);
						break;

					case XK_6:
						gVx = GLsizei(gWidth)/2.0f;
						gVy = 0;
						gVwidth = GLsizei(gWidth)/2.0f;
						gVhight = GLsizei(gHight);
						break;

					case XK_7:
						gVx = 0;
						gVy = GLsizei(gHight)/2.0f;
						gVwidth = GLsizei(gWidth);
						gVhight = GLsizei(gHight)/2.0f;
						break;

					case XK_8:
						gVx = 0;
						gVy = 0;
						gVwidth = GLsizei(gWidth);
						gVhight = GLsizei(gHight)/2.0f;
						break;

					case XK_9:
						gVx = GLsizei(gWidth)/4.0f;
						gVy = GLsizei(gHight)/4.0f;
						gVwidth = GLsizei(gWidth)/2.0f;
						gVhight = GLsizei(gHight)/2.0f;
						break;

					default:
					break;
				}
				resize(gVwidth, gVhight);
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

	XStoreName(gpDisplay, gWindow, "XWindow Viewports");

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

	glViewport(gVx, gVy, width, hight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,
					(GLfloat)gVwidth/(GLfloat)gVhight,
					0.1f,
					100.0f);
}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -4.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);

	glEnd();

	glXSwapBuffers(gpDisplay, gWindow);
}

void update(void)
{
	//code
	angle = angle + 4.0f;

	if(angle >= 360.0f)
		angle = 0.0f;
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

