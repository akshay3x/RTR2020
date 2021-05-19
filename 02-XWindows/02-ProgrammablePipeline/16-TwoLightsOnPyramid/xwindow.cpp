#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>

#include <GL/glew.h>

#include <GL/gl.h>	//for openGL apis
#include <GL/glx.h> //for glx apis // /usr/include->gl folder

#include "vmath.h"

//namespace
using namespace std;
using namespace vmath;
enum
{
	ATTRIBUTE_POSITION = 0,
	ATTRIBUTE_COLOR,
	ATTRIBUTE_NORMAL,
	ATTRIBUTE_TEXTURE0
};

//global variable declarations
Display *gpDisplay = NULL;
XVisualInfo *gpXVisualInfo = NULL;
Colormap gColormap;
Window gWindow;

GLXContext gGLXContext;
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display* , GLXFBConfig ,GLXContext , Bool , const int*);
glXCreateContextAttribsARBProc glxCreateContextAttribsARB = NULL;
GLXFBConfig gGLXFBConfig;

GLuint gVertexShaderObject;
GLuint gFragmentShaderObject;
GLuint gShaderProgramObject;

GLuint gModelMatrixUniform;
GLuint gViewMatrixUniform;
GLuint gProjectionMatrixUniform;

GLuint gLightAmbientUniform;
GLuint gLightDiffuseUniform;
GLuint gLightSpecularUniform;
GLuint gLightPositionUniform;

GLuint gMaterialAmbientUniform;
GLuint gMaterialDiffuseUniform;
GLuint gMaterialSpecularUniform;
GLuint gMaterialShininessUniform;

GLuint gLKeyPressedUniform;
GLuint gVaoPyramid;
GLuint gVboPyramid;
GLuint gVboPyramidNormals;

mat4 gPerspectiveProjectionMatrix;

bool gbFullscreen = false;

int giWindowWidth = 800;
int giWindowHight = 600;

//debug file
FILE *gpFile = NULL;

GLfloat anglePyramid = 0.0f;
bool gbLight = false;
bool gbAnimate = false;

struct Light
{
	vec4 lightAmbientColor[2];
	vec4 lightDiffuseColor[2];
	vec4 lightSpecularColor[2];
	vec4 lightPositionColor[2];
};

struct Light LightRB;

