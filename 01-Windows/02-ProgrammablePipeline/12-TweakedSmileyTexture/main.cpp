#include <Windows.h>
#include <stdio.h>
#include <math.h>
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

GLuint gVaoQuad;
GLuint gVboQuad;
GLuint gVboQuadColor;
GLuint gVboQuadTexture;

GLuint pressedDigit = 0;

GLuint gMVPU;
GLuint gTextureUniformSampler;
GLuint gTKeyPressedUniform;
mat4 gPerspectiveProjectionMatrix;

bool gbTexture = false;

GLuint SmileyTexture;

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
							TEXT("TweakedSmileyTexture:Akshay"),
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

				case 49:
				case VK_NUMPAD1:
					pressedDigit = 1;
					gbTexture = true;
					break;

				case 50:
				case VK_NUMPAD2:
					pressedDigit = 2;
					gbTexture = true;
					break;

				case 51:
				case VK_NUMPAD3:
					pressedDigit = 3;
					gbTexture = true;
					break;

				case 52:
				case VK_NUMPAD4:
					pressedDigit = 4;
					gbTexture = true;
					break;

				default:
					pressedDigit = 5;
					gbTexture = false;
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
	bool LoadGLTexture(GLuint *texture, TCHAR resourceID[]);

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
	" #version 450 core \n"									\
	" \n" 													\
	" in vec4 vPosition; \n" 								\
	" in vec2 vTextCoords; \n" 								\
	" uniform mat4 u_mvp_matrix; \n" 						\
	" out vec2 out_text_coords; \n" 						\
	" void main(void) \n" 									\
	" 	{ \n" 												\
	" 		gl_Position = u_mvp_matrix * vPosition; \n" 	\
	" 		out_text_coords = vTextCoords; \n" 				\
	" 	} \n";

	//provide source code shader
	glShaderSource(gVertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);

	//compile shader
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

	//Fragment Shader
	//create Shader
	gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *gFragmentShaderSourceCode =
	" #version 450 core \n" 					\
	" \n" 										\
	" out vec4 FragColor; \n" 					\
	" uniform sampler2D u_texture_sampler; \n"	\
	" in vec2 out_text_coords; \n" 				\
	" uniform int u_texture;"					\
	" void main(void) \n" 						\
	" { \n"										\
	"	if(u_texture == 1)\n"					\
	"		FragColor = (texture(u_texture_sampler, out_text_coords)); \n" \
	"	else \n"								\
	"		FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); \n" \
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
	glBindAttribLocation(gShaderProgramObject, ATTRIBUTE_TEXTURE0, "vTextCoords");

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

	gMVPU = glGetUniformLocation(gShaderProgramObject, "u_mvp_matrix");
	gTKeyPressedUniform = glGetUniformLocation(gShaderProgramObject, "u_texture");
	gTextureUniformSampler = glGetUniformLocation(gShaderProgramObject, "u_texture_sampler");

	const GLfloat QuadVertices[] = 
	{
		-1.0f,	 1.0f,	0.0f,
		 1.0f,	 1.0f,	0.0f,
		 1.0f,	-1.0f,	0.0f,
		-1.0f,	-1.0f,	0.0f
	};

	glGenVertexArrays(1, &gVaoQuad);
	glBindVertexArray(gVaoQuad);

	glGenBuffers(1, &gVboQuad);
	glBindBuffer(GL_ARRAY_BUFFER, gVboQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertices), QuadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVboQuadTexture);
	glBindBuffer(GL_ARRAY_BUFFER, gVboQuadTexture);
	glBufferData(GL_ARRAY_BUFFER, (4 * 2 * (sizeof(GLfloat))), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ATTRIBUTE_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

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

	glEnable(GL_TEXTURE_2D);

	LoadGLTexture(&SmileyTexture, MAKEINTRESOURCE(SMILEY_BITMAP));

	//WarmUp resize() Call
	resize(WIN_WIDTH, WIN_HIGHT);
}

