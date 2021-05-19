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
#include "Sphere.h"

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

GLuint gVertexShaderObjectPerVertex;
GLuint gFragmentShaderObjectPerVertex;
GLuint gShaderProgramObjectPerVertex;

GLuint gVertexShaderObjectPerFragment;
GLuint gFragmentShaderObjectPerFragment;
GLuint gShaderProgramObjectPerFragment;

GLuint gVao_sphere;
GLuint gVbo_sphere_position;
GLuint gVbo_sphere_normal;
GLuint gVbo_sphere_element;

GLuint gModelMatrixUniformPerVertex;
GLuint gViewMatrixUniformPerVertex;
GLuint gPerspectiveProjectionMatrixUniformPerVertex;

GLuint gLightAmbientUniformPerVertex;
GLuint gLightDiffuseUniformPerVertex;
GLuint gLightSpecularUniformPerVertex;
GLuint gLightPositionUniformPerVertex;

GLuint gMaterialAmbientUniformPerVetex;
GLuint gMaterialDiffuseUniformPerVetex;
GLuint gMaterialSpecularUniformPerVetex;
GLuint gMaterialShininessUniformPerVetex;

GLuint gLKeyPressedUniformPerVertex;

GLuint gModelMatrixUniformPerFragment;
GLuint gViewMatrixUniformPerFragment;
GLuint gPerspectiveProjectionMatrixUniformPerFragment;

GLuint gLightAmbientUniformPerFragment;
GLuint gLightDiffuseUniformPerFragment;
GLuint gLightSpecularUniformPerFragment;
GLuint gLightPositionUniformPerFragment;

GLuint gMaterialAmbientUniformPerFragment;
GLuint gMaterialDiffuseUniformPerFragment;
GLuint gMaterialSpecularUniformPerFragment;
GLuint gMaterialShininessUniformPerFragment;

GLuint gLKeyPressedUniformPerFragment;

mat4 gPerspectiveProjectionMatrix;

bool gbFullscreen = false;
bool gbLight = false;
bool gPerVertexLighting = false;
bool gPerFragmentLighting =false;

float sphere_vertices[1146];
float sphere_normals[1146];
float sphere_textures[764];
unsigned short sphere_elements[2280];

GLuint gNumVertices = 0;
GLuint gNumElements = 0;

int giWindowWidth = 800;
int giWindowHight = 600;

