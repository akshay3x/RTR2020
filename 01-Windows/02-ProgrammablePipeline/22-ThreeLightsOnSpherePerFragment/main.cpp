#include <Windows.h>
#include <stdio.h>
#include "resource.h"

#include "glew.h"
#include "vmath.h" //C++ namespace (library header)

#include <GL/GL.h>

//macro definitions
#define WIN_WIDTH 800
#define WIN_HIGHT 600

//library inclusion
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")

//for sphere
#include "Sphere.h"
#pragma comment(lib, "Sphere.lib")

using namespace vmath;

enum
{
	ATTRIBUTE_POSITION = 0,
	ATTRIBUTE_COLOR,
	ATTRIBUTE_NORMAL,
	ATTRIBUTE_TEXTURE0
};

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

mat4 gPerspectiveProjectionMatrix;

bool gbLight = false;
bool gbAnimate = false;
bool gbUsePerVertexShader = false;
bool gbUsePerFragmentShader = false;

float sphere_vertices[1146];
float sphere_normals[1146];
float sphere_textures[764];
unsigned short sphere_elements[2280];

GLuint gNumVertices = 0;
GLuint gNumElements = 0;

struct Light
{
	vec4 lightAmbientColor[3];
	vec4 lightDiffuseColor[3];
	vec4 lightSpecularColor[3];
	vec4 lightPositionColor[3];
};

struct Light LightRB;

GLfloat materialAmbient[]  = { 0.0f, 0.0f, 0.0f, 1.0f};
GLfloat materialDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f}; //White
GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f}; //White
GLfloat materialShininess  = 128.0f;

GLfloat angleLight0 = 0.0f;
GLfloat angleLight1 = 0.0f;
GLfloat angleLight2 = 0.0f;

