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

GLuint gVertexShaderObject;
GLuint gFragmentShaderObject;
GLuint gShaderProgramObject;

GLuint gVao_sphere;
GLuint gVbo_sphere_position;
GLuint gVbo_sphere_normal;
GLuint gVbo_sphere_element;

GLuint gModelMatrixUniform;
GLuint gViewMatrixUniform;
GLuint gPerspectiveProjectionMatrixUniform;

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

bool gbAnimate = false;
bool gbLight = false;


float sphere_vertices[1146];
float sphere_normals[1146];
float sphere_textures[764];
unsigned short sphere_elements[2280];

GLuint gNumVertices = 0;
GLuint gNumElements = 0;

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
							TEXT("PerVertexPreFragmentToggle:Akshay"),
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
						gbLight = true; 
					else
						gbLight = false;
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
	gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCode = 
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

	//provide source code shader
	glShaderSource(gVertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

	//compile shader
	fprintf(gpFile, "DEBUG:compiling shader vertex shader\n");
	glCompileShader(gVertexShaderObject);

	GLint iShaderCompileStatus = 0;
	GLint iInfoLogLength = 0;
	char* szInfoLog = NULL;

	glGetShaderiv(gVertexShaderObject, GL_COMPILE_STATUS, &iShaderCompileStatus);
	if(iShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(gVertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if(iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if(szInfoLog != NULL)
			{
				GLsizei written;
				glGetShaderInfoLog(gVertexShaderObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Vertex Shader Compilation Log: %s\n", szInfoLog);
				free(szInfoLog);
				DestroyWindow(ghwnd);
			}
		}
	}
	fprintf(gpFile, "DEBUG:Vertex Shader Compilation Done\n");

	//Fragment Shader
	//create Shader
	fprintf(gpFile, "DEBUG:Fragment Shader\n");
	fprintf(gpFile, "DEBUG:Creating Fragment Shader\n");
	gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *gFragmentShaderSourceCode =
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

	//provide source code shader
	glShaderSource(gFragmentShaderObject, 1, (const GLchar **) &gFragmentShaderSourceCode, NULL);

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
				fprintf(gpFile, "Fragment Shader Compilation Log: %s\n", szInfoLog);
				free(szInfoLog);
				DestroyWindow(ghwnd);
			}
		}
	}

	//shader program
	//create program
	gShaderProgramObject = glCreateProgram();

	//attach ahders to shader program
	glAttachShader(gShaderProgramObject, gVertexShaderObject);
	glAttachShader(gShaderProgramObject, gFragmentShaderObject);

	glBindAttribLocation(gShaderProgramObject, ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(gShaderProgramObject, ATTRIBUTE_NORMAL, "vNormal");

	//link shader program
	glLinkProgram(gShaderProgramObject);

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);

	if(iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if(iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);
			if(szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpFile, "Shader Program Link Log: %s\n", szInfoLog);
				free(szInfoLog);
				DestroyWindow(ghwnd);
			}
		}
	}

	gModelMatrixUniform	= glGetUniformLocation(gShaderProgramObject, "u_model_matrix");
	gViewMatrixUniform	= glGetUniformLocation(gShaderProgramObject, "u_view_matrix");
	gPerspectiveProjectionMatrixUniform = glGetUniformLocation(gShaderProgramObject, "u_projection_matrix");
	gLKeyPressedUniform	= glGetUniformLocation(gShaderProgramObject, "u_LkeyPressed");

	gLightAmbientUniform	= glGetUniformLocation(gShaderProgramObject, "u_la");
	gLightDiffuseUniform	= glGetUniformLocation(gShaderProgramObject, "u_ld");
	gLightSpecularUniform	= glGetUniformLocation(gShaderProgramObject, "u_ls");
	gLightPositionUniform	= glGetUniformLocation(gShaderProgramObject, "u_light_position");

	gMaterialAmbientUniform	= glGetUniformLocation(gShaderProgramObject, "u_ka");
	gMaterialDiffuseUniform	= glGetUniformLocation(gShaderProgramObject, "u_kd");
	gMaterialSpecularUniform 	= glGetUniformLocation(gShaderProgramObject, "u_ks");
	gMaterialShininessUniform	= glGetUniformLocation(gShaderProgramObject, "u_material_shininess");

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

	fprintf(gpFile, "DEBUG:Binding VBOs Done\n");

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

	//WarmUp resize() Call
	resize(WIN_WIDTH, WIN_HIGHT);

	fprintf(gpFile, "DEBUG:Initialization Done\n");
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

	glUseProgram(gShaderProgramObject);

	mat4 modelMatrix;
	mat4 ViewMatrix;
	mat4 translateMatrix;
	mat4 scaleMatrix;
	mat4 rotationMatrix;
	mat4 modelViewProjectionMatrix;

	modelMatrix			= mat4::identity();
	ViewMatrix			= mat4::identity();
	translateMatrix		= mat4::identity();
	rotationMatrix		= mat4::identity();

	if(gbLight == true)
	{
		GLfloat lightAmbient[]	= {	0.0f,	0.0f,	0.0f,	1.0f};
		GLfloat lightDiffuse[]	= {	1.0f,	1.0f,	1.0f,	1.0f};//white
		GLfloat lightSpecular[]	= {	1.0f,	1.0f,	1.0f,	1.0f};//white
		GLfloat lightPosition[]	= {	100.0f,	100.0f,	100.0f,	1.0f};//light position

		GLfloat materialAmbient[]	= { 0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat materialDiffuse[]	= { 1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat materialSpecular[]	= { 1.0f, 1.0f, 1.0f, 1.0f};

		glUniform1i(gLKeyPressedUniform, 1);

		glUniform4fv(gLightAmbientUniform,	1, (GLfloat *)lightPosition);
		glUniform4fv(gLightDiffuseUniform,	1, (GLfloat *)lightDiffuse);
		glUniform4fv(gLightSpecularUniform,	1, (GLfloat *)lightSpecular);
		glUniform4fv(gLightPositionUniform, 1, (GLfloat *)lightPosition);

		glUniform4fv(gMaterialAmbientUniform, 	1, (GLfloat *)materialAmbient);
		glUniform4fv(gMaterialDiffuseUniform,	1, (GLfloat *)materialDiffuse);
		glUniform4fv(gMaterialSpecularUniform,	1, (GLfloat *)materialSpecular);
		glUniform1f(gMaterialShininessUniform, 128.0f);
	}
	else
	{
		glUniform1i(gLKeyPressedUniform, 0);
	}

	translateMatrix = translate(0.0f, 0.0f , -3.0f);
	modelMatrix =  translateMatrix;

	glUniformMatrix4fv(gModelMatrixUniform, 1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(gViewMatrixUniform,   1, GL_FALSE, ViewMatrix);
	glUniformMatrix4fv(gPerspectiveProjectionMatrixUniform, 1, GL_FALSE, gPerspectiveProjectionMatrix);

	glBindVertexArray(gVao_sphere);

	//draw, either by glDrawTriangles() or glDrawArrays() or glDrawElements()
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gVbo_sphere_element);
	glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);

	glUseProgram(0);

	SwapBuffers(ghdc);
}

void update(void)
{
	//code
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