GLfloat materialAmbient[]  = { 0.0f, 0.0f, 0.0f, 1.0f};
GLfloat materialDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f}; //White
GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f}; //White
GLfloat materialShininess  = 128.0f;

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

					case XK_A:
					case XK_a:
						if(gbAnimate == false)
							gbAnimate = true; 
						else
							gbAnimate = false;
					break;

					case XK_L:
					case XK_l:
						if(gbLight == false)
							gbLight = true; 
						else
							gbLight = false;
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

	GLXFBConfig *pGLXFBConfig = NULL;
	GLXFBConfig bestGLXFBConfig;
	XVisualInfo *pTempXVisualInfo = NULL;
	int numFBConfig = 0;

	int defaultScreen;
	int styleMask;

	static int frameBufferAttributes[] =
	{ 
		GLX_X_RENDERABLE,		True,
		GLX_DRAWABLE_TYPE,		GLX_WINDOW_BIT,
		GLX_RENDER_TYPE,		GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE,		GLX_TRUE_COLOR,
		GLX_RED_SIZE,   		8,
		GLX_GREEN_SIZE, 		8,
		GLX_BLUE_SIZE,  		8,
		GLX_ALPHA_SIZE, 		8,
		GLX_DEPTH_SIZE, 		24,
		GLX_STENCIL_SIZE,		8,
		GLX_DOUBLEBUFFER, 		True,
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

	pGLXFBConfig = glXChooseFBConfig(gpDisplay, XDefaultScreen(gpDisplay), frameBufferAttributes, &numFBConfig);

	fprintf(gpFile, "fbconfigs = %d \n", numFBConfig);

	int bestFrameBufferConfig		= -1;
	int worstFrameBufferConfig		= -1;
	int bestNumberOfSamples			= -1;
	int worstNumberOfSample			= 999;

	for(int i = 0; i < numFBConfig; i++)
	{
		pTempXVisualInfo = glXGetVisualFromFBConfig(gpDisplay, pGLXFBConfig[i]);
		//fprintf( gpFile, "visual ID = 0x%lx\n", pTempXVisualInfo->visualid );

		if(pTempXVisualInfo != NULL)
		{
			int sampleBuffers, samples;
			glXGetFBConfigAttrib(gpDisplay, pGLXFBConfig[i], GLX_SAMPLE_BUFFERS, &sampleBuffers);
			glXGetFBConfigAttrib(gpDisplay, pGLXFBConfig[i], GLX_SAMPLES, &samples);

			if(bestFrameBufferConfig < 0 || ((sampleBuffers && samples) > bestNumberOfSamples))
			{
				bestFrameBufferConfig = i;
				bestNumberOfSamples = samples;
			}

			if((worstFrameBufferConfig < 0) || (!sampleBuffers) || (samples < worstNumberOfSample))
			{
				worstFrameBufferConfig = i;
				worstNumberOfSample = samples;
			}
		}
	}
	XFree(pTempXVisualInfo);

	bestGLXFBConfig = pGLXFBConfig[bestFrameBufferConfig];
	gGLXFBConfig = bestGLXFBConfig;

	XFree(pGLXFBConfig);

	gpXVisualInfo = glXGetVisualFromFBConfig(gpDisplay, gGLXFBConfig);
	if(gpXVisualInfo == NULL)
	{
		fprintf(gpFile, "ERROR:Unable to get a visual info.\nExiting now..\n");
		uninitialize();
		exit(1);
	}

	fprintf(gpFile, "====bestFrameBufferConfig = %d ===== \n", bestFrameBufferConfig);
	fprintf( gpFile, "visual ID = 0x%lx\n", gpXVisualInfo->visualid );

	winAttribs.border_pixel = 0;
	winAttribs.background_pixmap = 0;
	winAttribs.colormap = XCreateColormap(gpDisplay,
						RootWindow(gpDisplay, gpXVisualInfo->screen),
						gpXVisualInfo->visual, AllocNone);

	gColormap = winAttribs.colormap;

	winAttribs.background_pixel = BlackPixel(gpDisplay, defaultScreen);

	winAttribs.event_mask =
				ExposureMask |
				VisibilityChangeMask |
				ButtonPressMask |
				KeyPressMask |
				PointerMotionMask |
				StructureNotifyMask;

	styleMask = CWBorderPixel | CWBackPixel | CWEventMask | CWColormap;

	gWindow = XCreateWindow(
		gpDisplay,
		RootWindow(gpDisplay, gpXVisualInfo->screen),
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

	XStoreName(gpDisplay, gWindow, " XWindows | Two Lights on Pyramid");

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
	void uninitialize();

	//variable declarations
	int numExtensions = 0;
	FILE *gpGLExtensionsFile = NULL;

	//code
	glxCreateContextAttribsARB = NULL;
	glxCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB((const GLubyte*)("glXCreateContextAttribsARB"));

	const int attribs[] = 
	{
		GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
		GLX_CONTEXT_MINOR_VERSION_ARB, 5,
		GLX_CONTEXT_PROFILE_MASK_ARB,
		GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
		None, 0
	};

	gGLXContext = glxCreateContextAttribsARB(gpDisplay, gGLXFBConfig, 0, True, attribs);

	if(gGLXContext == NULL)
	{
		const int attribs_low[] = 
		{
			GLX_CONTEXT_MAJOR_VERSION_ARB,	1,
			GLX_CONTEXT_MINOR_VERSION_ARB,	0,
			GLX_CONTEXT_PROFILE_MASK_ARB,	0,
			None
		};

		gGLXContext = glxCreateContextAttribsARB(gpDisplay, gGLXFBConfig, 0, True, attribs_low);
		if(gGLXContext == NULL)
		{
			fprintf(gpFile, "ERROR: glxCreateContextAttribsARB().\n Exiting...\n");
			uninitialize();
			exit(1);
		}
	}

	Bool isDirectContext = glXIsDirect(gpDisplay, gGLXContext);

	if(isDirectContext == True)
		fprintf(gpFile, "DEBUG: Direct Rendering Context\n");
	else
		fprintf(gpFile, "DEBUG: NON Direct Rendering Context\n");

	glXMakeCurrent(gpDisplay, gWindow, gGLXContext);

	GLenum glew_error = glewInit();
	if(glew_error != GLEW_OK)
	{
		glXDestroyContext(gpDisplay, gGLXContext);
		gGLXContext = NULL;
		fprintf(gpFile, "DEBUG: glewInit() Failed\n");
		uninitialize();
		exit(1);
	}

	gpGLExtensionsFile = fopen("./EXTENSIONS_LOG.TXT", "w");
	if( gpFile == NULL)
	{
		printf("ERROR: Debug File Open Failed\n:");
		exit(0);
	}
	else
	{
		fprintf(gpFile, "DEBUG:Extensions File Created Successfully\n");
	}

	fprintf(gpGLExtensionsFile, "OpenGL Vendor  :%s\n", glGetString(GL_VENDOR));
	fprintf(gpGLExtensionsFile, "OpenGL Renderer:%s\n", glGetString(GL_RENDERER));
	fprintf(gpGLExtensionsFile, "OpenGL Version :%s\n", glGetString(GL_VERSION));
	fprintf(gpGLExtensionsFile, "OpenGL Shading Language (GLSL) Version:%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	glGetIntegerv (GL_NUM_EXTENSIONS, &numExtensions);
	for(int i = 0; i < numExtensions; i++)
	{
		fprintf(gpGLExtensionsFile, "%s\n", glGetStringi(GL_EXTENSIONS, i));
	}
	fclose(gpGLExtensionsFile);
	gpGLExtensionsFile = NULL;

	//vertex shader
	//create vertex shader
	gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCode =
	" #version 450 core \n" \
	" in vec4 vPosition; \n" \
	" in vec3 vNormal; \n" \
	" uniform mat4 u_model_matrix; \n" \
	" uniform mat4 u_view_matrix; \n" \
	" uniform mat4 u_projection_matrix; \n" \
	" uniform int u_LkeyPressed; \n" \
	" uniform vec4 u_la[2]; \n" \
	" uniform vec4 u_ld[2]; \n" \
	" uniform vec4 u_ls[2]; \n" \
	" uniform vec4 u_light_position[2]; \n" \
	" uniform vec4 u_ka; \n" \
	" uniform vec4 u_kd; \n" \
	" uniform vec4 u_ks; \n" \
	" uniform float u_material_shininess; \n" \
	" out vec3 fong_ads_light; \n" \
	" void main(void) \n" \
	"	{ \n" \
	"		vec3 ambient[2];\n" \
	"		vec3 diffuse[2];\n" \
	"		vec3 specular[2];\n" \
	"		vec3 light_direction[2];\n" \
	"		vec3 reflection_vector[2];\n" \

	"		if(u_LkeyPressed == 1) \n" \
	"			{ \n" \
	"				vec4 eye_coordinates	=  u_view_matrix * u_model_matrix * vPosition; \n" \
	"				vec3 tranformed_norm	= normalize( mat3( u_view_matrix * u_model_matrix) * vNormal); \n" \
	"				vec3 view_vector 		= normalize(-eye_coordinates.xyz); \n" \
	"				for(int i = 0; i < 2; i++)\n" \
	"				{ \n" \
	"					light_direction[i]		= normalize( vec3( u_light_position[i] - eye_coordinates)); \n" \
	"					reflection_vector[i]	= reflect( -light_direction[i], tranformed_norm); \n" \
	"					ambient[i]	= vec3(u_la[i] * u_ka); \n" \
	"					diffuse[i]	= vec3(u_ld[i] * u_kd * max( dot( light_direction[i], tranformed_norm), 0.0f));\n" \
	"					specular[i]	= vec3(u_ls[i] * u_ks *  pow( max( dot( reflection_vector[i], view_vector), 0.0f), u_material_shininess)); \n" \

	"					fong_ads_light	= fong_ads_light + ambient[i] + diffuse[i] + specular[i]; \n" \
	"				} \n" \
	"			} \n" \

	"		else \n" \
	"			{ \n" \
	"				fong_ads_light = vec3(1.0f, 1.0f, 1.0f); \n" \
	"			} \n" \

	"		gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition; \n" \
	"	} \n";

	//provide shader source code  
	glShaderSource(gVertexShaderObject, 1, (const GLchar**)&vertexShaderSourceCode, NULL);

	//cpompile shader
	glCompileShader(gVertexShaderObject);

	//Error checking for shader compilation
	GLint iShaderCompileStatus = 0;
	GLint iInfoLogLength = 0;
	char* szInfoLog = NULL;

	glGetShaderiv(gVertexShaderObject, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if(iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(gVertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if(iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if(szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gVertexShaderObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Vertex Shader Compilation log: %s\n", szInfoLog);
				free(szInfoLog);
				exit(1);
			}
		}
	}

	//Fragment Shader
	//create shader
	gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *gFragmentShaderSourceCode = 
	" #version 450 core \n" \

	" in vec3 fong_ads_light; \n"\
	" out vec4 FragColor; \n" \

	" void main(void) \n" \
	"	{ \n" \
	"		FragColor = vec4(fong_ads_light, 1.0); \n" \
	" 	} \n";


	//provide shader 
	glShaderSource(gFragmentShaderObject, 1, (const GLchar**)&gFragmentShaderSourceCode, NULL);

	//compile shader
	glCompileShader(gFragmentShaderObject); 

	glGetShaderiv(gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if(iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if(iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if(szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gFragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Fragment Shader Compilation log: %s\n", szInfoLog);
				free(szInfoLog);
				exit(1);
			}
		}
	}

	//shader program
	//create shader programm
	gShaderProgramObject = glCreateProgram(); 

	//attach compiled shaders to program
	glAttachShader(gShaderProgramObject, gVertexShaderObject);
	glAttachShader(gShaderProgramObject, gFragmentShaderObject);

	glBindAttribLocation(gShaderProgramObject, ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(gShaderProgramObject, ATTRIBUTE_NORMAL, "vNormal");

	//linking shader program
	glLinkProgram(gShaderProgramObject);
	
	//Error checking for linking shader program
	GLint iShaderProgramLinkStatus = 0;

	glGetProgramiv(gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if(iShaderProgramLinkStatus == GL_FALSE)
	{
		
		glGetProgramiv(gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if(iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if(szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Shader Program Link Log: %s\n", szInfoLog);
				free(szInfoLog);
				exit(1);
			}
		}
	}

	gModelMatrixUniform	= glGetUniformLocation(gShaderProgramObject, "u_model_matrix");
	gViewMatrixUniform	= glGetUniformLocation(gShaderProgramObject, "u_view_matrix");
	gProjectionMatrixUniform = glGetUniformLocation(gShaderProgramObject, "u_projection_matrix");
	gLKeyPressedUniform	= glGetUniformLocation(gShaderProgramObject, "u_LkeyPressed");

	gLightAmbientUniform	= glGetUniformLocation(gShaderProgramObject, "u_la");
	gLightDiffuseUniform	= glGetUniformLocation(gShaderProgramObject, "u_ld");
	gLightSpecularUniform	= glGetUniformLocation(gShaderProgramObject, "u_ls");
	gLightPositionUniform	= glGetUniformLocation(gShaderProgramObject, "u_light_position");

	gMaterialAmbientUniform	= glGetUniformLocation(gShaderProgramObject, "u_ka");
	gMaterialDiffuseUniform	= glGetUniformLocation(gShaderProgramObject, "u_kd");
	gMaterialSpecularUniform 	= glGetUniformLocation(gShaderProgramObject, "u_ks");
	gMaterialShininessUniform	= glGetUniformLocation(gShaderProgramObject, "u_material_shininess");

	const GLfloat pyramidVertices[] = 
	{
		 0.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,
		 1.0f, -1.0f, 1.0f,

		 0.0f,  1.0f,  0.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,

		 0.0f,  1.0f,  0.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		 0.0f,  1.0f,  0.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f
	};

	const GLfloat pyramidNormals[] = 
	{
		// FRONT FACE
		0.0f,0.447214f,0.894427f,
		0.0f,0.447214f,0.894427f,
		0.0f,0.447214f,0.894427f,

		// RIGHT FACE
		0.894427f, 0.447214f, 0.0f,
		0.894427f, 0.447214f, 0.0f,
		0.894427f, 0.447214f, 0.0f,

		// BACK FACE
		0.0f, 0.447214f, -0.894427f,
		0.0f, 0.447214f, -0.894427f,
		0.0f, 0.447214f, -0.894427f,

		// LEFT FACE
		-0.894427f, 0.447214f, 0.0f,
		-0.894427f, 0.447214f, 0.0f,
		-0.894427f, 0.447214f, 0.0f
	};


	glGenVertexArrays(1, &gVaoPyramid);
	glBindVertexArray(gVaoPyramid);

	glGenBuffers(1, &gVboPyramid);
	glBindBuffer(GL_ARRAY_BUFFER, gVboPyramid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVboPyramidNormals);
	glBindBuffer(GL_ARRAY_BUFFER, gVboPyramidNormals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidNormals), pyramidNormals, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0);

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

	gPerspectiveProjectionMatrix = mat4::identity();

	//LightSource0
	LightRB.lightAmbientColor[0] =	vec4( 0.0f, 0.0f, 0.0f, 1.0f);
	LightRB.lightDiffuseColor[0] =	vec4( 1.0f, 0.0f, 0.0f, 1.0f); //Red
	LightRB.lightSpecularColor[0] =	vec4( 1.0f, 0.0f, 0.0f, 1.0f); //Red
	LightRB.lightPositionColor[0] =	vec4( 2.0f, 0.0f, 0.0f, 1.0f); //

	//LightSource1
	LightRB.lightAmbientColor[1] =	vec4( 0.0f, 0.0f, 0.0f, 1.0f);
	LightRB.lightDiffuseColor[1] =	vec4( 0.0f, 0.0f, 1.0f, 1.0f); //Red
	LightRB.lightSpecularColor[1] =	vec4( 0.0f, 0.0f, 1.0f, 1.0f); //Red
	LightRB.lightPositionColor[1] =	vec4(-2.0f, 0.0f, 0.0f, 1.0f); //

	//warmup resize call
	resize(giWindowWidth, giWindowHight);
}

void resize(int width, int hight)
{
	//code
	if(hight <= 0)
		hight = 1;

	glViewport(0, 0, GLsizei(width), GLsizei(hight));
	gPerspectiveProjectionMatrix = perspective(45.0f, (GLfloat)width/(GLfloat)hight, 0.1f, 100.0f);
}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

	glUseProgram(gShaderProgramObject);

	mat4 modelMatrix;
	mat4 ViewMatrix;
	mat4 translateMatrix;
	mat4 scaleMatrix;
	mat4 rotationMatrix;
	mat4 modelViewProjectionMatrix;

	modelMatrix = mat4::identity();
	ViewMatrix = mat4::identity();
	translateMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	modelViewProjectionMatrix = mat4::identity();

	if(gbLight == true)
	{


		glUniform4fv(gLightAmbientUniform,	4, (GLfloat *)&LightRB.lightAmbientColor);
		glUniform4fv(gLightDiffuseUniform,	4, (GLfloat *)&LightRB.lightDiffuseColor);
		glUniform4fv(gLightSpecularUniform,	4, (GLfloat *)&LightRB.lightSpecularColor);
		glUniform4fv(gLightPositionUniform,	4, (GLfloat *)&LightRB.lightPositionColor);

		glUniform1i(gLKeyPressedUniform, 1);

		glUniform4fv(gMaterialAmbientUniform, 	1, (GLfloat *)materialAmbient);
		glUniform4fv(gMaterialDiffuseUniform,	1, (GLfloat *)materialDiffuse);
		glUniform4fv(gMaterialSpecularUniform,	1, (GLfloat *)materialSpecular);
		glUniform1f(gMaterialShininessUniform, 128.0f);
	}
	else
	{
		glUniform1i(gLKeyPressedUniform, 0);
	}

	translateMatrix = translate(0.0f, 0.0f , -6.0f);
	rotationMatrix = rotate(anglePyramid, 0.0f, 1.0f, 0.0f);
	modelMatrix = translateMatrix * rotationMatrix;

	glUniformMatrix4fv(gModelMatrixUniform,	1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(gViewMatrixUniform,	1, GL_FALSE, ViewMatrix);
	glUniformMatrix4fv(gProjectionMatrixUniform,	1, GL_FALSE, gPerspectiveProjectionMatrix);

	glBindVertexArray(gVaoPyramid);

	glDrawArrays(GL_TRIANGLES, 0, 12);

	glBindVertexArray(0);

	glUseProgram(0);

	glXSwapBuffers(gpDisplay, gWindow);
}


void update(void)
{
	//code
	if(gbAnimate == true)
	{
		anglePyramid = anglePyramid + 1.0f;
		if(anglePyramid > 360.0f)
			anglePyramid = 0.0f;
	}
}

void uninitialize(void)
{
	//variable declarations
	GLXContext currentGLXContext;

	//code
		if(gVaoPyramid)
	{
		glDeleteVertexArrays(1, &gVaoPyramid);
		gVaoPyramid = 0;
	}

	if(gVboPyramid)
	{
		glDeleteBuffers(1, &gVboPyramid);
		gVboPyramid = 0;
	}

	glDetachShader(gShaderProgramObject, gVertexShaderObject);
	glDetachShader(gShaderProgramObject, gFragmentShaderObject);

	if(gVertexShaderObject)
	{
		glDeleteShader(gVertexShaderObject);
		gVertexShaderObject = 0;
	}

	if(gFragmentShaderObject)
	{
		glDeleteShader(gFragmentShaderObject);
		gFragmentShaderObject = 0;
	}

	if(gShaderProgramObject)
	{
		glDeleteProgram(gShaderProgramObject);
		gShaderProgramObject = 0;
	}

	glUseProgram(0);

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