//main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//function declations
	void initialize(void);
	void display(void);
	void uninitialize(void);
	void update(void);

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
	//opening a file
	if(fopen_s(&gpFile, "DebugLog.txt", "w") != 0)
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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance , MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(hInstance , MAKEINTRESOURCE(MYICON));
	wndclass.lpfnWndProc = WndProc;
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
							TEXT("RTR2020-035 | Three Lights On Sphere"),
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
				case VK_ESCAPE:
					ToggleFullscreen();
					break;

				case 'Q':
				case 'q':
					DestroyWindow(hwnd);
					break;

				case 'L':
				case 'l':
					if(gbLight == false)
						gbLight = true; 
					else
						gbLight = false;
					break;

				case 'V':
				case 'v':
					gbUsePerVertexShader = true;
					gbUsePerFragmentShader = false;
					break;
				
				case 'F':
				case 'f':
					gbUsePerVertexShader = false;
					gbUsePerFragmentShader = true;
					break;

				default:
					break;
			}
			break;

		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;

		case WM_QUIT:
			fprintf(gpFile, "DEBUG:WM_QUIT Recieved\n");
			//uninitialize();
			PostQuitMessage(0);
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
	void uninitialize(void);

	//variable declarations
	PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR)};
	int iPixelFormatIndex;
	GLint numExtensions;
	FILE *gpGLExtensionsFile = NULL;

	//code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	if(fopen_s(&gpGLExtensionsFile, "GLExtensions.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("Can Not Open Desired File..."),TEXT("Error"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "DEBUG:GLExtensions File Created Successfully\n");
		fprintf(gpGLExtensionsFile, "DEBUG:GLExtensions File Created Successfully\n");
	}

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

	ghdc = GetDC(ghwnd);

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
		uninitialize();
	}

	if(wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFile, "DEBUG:wgl_MakeContext() Failed\n");
		DestroyWindow(ghwnd);
	}

	GLenum glew_error = glewInit();
	if(glew_error != GLEW_OK)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
		fprintf(gpFile, "DEBUG: glewInit() Failed\n");
		uninitialize();
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

	if(gpGLExtensionsFile)
	{
		fprintf(gpGLExtensionsFile, "DEBUG:GLExtensions File Closed\n");
		fclose(gpGLExtensionsFile);
		gpGLExtensionsFile = NULL;
		fprintf(gpFile, "DEBUG:GLExtensions File Closed\n");
	}

	//vertex shader
	//create shader
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

	" uniform vec4 u_la[3]; \n" \
	" uniform vec4 u_ld[3]; \n" \
	" uniform vec4 u_ls[3]; \n" \
	" uniform vec4 u_light_position[3]; \n" \

	" uniform vec4 u_ka; \n" \
	" uniform vec4 u_kd; \n" \
	" uniform vec4 u_ks; \n" \
	" uniform float u_material_shininess; \n" \

	" out vec3 fong_ads_light; \n" \

	" void main(void) \n" \
	"	{ \n" \
	"		vec3 ambient[3];\n" \
	"		vec3 diffuse[3];\n" \
	"		vec3 specular[3];\n" \
	"		vec3 light_direction[3];\n" \
	"		vec3 reflection_vector[3];\n" \

	"		if(u_LkeyPressed == 1) \n" \
	"			{ \n" \
	"				vec4 eye_coordinates	= u_view_matrix * u_model_matrix * vPosition; \n" \
	"				vec3 tranformed_norm	= normalize( mat3( u_view_matrix * u_model_matrix) * vNormal); \n" \
	"				vec3 view_vector 		= normalize(-eye_coordinates.xyz); \n" \

	"				for(int i = 0; i < 3; i++)\n" \
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


	const GLchar* vertexShaderSourceCodePerFragment =
		" #version 450 core \n" \

		" in vec4 vPosition; \n" \
		" in vec3 vNormal; \n" \

		" uniform mat4 u_model_matrix; \n" \
		" uniform mat4 u_view_matrix; \n" \
		" uniform mat4 u_projection_matrix; \n" \

		" out vec4 out_eye_coordinates; \n" \
		" out vec3 out_tranformed_norm; \n" \

		" void main(void) \n" \
		"	{ \n" \
		"		out_eye_coordinates	= u_model_matrix * u_view_matrix * vPosition; \n" \
		"		out_tranformed_norm	= vec3( mat3( u_view_matrix * u_model_matrix) * vNormal); \n" \

		"		gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition; \n" \
		"	} \n";

	//provide source code shader
	glShaderSource(gVertexShaderObjectPerVertex, 1, (const GLchar**)&vertexShaderSourceCodePerVertex, NULL);
	glShaderSource(gVertexShaderObjectPerFragment, 1, (const GLchar**)&vertexShaderSourceCodePerFragment, NULL);

	//compile shader
	glCompileShader(gVertexShaderObjectPerVertex);
	glCompileShader(gVertexShaderObjectPerFragment);

	GLint iShaderCompileStatus = 0;
	GLint iInfoLogLength = 0;
	char* szInfoLog = NULL;

	glGetShaderiv(gVertexShaderObjectPerVertex, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if(iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(gVertexShaderObjectPerVertex, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if(iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if(szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gVertexShaderObjectPerVertex, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Vertex Shader Compilation Log: %s\n", szInfoLog);
				free(szInfoLog);
				DestroyWindow(ghwnd);
				
			}
		}
	}

	glGetShaderiv(gVertexShaderObjectPerFragment, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if (iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(gVertexShaderObjectPerFragment, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gVertexShaderObjectPerFragment, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Vertex Shader Compilation Log: %s\n", szInfoLog);
				free(szInfoLog);
				DestroyWindow(ghwnd);

			}
		}
	}
	
	//Fragment Shader
	//create Shader
	gFragmentShaderObjectPerVertex = glCreateShader(GL_FRAGMENT_SHADER);
	gFragmentShaderObjectPerFragment = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *gFragmentShaderSourceCodePerVertex =
	" #version 450 core \n" \

	" in vec3 fong_ads_light; \n"\
	" out vec4 FragColor; \n" \

	" void main(void) \n" \
	"	{ \n" \
	"		FragColor = vec4(fong_ads_light, 1.0); \n" \
	" 	} \n";

	
	const GLchar* gFragmentShaderSourceCodePerFragment =
		" #version 450 core \n" \
		" uniform int u_LkeyPressed; \n" \

		" uniform vec4 u_la[3]; \n" \
		" uniform vec4 u_ld[3]; \n" \
		" uniform vec4 u_ls[3]; \n" \
		" uniform vec4 u_light_position[3]; \n" \

		" uniform vec4 u_ka; \n" \
		" uniform vec4 u_kd; \n" \
		" uniform vec4 u_ks; \n" \
		" uniform float u_material_shininess; \n" \

		" in vec4 out_eye_coordinates; \n" \
		" in vec3 out_tranformed_norm; \n" \

		" out vec4 FragColor; \n" \

		" void main(void) \n" \
		"	{ \n" \
		"		vec3 light_direction[3]; \n" \
		"		vec3 normalized_light_direction[3]; \n" \
		"		vec3 reflection_vector[3]; \n" \

		"		vec3 ambient[3]; \n" \
		"		vec3 diffuse[3]; \n" \
		"		vec3 specular[3]; \n" \

		"		vec3 fong_ads_light; \n" \

		"		if(u_LkeyPressed == 1) \n" \
		"			{ \n" \
		"				vec3 view_vector					= (-out_eye_coordinates.xyz); \n" \
		"				vec3 normalized_transformed_norm	= normalize(out_tranformed_norm);\n" \
		"				vec3 normalized_view_vector			= normalize(view_vector);\n" \

		"				for(int i = 0; i < 3; i++) \n" \
		"					{ \n"\
		"						light_direction[i]				= vec3( u_light_position[i] - out_eye_coordinates); \n" \
		"						normalized_light_direction[i]	= normalize(light_direction[i]);\n" \
		"						reflection_vector[i]			= reflect(-normalized_light_direction[i], normalized_transformed_norm); \n" \

		"						ambient[i]	= vec3(u_la[i] * u_ka) ; \n" \
		"						diffuse[i]	= vec3(u_ld[i] * u_kd * max( dot( normalized_light_direction[i], normalized_transformed_norm), 0.0f));\n" \
		"						specular[i]	= vec3(u_ls[i] * u_ks * pow( max( dot( reflection_vector[i], normalized_view_vector), 0.0f), u_material_shininess)); \n" \

		"						fong_ads_light = fong_ads_light + ambient[i] + diffuse[i] + specular[i]; \n" \
		"					} \n" \
		"			} \n" \
		"			else \n" \
		"			{ \n"	 \
		"				fong_ads_light = vec3(1.0f, 1.0f, 1.0f); \n" \
		"			} \n" \
		"		FragColor = vec4(fong_ads_light, 1.0); \n" \
		" } \n";


	//provide source code shader
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
				fprintf(gpFile, "Fragment Shader Compilation Log: %s\n", szInfoLog);
				free(szInfoLog);
				DestroyWindow(ghwnd);
			}
		}
	}

	glGetShaderiv(gFragmentShaderObjectPerFragment, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if (iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(gFragmentShaderObjectPerFragment, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gFragmentShaderObjectPerFragment, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Fragment Shader Compilation Log: %s\n", szInfoLog);
				free(szInfoLog);
				DestroyWindow(ghwnd);
			}
		}
	}

	//shader program
	//create program
	gShaderProgramObjectPerVertex = glCreateProgram();
	gShaderProgramObjectPerFragment = glCreateProgram();

	//attach ahders to shader program
	glAttachShader(gShaderProgramObjectPerVertex, gVertexShaderObjectPerVertex);
	glAttachShader(gShaderProgramObjectPerVertex, gFragmentShaderObjectPerVertex);

	glAttachShader(gShaderProgramObjectPerFragment, gVertexShaderObjectPerFragment);
	glAttachShader(gShaderProgramObjectPerFragment, gFragmentShaderObjectPerFragment);

	glBindAttribLocation(gShaderProgramObjectPerVertex, ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(gShaderProgramObjectPerVertex, ATTRIBUTE_NORMAL, "vNormal");

	glBindAttribLocation(gShaderProgramObjectPerFragment, ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(gShaderProgramObjectPerFragment, ATTRIBUTE_NORMAL, "vNormal");

	//link shader program
	glLinkProgram(gShaderProgramObjectPerVertex);
	glLinkProgram(gShaderProgramObjectPerFragment);

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(gShaderProgramObjectPerVertex, GL_LINK_STATUS, &iShaderProgramLinkStatus);

	if(iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(gShaderProgramObjectPerVertex, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if(iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if(szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(gShaderProgramObjectPerVertex, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Shader Program Link Log: %s\n", szInfoLog);
				free(szInfoLog);
				DestroyWindow(ghwnd);
			}
		}
	}

	glGetProgramiv(gShaderProgramObjectPerFragment, GL_LINK_STATUS, &iShaderProgramLinkStatus);

	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(gShaderProgramObjectPerFragment, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(gShaderProgramObjectPerFragment, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Shader Program Link Log: %s\n", szInfoLog);
				free(szInfoLog);
				DestroyWindow(ghwnd);
			}
		}
	}

	gModelMatrixUniform		= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_model_matrix");
	gViewMatrixUniform		= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_view_matrix");
	gProjectionMatrixUniform = glGetUniformLocation(gShaderProgramObjectPerVertex, "u_projection_matrix");
	gLKeyPressedUniform		= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_LkeyPressed");

	gLightAmbientUniform	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_la");
	gLightDiffuseUniform	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_ld");
	gLightSpecularUniform	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_ls");
	gLightPositionUniform	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_light_position");

	gMaterialAmbientUniform		= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_ka");
	gMaterialDiffuseUniform		= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_kd");
	gMaterialSpecularUniform 	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_ks");
	gMaterialShininessUniform	= glGetUniformLocation(gShaderProgramObjectPerVertex, "u_material_shininess");

	gModelMatrixUniform		= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_model_matrix");
	gViewMatrixUniform		= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_view_matrix");
	gProjectionMatrixUniform = glGetUniformLocation(gShaderProgramObjectPerFragment, "u_projection_matrix");
	gLKeyPressedUniform		= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_LkeyPressed");

	gLightAmbientUniform	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_la");
	gLightDiffuseUniform	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_ld");
	gLightSpecularUniform	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_ls");
	gLightPositionUniform	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_light_position");

	gMaterialAmbientUniform		= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_ka");
	gMaterialDiffuseUniform		= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_kd");
	gMaterialSpecularUniform	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_ks");
	gMaterialShininessUniform	= glGetUniformLocation(gShaderProgramObjectPerFragment, "u_material_shininess");


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
	//Set background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	gPerspectiveProjectionMatrix = mat4::identity();

	//LightSource0
	LightRB.lightAmbientColor[0]  =	vec4( 0.0f, 0.0f, 0.0f, 1.0f);
	LightRB.lightDiffuseColor[0]  =	vec4( 1.0f, 0.0f, 0.0f, 1.0f); //Red
	LightRB.lightSpecularColor[0] =	vec4( 1.0f, 0.0f, 0.0f, 1.0f); //Red
	LightRB.lightPositionColor[0] =	vec4( 0.0f, 0.0f, 0.0f, 1.0f); //

	//LightSource1
	LightRB.lightAmbientColor[1]  =	vec4( 0.0f, 0.0f, 0.0f, 1.0f);
	LightRB.lightDiffuseColor[1]  =	vec4( 0.0f, 1.0f, 0.0f, 1.0f); //
	LightRB.lightSpecularColor[1] =	vec4( 0.0f, 1.0f, 0.0f, 1.0f); //
	LightRB.lightPositionColor[1] =	vec4( 0.0f, 0.0f, 0.0f, 1.0f); //

		//LightSource1
	LightRB.lightAmbientColor[2]  = vec4( 0.0f, 0.0f, 0.0f, 1.0f);
	LightRB.lightDiffuseColor[2]  = vec4( 0.0f, 0.0f, 1.0f, 1.0f); //
	LightRB.lightSpecularColor[2] = vec4( 0.0f, 0.0f, 1.0f, 1.0f); //
	LightRB.lightPositionColor[2] = vec4( 0.0f, 0.0f, 0.0f, 1.0f); //
	//WarmUp resize() Call
	resize(WIN_WIDTH, WIN_HIGHT);
}

void resize(int width, int hight)
{
	//code
	if(hight == 0)
		hight = 1;

	glViewport(0, 0, GLsizei(width), GLsizei(hight));

	gPerspectiveProjectionMatrix = perspective(45.0f, (GLfloat)width/(GLfloat)hight, 0.1f, 100.0f);
}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 modelMatrix;
	mat4 ViewMatrix;
	mat4 translateMatrix;
	mat4 scaleMatrix;
	mat4 rotationMatrix;

	modelMatrix = mat4::identity();
	ViewMatrix = mat4::identity();
	translateMatrix = mat4::identity();
	rotationMatrix = mat4::identity();

	if (gbUsePerVertexShader == true)
	{
		glUseProgram(gShaderProgramObjectPerVertex);
		if (gbLight == true)
		{

			LightRB.lightPositionColor[0] = vec4(0.0f, 2 * sin(angleLight0), 2 * cos(angleLight0), 1.0f); //
			LightRB.lightPositionColor[1] = vec4(2 * sin(angleLight1), 0.0f, 2 * cos(angleLight1), 1.0f); //
			LightRB.lightPositionColor[2] = vec4(2 * sin(angleLight2), 2 * cos(angleLight2), 0.0f, 1.0f); //

			glUniform1i(gLKeyPressedUniform, 1);

			glUniform4fv(gLightAmbientUniform,	3, (GLfloat*)&LightRB.lightAmbientColor);
			glUniform4fv(gLightDiffuseUniform,	3, (GLfloat*)&LightRB.lightDiffuseColor);
			glUniform4fv(gLightSpecularUniform,	3, (GLfloat*)&LightRB.lightSpecularColor);
			glUniform4fv(gLightPositionUniform,	3, (GLfloat*)&LightRB.lightPositionColor);

			glUniform4fv(gMaterialAmbientUniform,	1, (GLfloat*)materialAmbient);
			glUniform4fv(gMaterialDiffuseUniform,	1, (GLfloat*)materialDiffuse);
			glUniform4fv(gMaterialSpecularUniform,	1, (GLfloat*)materialSpecular);
			glUniform1f(gMaterialShininessUniform,	128.0f);
		}
		else
		{
			glUniform1i(gLKeyPressedUniform, 0);
		}

		translateMatrix = translate(0.0f, 0.0f, -2.0f);
		modelMatrix = translateMatrix * rotationMatrix;

		glUniformMatrix4fv(gModelMatrixUniform, 1, GL_FALSE, modelMatrix);
		glUniformMatrix4fv(gViewMatrixUniform, 1, GL_FALSE, ViewMatrix);
		glUniformMatrix4fv(gProjectionMatrixUniform, 1, GL_FALSE, gPerspectiveProjectionMatrix);

		glBindVertexArray(gVao_sphere);

		//draw, either by glDrawTriangles() or glDrawArrays() or glDrawElements()
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gVbo_sphere_element);
		glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

		glBindVertexArray(0);

		glUseProgram(0);
	}

		modelMatrix = mat4::identity();
		ViewMatrix = mat4::identity();
		translateMatrix = mat4::identity();
		rotationMatrix = mat4::identity();

		if (gbUsePerFragmentShader == true)
	{
		glUseProgram(gShaderProgramObjectPerFragment);
		if (gbLight == true)
		{

			LightRB.lightPositionColor[0] = vec4(0.0f, 2 * sin(angleLight0), 2 * cos(angleLight0), 1.0f); //
			LightRB.lightPositionColor[1] = vec4(2 * sin(angleLight1), 0.0f, 2 * cos(angleLight1), 1.0f); //
			LightRB.lightPositionColor[2] = vec4(2 * sin(angleLight2), 2 * cos(angleLight2), 0.0f, 1.0f); //

			glUniform1i(gLKeyPressedUniform, 1);

			glUniform4fv(gLightAmbientUniform,	3, (GLfloat*)&LightRB.lightAmbientColor);
			glUniform4fv(gLightDiffuseUniform,	3, (GLfloat*)&LightRB.lightDiffuseColor);
			glUniform4fv(gLightSpecularUniform,	3, (GLfloat*)&LightRB.lightSpecularColor);
			glUniform4fv(gLightPositionUniform,	3, (GLfloat*)&LightRB.lightPositionColor);

			glUniform4fv(gMaterialAmbientUniform,	1, (GLfloat*)materialAmbient);
			glUniform4fv(gMaterialDiffuseUniform,	1, (GLfloat*)materialDiffuse);
			glUniform4fv(gMaterialSpecularUniform,	1, (GLfloat*)materialSpecular);
			glUniform1f(gMaterialShininessUniform,	128.0f);
		}
		else
		{
			glUniform1i(gLKeyPressedUniform, 0);
		}

		translateMatrix = translate(0.0f, 0.0f, -2.0f);
		modelMatrix = translateMatrix * rotationMatrix;

		glUniformMatrix4fv(gModelMatrixUniform, 1, GL_FALSE, modelMatrix);
		glUniformMatrix4fv(gViewMatrixUniform, 1, GL_FALSE, ViewMatrix);
		glUniformMatrix4fv(gProjectionMatrixUniform, 1, GL_FALSE, gPerspectiveProjectionMatrix);

		glBindVertexArray(gVao_sphere);

		//draw, either by glDrawTriangles() or glDrawArrays() or glDrawElements()
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gVbo_sphere_element);
		glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

		glBindVertexArray(0);

		glUseProgram(0);
	}
	SwapBuffers(ghdc);
}

