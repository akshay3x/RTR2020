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

 bool gbLight = false;
 
 GLUquadric *quadric = NULL;

//LightSOurce0
GLfloat lightAmbientZero[]  = { 0.0f, 0.0f, 0.0f, 1.0f}; 
GLfloat lightDiffuseZero[]  = { 1.0f, 0.0f, 0.0f, 1.0f}; //red
GLfloat lightSpecularZero[] = { 1.0f, 0.0f, 0.0f, 1.0f}; //red
GLfloat lightPositionZero[] = { 0.0f, 0.0f, 0.0f, 1.0f}; //Positional Light

//LightSOurce1
GLfloat lightAmbientOne[]  =  { 0.0f, 0.0f, 0.0f, 1.0f};
GLfloat lightDiffuseOne[]  =  { 0.0f, 1.0f, 0.0f, 1.0f}; //green
GLfloat lightSpecularOne[] =  { 0.0f, 1.0f, 0.0f, 1.0f}; //green
GLfloat lightPositionOne[] =  { 0.0f, 0.0f, 0.0f, 1.0f}; //Positional Light

//LightSOurce2
GLfloat lightAmbientTwo[]  =  { 0.0f, 0.0f, 0.0f, 1.0f};
GLfloat lightDiffuseTwo[]  =  { 0.0f, 0.0f, 1.0f, 1.0f}; //blue
GLfloat lightSpecularTwo[] =  { 0.0f, 0.0f, 1.0f, 1.0f}; //blue
GLfloat lightPositionTwo[] =  { 0.0f, 0.0f, 0.0f, 1.0f}; //Positional Light

//MaterialProperties
GLfloat materialAmbient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialShininess  =  50.0f;

GLfloat lightAngleZero = 0.0f;
GLfloat lightAngleOne  = 0.0f;
GLfloat lightAngleTwo  = 0.0f;

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
						XLookupString(&event.xkey, keys, sizeof(keys), NULL, NULL);

						switch(keysym)
						{
							case XK_Escape:
								bDone = true;
								break;

							default:
								break;
						}

						switch(keys[0])
						{
							case 'F':
							case 'f':
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

	XStoreName(gpDisplay, gWindow, "XWindow Lights On Steady Sphere");

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

	glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbientZero);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuseZero);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecularZero);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_AMBIENT,  lightAmbientOne);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  lightDiffuseOne);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecularOne);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2, GL_AMBIENT,  lightAmbientTwo);
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  lightDiffuseTwo);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecularTwo);
	glEnable(GL_LIGHT2);

	glMaterialfv(GL_FRONT,  GL_AMBIENT,   materialAmbient);
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,   materialDiffuse);
	glMaterialfv(GL_FRONT,  GL_SPECULAR,  materialSpecular);
	glMaterialf(GL_FRONT,   GL_SHININESS, materialShininess);

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
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
		gluLookAt(0.0f, 0.0f, 2.0f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f);

		glPushMatrix();
			glRotatef(lightAngleZero, 1.0f, 0.0f, 0.0f);
			lightPositionZero[2] = lightAngleZero;
			glLightfv(GL_LIGHT0, GL_POSITION, lightPositionZero);
		glPopMatrix();

		glPushMatrix();
			glRotatef(lightAngleOne, 0.0f, 1.0f, 0.0f);
			lightPositionOne[2] = lightAngleOne;
			glLightfv(GL_LIGHT1, GL_POSITION, lightPositionOne);
		glPopMatrix();

		glPushMatrix();
			glRotatef(lightAngleTwo, 0.0f, 0.0f, 1.0f);
			lightPositionTwo[0] = lightAngleTwo;
			glLightfv(GL_LIGHT2, GL_POSITION, lightPositionTwo);
		glPopMatrix();

		glTranslatef(0.0f, 0.0f, -1.0f);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		quadric = gluNewQuadric(); 
		gluSphere(quadric, 0.2, 30, 30);
	glPopMatrix();

	glXSwapBuffers(gpDisplay, gWindow);
}

void update(void)
{
	//code
	lightAngleZero = lightAngleZero + 1.0f;
	if(lightAngleZero >= 360)
		lightAngleZero = 0.0f;

	lightAngleOne = lightAngleOne + 1.0f;
	if(lightAngleOne >= 360)
		lightAngleOne = 0.0f;

	lightAngleTwo = lightAngleTwo + 1.0f;
	if(lightAngleTwo >= 360)
		lightAngleTwo = 0.0f;
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

	if(quadric)
	{
		gluDeleteQuadric(quadric);
		quadric = NULL;
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