//debug file
FILE *gpFile = NULL;

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
					case XK_Q:
					case XK_q:
					bDone = true;
					break;

					case XK_Escape:
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

					case XK_L:
					case XK_l:
						if(gbLight == false)
							gbLight = true; 
						else
							gbLight = false;
					break;

					case XK_F:
					case XK_f:
							gPerFragmentLighting = true;
							gPerVertexLighting = false;
							//gbLight = true; 
					break;

					case XK_V:
					case XK_v:
							gPerFragmentLighting = false; 
							gPerVertexLighting = true;
							//gbLight = true; 
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

	XStoreName(gpDisplay, gWindow, " XWindows | Perfragment-Pervertex Toggle Lights on Sphere");

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
	gVertexShaderObjectPerVertex = glCreateShader(GL_VERTEX_SHADER);
	gVertexShaderObjectPerFragment = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCodePerVertex =
	" #version 450 core \n" \

	" in vec4 vPosition; \n" \
	" in vec3 vNormal; \n" \

	" uniform mat4 u_model_matrix; \n" \
	" uniform mat4 u_view_matrix; \n" \
	" uniform mat4 u_projection_matrix; \n" \

	" uniform int u_LkeyPressed; \n" \

	" uniform vec4 u_la; \n" \
	" uniform vec4 u_ld; \n" \
	" uniform vec4 u_ls; \n" \
	" uniform vec4 u_light_position; \n" \

	" uniform vec4 u_ka; \n" \
	" uniform vec4 u_kd; \n" \
	" uniform vec4 u_ks; \n" \
	" uniform float u_material_shininess; \n" \

	" out vec3 fong_ads_light; \n" \

	" void main(void) \n" \
	"	{ \n" \
	"		if(u_LkeyPressed == 1) \n" \
	"			{ \n" \
	"				vec4 eye_coordinates	= u_view_matrix * u_model_matrix * vPosition; \n" \
	"				vec3 tranformed_norm	= normalize( mat3( u_view_matrix * u_model_matrix) * vNormal); \n" \
	"				vec3 light_direction	= normalize( vec3( u_light_position - eye_coordinates)); \n" \
	"				vec3 reflection_vector	= reflect( -light_direction, tranformed_norm); \n" \
	"				vec3 view_vector 		= normalize(-eye_coordinates.xyz); \n" \
	"				vec3 ambient	= vec3(u_la * u_ka); \n" \
	"				vec3 diffuse	= vec3(u_ld * u_kd * max( dot( light_direction, tranformed_norm), 0.0f)); \n" \
	"				vec3 specular	= vec3(u_ls * u_ks *  pow( max( dot( reflection_vector, view_vector), 0.0f), u_material_shininess)); \n" \
	"				fong_ads_light	= ambient + diffuse + specular; \n" \
	"			} \n" \
	"			else \n" \
	"			{	\n" \
	"				fong_ads_light = vec3(1.0f,1.0f, 1.0f); \n" \
	"			} \n" \

	"		gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition; \n" \
	"	} \n";

	const GLchar *vertexShaderSourceCodePerFragment =
	" #version 450 core \n" \

	" in vec4 vPosition; \n" \
	" in vec3 vNormal; \n" \

	" uniform mat4 u_model_matrix; \n" \
	" uniform mat4 u_view_matrix; \n" \
	" uniform mat4 u_projection_matrix; \n" \

	" uniform vec4 u_light_position; \n" \

	" out vec3 out_tranformed_norm; \n" \
	" out vec3 out_light_direction; \n" \
	" out vec3 out_view_vector; \n" \

	" void main(void) \n" \
	"	{ \n" \

	"		vec4 eye_coordinates	= u_model_matrix * u_view_matrix * vPosition; \n" \
	"		out_tranformed_norm		= vec3( mat3( u_view_matrix * u_model_matrix) * vNormal); \n" \
	"		out_light_direction		= vec3( u_light_position - eye_coordinates); \n" \
	"		out_view_vector			= (-eye_coordinates.xyz); \n" \

	"		gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition; \n" \
	"	} \n";

	//provide shader source code  
	glShaderSource(gVertexShaderObjectPerVertex, 1, (const GLchar**)&vertexShaderSourceCodePerVertex, NULL);
	glShaderSource(gVertexShaderObjectPerFragment, 1, (const GLchar**)&vertexShaderSourceCodePerFragment, NULL);

	//cpompile shader
	glCompileShader(gVertexShaderObjectPerVertex);
	glCompileShader(gVertexShaderObjectPerFragment);

	//Error checking for shader compilation
	GLint iShaderCompileStatus = 0;
	GLint iInfoLogLength = 0;
	char* szInfoLog = NULL;

	glGetShaderiv(gVertexShaderObjectPerVertex, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if(iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(gVertexShaderObjectPerVertex, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if(iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if(szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gVertexShaderObjectPerVertex, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Vertex Shader per vertex Compilation log: %s\n", szInfoLog);
				free(szInfoLog);
				exit(1);
			}
		}
	}


	glGetShaderiv(gVertexShaderObjectPerFragment, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if(iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(gVertexShaderObjectPerFragment, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if(iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if(szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gVertexShaderObjectPerFragment, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Vertex Shader per fragment Compilation log: %s\n", szInfoLog);
				free(szInfoLog);
				exit(1);
			}
		}
	}

	//Fragment Shader
	//create shader
	gFragmentShaderObjectPerVertex = glCreateShader(GL_FRAGMENT_SHADER);
	gFragmentShaderObjectPerFragment = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *gFragmentShaderSourceCodePerVertex = 
	" #version 450 core \n" \

	" in vec3 fong_ads_light; \n" \
	" uniform int u_LkeyPressed; \n" \
	" out vec4 FragColor; \n" \

	" void main(void) \n" \
	" { \n" \
	"		if(u_LkeyPressed == 1) \n" \
	"			{ \n" \
	"				FragColor = vec4(fong_ads_light, 1.0f); \n" \
	"			} \n" \
	"			else \n" \
	"			{ \n" \
	"  				FragColor = vec4(fong_ads_light, 1.0f); \n" \
	"			} \n" \
	" } \n";


	const GLchar *gFragmentShaderSourceCodePerFragment =
	" #version 450 core \n" \

	" uniform int u_LkeyPressed; \n" \

	" uniform vec4 u_la; \n" \
	" uniform vec4 u_ld; \n" \
	" uniform vec4 u_ls; \n" \

	" uniform vec4 u_ka; \n" \
	" uniform vec4 u_kd; \n" \
	" uniform vec4 u_ks; \n" \
	" uniform float u_material_shininess; \n" \

	" in vec3 out_tranformed_norm; \n" \
	" in vec3 out_light_direction; \n" \
	" in vec3 out_view_vector; \n" \

	" out vec4 FragColor; \n" \

	" void main(void) \n" \
	"	{ \n"\
	"		vec3 fong_ads_light; \n" \

	"		if(u_LkeyPressed == 1) \n" \
	"		{ \n"\

	"			vec3 normalized_transformed_norm	= normalize(out_tranformed_norm);\n" \
	"			vec3 normalized_light_direction		= normalize(out_light_direction);\n" \
	"			vec3 normalized_view_vector			= normalize(out_view_vector);\n" \
	"			vec3 reflection_vector				= reflect(-normalized_light_direction, normalized_transformed_norm); \n" \

	"			vec3 ambient	= vec3(u_la * u_ka) ; \n" \
	"			vec3 diffuse	= vec3(u_ld * u_kd * max( dot( normalized_light_direction, normalized_transformed_norm), 0.0f));\n" \
	"			vec3 specular	= vec3(u_ls * u_ks * pow( max( dot( reflection_vector, normalized_view_vector), 0.0f), u_material_shininess)); \n" \

	"			fong_ads_light = ambient + diffuse + specular; \n" \

	"		} \n" \

	"		else \n" \
	"		{ \n" \
	"			fong_ads_light = vec3(1.0f, 1.0f, 1.0f); \n" \
	"		} \n" \

	"		FragColor = vec4(fong_ads_light, 1.0); \n" \
	" } \n";

	//provide shader 
	glShaderSource(gFragmentShaderObjectPerVertex, 1, (const GLchar**)&gFragmentShaderSourceCodePerVertex, NULL);
	glShaderSource(gFragmentShaderObjectPerFragment, 1, (const GLchar**)&gFragmentShaderSourceCodePerFragment, NULL);

	//compile shader
	glCompileShader(gFragmentShaderObjectPerVertex);
	glCompileShader(gFragmentShaderObjectPerFragment);

	glGetShaderiv(gFragmentShaderObjectPerVertex, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if(iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(gFragmentShaderObjectPerVertex, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if(iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if(szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gFragmentShaderObjectPerVertex, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Fragment Shader Per Vertex Compilation log: %s\n", szInfoLog);
				free(szInfoLog);
				exit(1);
			}
		}
	}

	glGetShaderiv(gFragmentShaderObjectPerFragment, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if(iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(gFragmentShaderObjectPerFragment, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if(iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if(szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gFragmentShaderObjectPerFragment, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Fragment Shader per fragment Compilation log: %s\n", szInfoLog);
				free(szInfoLog);
				exit(1);
			}
		}
	}

	//shader program
	//create shader programm
	gShaderProgramObjectPerVertex = glCreateProgram(); 
	gShaderProgramObjectPerFragment = glCreateProgram(); 

	//attach compiled shaders to program
	glAttachShader(gShaderProgramObjectPerVertex, gVertexShaderObjectPerVertex);
	glAttachShader(gShaderProgramObjectPerVertex, gFragmentShaderObjectPerVertex);
	
	glAttachShader(gShaderProgramObjectPerFragment, gVertexShaderObjectPerFragment);
	glAttachShader(gShaderProgramObjectPerFragment, gFragmentShaderObjectPerFragment);

	glBindAttribLocation(gShaderProgramObjectPerVertex, ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(gShaderProgramObjectPerVertex, ATTRIBUTE_NORMAL, "vNormal");

	glBindAttribLocation(gShaderProgramObjectPerFragment, ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(gShaderProgramObjectPerFragment, ATTRIBUTE_NORMAL, "vNormal");

	//linking shader program
	glLinkProgram(gShaderProgramObjectPerVertex);
	glLinkProgram(gShaderProgramObjectPerFragment);
	
	//Error checking for linking shader program
	GLint iShaderProgramLinkStatus = 0;

	glGetProgramiv(gShaderProgramObjectPerVertex, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if(iShaderProgramLinkStatus == GL_FALSE)
	{
		
		glGetProgramiv(gShaderProgramObjectPerVertex, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if(iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if(szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(gShaderProgramObjectPerVertex, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Shader Program per vertex Link Log: %s\n", szInfoLog);
				free(szInfoLog);
				exit(1);
			}
		}
	}

	glGetProgramiv(gShaderProgramObjectPerFragment, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if(iShaderProgramLinkStatus == GL_FALSE)
	{
		
		glGetProgramiv(gShaderProgramObjectPerFragment, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if(iInfoLogLength > 0)
		{
			szInfoLog = (char *)malloc(iInfoLogLength);
			if(szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(gShaderProgramObjectPerFragment, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Shader Programm per fragment Link log = %s\n", szInfoLog);
				free(szInfoLog);
				exit(1);
			}
		}
	}

	gModelMatrixUniformPerVertex	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_model_matrix");
	gViewMatrixUniformPerVertex	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_view_matrix");
	gPerspectiveProjectionMatrixUniformPerVertex = glGetUniformLocation(gShaderProgramObjectPerVertex, "u_projection_matrix");
	gLKeyPressedUniformPerVertex	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_LkeyPressed");

	gLightAmbientUniformPerVertex	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_la");
	gLightDiffuseUniformPerVertex	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_ld");
	gLightSpecularUniformPerVertex	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_ls");
	gLightPositionUniformPerVertex	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_light_position");

	gMaterialAmbientUniformPerVetex	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_ka");
	gMaterialDiffuseUniformPerVetex	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_kd");
	gMaterialSpecularUniformPerVetex 	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_ks");
	gMaterialShininessUniformPerVetex	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_material_shininess");

	gModelMatrixUniformPerFragment	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_model_matrix");
	gViewMatrixUniformPerFragment	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_view_matrix");
	gPerspectiveProjectionMatrixUniformPerFragment = glGetUniformLocation(gShaderProgramObjectPerFragment, "u_projection_matrix");
	gLKeyPressedUniformPerFragment	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_LkeyPressed");

	gLightAmbientUniformPerFragment	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_la");
	gLightDiffuseUniformPerFragment	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_ld");
	gLightSpecularUniformPerFragment	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_ls");
	gLightPositionUniformPerFragment	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_light_position");

	gMaterialAmbientUniformPerFragment	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_ka");
	gMaterialDiffuseUniformPerFragment	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_kd");
	gMaterialSpecularUniformPerFragment 	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_ks");
	gMaterialShininessUniformPerFragment	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_material_shininess");


	getSphereVertexData(sphere_vertices, sphere_normals, sphere_textures, sphere_elements);
	gNumVertices = getNumberOfSphereVertices();
	gNumElements = getNumberOfSphereElements();

	//vao
	glGenVertexArrays(1, &gVao_sphere);
	glBindVertexArray(gVao_sphere);

	// position vbo
	glGenBuffers(1, &gVbo_sphere_position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_sphere_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_vertices), sphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &gVbo_sphere_normal);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_sphere_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_normals), sphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &gVbo_sphere_element);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gVbo_sphere_element);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sphere_elements), sphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
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

	mat4 modelMatrix = mat4::identity();
	mat4 viewMatrix = mat4::identity();
	mat4 translateMatrix = mat4::identity();

	if(gPerVertexLighting == true)
	{
		glUseProgram(gShaderProgramObjectPerVertex);

		if(gbLight == true)
		{
			GLfloat lightAmbient[]	= {	0.0f,	0.0f,	0.0f,	1.0f};
			GLfloat lightDiffuse[]	= {	1.0f,	1.0f,	1.0f,	1.0f};//white
			GLfloat lightSpecular[]	= {	1.0f,	1.0f,	1.0f,	1.0f};//white
			GLfloat lightPosition[]	= {	100.0f,	100.0f,	100.0f,	1.0f};//light position

			GLfloat materialAmbient[]	= { 0.0f, 0.0f, 0.0f, 1.0f};
			GLfloat materialDiffuse[]	= { 1.0f, 1.0f, 1.0f, 1.0f};
			GLfloat materialSpecular[]	= { 1.0f, 1.0f, 1.0f, 1.0f};

			glUniform1i(gLKeyPressedUniformPerVertex, 1);

			glUniform4fv(gLightAmbientUniformPerVertex,	1, (GLfloat *)lightAmbient);
			glUniform4fv(gLightDiffuseUniformPerVertex,	1, (GLfloat *)lightDiffuse);
			glUniform4fv(gLightSpecularUniformPerVertex,	1, (GLfloat *)lightSpecular);
			glUniform4fv(gLightPositionUniformPerVertex, 1, (GLfloat *)lightPosition);

			glUniform4fv(gMaterialAmbientUniformPerVetex, 	1, (GLfloat *)materialAmbient);
			glUniform4fv(gMaterialDiffuseUniformPerVetex,	1, (GLfloat *)materialDiffuse);
			glUniform4fv(gMaterialSpecularUniformPerVetex,	1, (GLfloat *)materialSpecular);
			glUniform1f(gMaterialShininessUniformPerVetex, 128.0f);
		}
		else
		{
			glUniform1i(gLKeyPressedUniformPerVertex, 0);
		}

		translateMatrix = translate(0.0f, 0.0f , -3.0f);
		modelMatrix =  translateMatrix;

		glUniformMatrix4fv(gModelMatrixUniformPerVertex, 1, GL_FALSE, modelMatrix);
		glUniformMatrix4fv(gViewMatrixUniformPerVertex,	1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(gPerspectiveProjectionMatrixUniformPerVertex, 1, GL_FALSE, gPerspectiveProjectionMatrix);

		glBindVertexArray(gVao_sphere);

		// *** draw, either by glDrawTriangles() or glDrawArrays() or glDrawElements()
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gVbo_sphere_element);
		glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

		glBindVertexArray(0);

		glUseProgram(0);
	}

	if( gPerFragmentLighting == true)
	{
		modelMatrix = mat4::identity();
		viewMatrix = mat4::identity();
		translateMatrix = mat4::identity();

		glUseProgram(gShaderProgramObjectPerFragment);

		if(gbLight == true)
		{
			GLfloat lightAmbient[]	= {	0.0f,	0.0f,	0.0f,	1.0f};
			GLfloat lightDiffuse[]	= {	1.0f,	1.0f,	1.0f,	1.0f};//white
			GLfloat lightSpecular[]	= {	1.0f,	1.0f,	1.0f,	1.0f};//white
			GLfloat lightPosition[]	= {	100.0f,	100.0f,	100.0f,	1.0f};//light position

			GLfloat materialAmbient[]	= { 0.0f, 0.0f, 0.0f, 1.0f};
			GLfloat materialDiffuse[]	= { 1.0f, 1.0f, 1.0f, 1.0f};
			GLfloat materialSpecular[]	= { 1.0f, 1.0f, 1.0f, 1.0f};

			glUniform1i(gLKeyPressedUniformPerFragment, 1);

			glUniform4fv(gLightAmbientUniformPerFragment,	1, (GLfloat *)lightAmbient);
			glUniform4fv(gLightDiffuseUniformPerFragment,	1, (GLfloat *)lightDiffuse);
			glUniform4fv(gLightSpecularUniformPerFragment,	1, (GLfloat *)lightSpecular);
			glUniform4fv(gLightPositionUniformPerFragment, 1, (GLfloat *)lightPosition);

			glUniform4fv(gMaterialAmbientUniformPerFragment, 	1, (GLfloat *)materialAmbient);
			glUniform4fv(gMaterialDiffuseUniformPerFragment,	1, (GLfloat *)materialDiffuse);
			glUniform4fv(gMaterialSpecularUniformPerFragment,	1, (GLfloat *)materialSpecular);
			glUniform1f(gMaterialShininessUniformPerFragment, 128.0f);
		}
		else
		{
			glUniform1i(gLKeyPressedUniformPerFragment, 0);
		}

		translateMatrix = translate(0.0f, 0.0f , -3.0f);
		modelMatrix =  translateMatrix;

		glUniformMatrix4fv(gModelMatrixUniformPerFragment, 1, GL_FALSE, modelMatrix);
		glUniformMatrix4fv(gViewMatrixUniformPerFragment,	1, GL_FALSE, viewMatrix);
		glUniformMatrix4fv(gPerspectiveProjectionMatrixUniformPerFragment, 1, GL_FALSE, gPerspectiveProjectionMatrix);

		glBindVertexArray(gVao_sphere);

		// *** draw, either by glDrawTriangles() or glDrawArrays() or glDrawElements()
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gVbo_sphere_element);
		glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

		glBindVertexArray(0);

		glUseProgram(0);
	}
	glXSwapBuffers(gpDisplay, gWindow);
}


void update(void)
{
	//code
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