void update(void)
{
	//code
	if (gbLight == true)
	{
		angleLight0 = angleLight0 + 0.02f;
		angleLight1 = angleLight0 + 0.02f;
		angleLight2 = angleLight0 + 0.02f;

		if (angleLight0 > 360.0f)
			angleLight0 = 0.0f;
		
		if (angleLight1 > 360.0f)
			angleLight1 = 0.0f;

		if (angleLight2 > 360.0f)
			angleLight2 = 0.0f;
	}
}

void uninitialize(void)
{
	//closing file
	if(gbFullscreen == true)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
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

	if(gVao_sphere)
	{
		glDeleteVertexArrays(1, &gVao_sphere);
		gVao_sphere = 0;
	}

	if(gVbo_sphere_position)
	{
		glDeleteBuffers(1, &gVbo_sphere_position);
		gVbo_sphere_position = 0;
	}

	if(gVbo_sphere_normal)
	{
		glDeleteBuffers(1, &gVbo_sphere_normal);
		gVbo_sphere_normal = 0;
	}

	if(gVbo_sphere_element)
	{
		glDeleteBuffers(1, &gVbo_sphere_element);
		gVbo_sphere_element = 0;
	}

	glDetachShader(gShaderProgramObjectPerVertex, gVertexShaderObjectPerVertex);
	glDetachShader(gShaderProgramObjectPerVertex, gFragmentShaderObjectPerVertex);

	glDetachShader(gShaderProgramObjectPerFragment, gVertexShaderObjectPerFragment);
	glDetachShader(gShaderProgramObjectPerFragment, gFragmentShaderObjectPerFragment);

	if(gVertexShaderObjectPerVertex)
	{
		glDeleteShader(gVertexShaderObjectPerVertex);
		gVertexShaderObjectPerVertex = 0;
	}

	if(gFragmentShaderObjectPerVertex)
	{
		glDeleteShader(gFragmentShaderObjectPerVertex);
		gFragmentShaderObjectPerVertex = 0;
	}

	if(gShaderProgramObjectPerVertex)
	{
		glDeleteProgram(gShaderProgramObjectPerVertex);
		gShaderProgramObjectPerVertex = 0;
	}

	glUseProgram(0);

	if (gVertexShaderObjectPerFragment)
	{
		glDeleteShader(gVertexShaderObjectPerFragment);
		gVertexShaderObjectPerFragment = 0;
	}

	if (gFragmentShaderObjectPerFragment)
	{
		glDeleteShader(gFragmentShaderObjectPerFragment);
		gFragmentShaderObjectPerFragment = 0;
	}

	if (gShaderProgramObjectPerFragment)
	{
		glDeleteProgram(gShaderProgramObjectPerFragment);
		gShaderProgramObjectPerFragment = 0;
	}

	glUseProgram(0);

	if(wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	if(ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	if(ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if(gpFile)
	{
		fprintf(gpFile, "DEBUG:Log File Closed\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}

