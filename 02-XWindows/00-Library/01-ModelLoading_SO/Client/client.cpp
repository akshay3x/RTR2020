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

#include <SOIL/SOIL.h>

#include "mylib.h"

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

bool gbAnimate = false;
bool gbTexture = false;
bool gbLight = false;
bool gbPolygonMode = false;

GLuint MarbleTexture = 0;

GLfloat lightAmbientZero[]  = {   0.0f,   0.0f,    0.0f, 1.0f};
GLfloat lightDiffuseZero[]  = {   1.0f,   1.0f,    1.0f, 1.0f};
GLfloat lightSpecularZero[] = {   1.0f,   1.0f,    1.0f, 1.0f};
GLfloat lightPositionZero[] = { 100.0f, 100.0f, 1000.0f, 1.0f};//light position

GLfloat materialAmbient[]  = { 0.0f, 0.0f, 0.0f, 1.0f};
GLfloat materialDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat MaterialShininess  = 50.0f;

FILE *g_fp_meshfile = NULL;

const char filename[] = "monkeyHead.txt";

float **gpArrayVertices;
float **gpArrayTextures;
float **gpArrayNormals;

int gNumOfFaceTriangles = 0;

int **gpArrayofFaceTrianglesIndices;
int **gpArrayofFaceTextureIndices;
int **gpArrayofFaceNormalsIndices;


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
	gpFile = fopen("./DEBUG_LOG1.TXT", "w");
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

						case 'a':
						case 'A':
							if(gbAnimate == false)
								gbAnimate = true; 
							else
								gbAnimate = false;
							break;

						case 't':
						case 'T':
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

						case 'M':
						case 'm':
							if(gbPolygonMode == false)
							{
								gbPolygonMode = true; 
							}
							else
							{
								gbPolygonMode = false;
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

	XStoreName(gpDisplay, gWindow, "XWindow Teapot With Light");

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
	//variable declaration
	int retVal = 1;

	//function declarations
	void resize(int, int);
	int LoadBitmapTexture(const char *);

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

	retVal = LoadMeshDataFromObj("monkeyHead.txt");

	if(retVal != 0)
		fprintf(gpFile, "DEBUG: ERROR LoadMeshDataFromObj()! Error Code = %d \n", retVal);
	else
	{
		gpArrayVertices = (float **)GetVertexArray();
		gpArrayTextures = (float **)GetTexturesArray();
		gpArrayNormals = (float **)GetNormalsArray();

		gNumOfFaceTriangles = GetNumberOfFaceTriangles();

		gpArrayofFaceTrianglesIndices = (int **)GetFaceTrianglesIndices();
		gpArrayofFaceTextureIndices = (int **)GetFaceTexturesIndices();
		gpArrayofFaceNormalsIndices = (int **)GetFaceNormalsIndices();
	}

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbientZero);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuseZero);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecularZero);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositionZero);
	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT,  GL_AMBIENT,  materialAmbient);
	glMaterialfv(GL_FRONT,  GL_DIFFUSE,  materialDiffuse);
	glMaterialfv(GL_FRONT,  GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT,  GL_SHININESS, MaterialShininess);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef( 0.0f, -0.0f , -5.0f);
	glScalef(1.5f, 1.5f, 1.5f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);


	if(gbPolygonMode == true)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		for(int i = 0; i < gNumOfFaceTriangles; ++i)
		{
		glBegin(GL_TRIANGLES);
			for(int j = 0; j != 3; j++)
			{
				int vi = gpArrayofFaceTrianglesIndices[i][j] - 1;
				int ti = gpArrayofFaceTextureIndices[i][j] - 1;
				int ni = gpArrayofFaceNormalsIndices[i][j] - 1;

				glNormal3f(gpArrayNormals[ni][0], gpArrayNormals[ni][1], gpArrayNormals[ni][2]);
				glTexCoord2f(gpArrayTextures[ti][0], gpArrayTextures[ti][1]);
				glVertex3f(gpArrayVertices[vi][0], gpArrayVertices[vi][1], gpArrayVertices[vi][2]);
			}
		glEnd();
		}

	glXSwapBuffers(gpDisplay, gWindow);
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
	//variable declarations
	GLXContext currentGLXContext;

	//code
	currentGLXContext = glXGetCurrentContext();
	if(currentGLXContext)
	{
		glXMakeCurrent(gpDisplay, 0, 0);
		glXDestroyContext(gpDisplay, currentGLXContext);
	}

	if(MarbleTexture)
	{
		glDeleteTextures(1, &MarbleTexture);
		MarbleTexture = 0;
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

