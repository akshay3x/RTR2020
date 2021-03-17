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

#include "sphere_materials.h"

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

//LightSource
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
	void update(void);

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

						case 'X':
						case 'x':
							keyPressed = 1;
							AngleForXRotation = 1;
							break;

						case 'Y':
						case 'y':
							keyPressed = 2;
							AngleForXRotation = 1;
							break;

						case 'Z':
						case 'z':
							keyPressed = 3;
							AngleForXRotation = 1;
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

	XStoreName(gpDisplay, gWindow, "XWindow 24 Spheres");

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

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f); //Dark Grey

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

	glXSwapBuffers(gpDisplay, gWindow);
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

	glTranslatef(9.5f, 12.0f, 0.0f);

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

	gluSphere(quadric[19], 1.0, 30, 30);
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
		for(int i = 0; i < 24; i++)
		{
			gluDeleteQuadric(quadric[i]);
			quadric[i] = NULL;
		}
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