bool LoadGLTexture(GLuint *texture, TCHAR resourceID[])
{
	//variable declarations
	bool bResult = false;
	HBITMAP hBitmap = NULL;
	BITMAP bmp;

	//code
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), resourceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if(hBitmap)
	{
		bResult = true;
		GetObject(hBitmap, sizeof(BITMAP), &bmp);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.bmWidth, bmp.bmHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, bmp.bmBits);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	return bResult;
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
	GLfloat QuadTextCoords[8];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(gShaderProgramObject);

	mat4 modelViewMatrix;
	mat4 translateMatrix;
	mat4 scaleMatrix;
	mat4 rotationMatrix;
	mat4 modelViewProjectionMatrix;

	modelViewMatrix = mat4::identity();
	translateMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	modelViewProjectionMatrix = mat4::identity();

	if(gbTexture == true)
		glUniform1i(gTKeyPressedUniform, 1);
	else
		glUniform1i(gTKeyPressedUniform, 0);

	translateMatrix = translate(0.0f, 0.0f , -8.0f);
	modelViewMatrix = translateMatrix * rotationMatrix;

	modelViewProjectionMatrix = gPerspectiveProjectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(gMVPU, 1, GL_FALSE, modelViewProjectionMatrix);

	if(pressedDigit == 1)
	{
		QuadTextCoords[0] = 0.0f;
		QuadTextCoords[1] = 1.0f;
		QuadTextCoords[2] = 1.0f;
		QuadTextCoords[3] = 1.0f;
		QuadTextCoords[4] = 1.0f;
		QuadTextCoords[5] = 0.0f;
		QuadTextCoords[6] = 0.0f;
		QuadTextCoords[7] = 0.0f;
	}
	else if(pressedDigit == 2)
	{
		QuadTextCoords[0] = 0.0f;
		QuadTextCoords[1] = 0.5f;
		QuadTextCoords[2] = 0.5f;
		QuadTextCoords[3] = 0.5f;
		QuadTextCoords[4] = 0.5f;
		QuadTextCoords[5] = 0.0f;
		QuadTextCoords[6] = 0.0f;
		QuadTextCoords[7] = 0.0f;
	}
	else if(pressedDigit == 3)
	{
		QuadTextCoords[0] = 0.0f;
		QuadTextCoords[1] = 2.0f;
		QuadTextCoords[2] = 2.0f;
		QuadTextCoords[3] = 2.0f;
		QuadTextCoords[4] = 2.0f;
		QuadTextCoords[5] = 0.0f;
		QuadTextCoords[6] = 0.0f;
		QuadTextCoords[7] = 0.0f;
	}
	else if(pressedDigit == 4)
	{
		QuadTextCoords[0] =  0.5f;
		QuadTextCoords[1] =  0.5f;
		QuadTextCoords[2] =  0.5f;
		QuadTextCoords[3] =  0.5f;
		QuadTextCoords[4] =  0.5f;
		QuadTextCoords[5] =  0.5f;
		QuadTextCoords[6] =  0.5f;
		QuadTextCoords[7] =  0.5f;
	}

	glBindBuffer(GL_ARRAY_BUFFER, gVboQuadTexture);
	glBufferData(GL_ARRAY_BUFFER, (4 * 2 * (sizeof(GLfloat))), QuadTextCoords, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ATTRIBUTE_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, SmileyTexture);
	glUniform1i(gTextureUniformSampler, 0);

	glBindVertexArray(gVaoQuad);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
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

	if(gVaoQuad)
	{
		glDeleteVertexArrays(1, &gVaoQuad);
		gVaoQuad = 0;
	}

	if(gVboQuad)
	{
		glDeleteBuffers(1, &gVboQuad);
		gVboQuad = 0;
	}

	if(gVboQuadTexture)
	{
		glDeleteBuffers(1, &gVboQuadTexture);
		gVboQuadTexture = 0;
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

