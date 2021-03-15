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

GLuint gVaoPyramid;
GLuint gVboPyramid;
GLuint gVboPpyramidCcolor;

GLuint gVaoCube;
GLuint gVboCube;
GLuint gVboCubeColor;

GLuint gMVPU;

mat4 gPerspectiveProjectionMatrix;

GLfloat anglePyramid = 0.0f;
GLfloat angleCube = 0.0f;

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
							TEXT("MyBlueScreenWindow:Akshay"),
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

	//code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

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

	fprintf(gpFile, "OpenGL Vendor  :%s\n", glGetString(GL_VENDOR));
	fprintf(gpFile, "OpenGL Renderer:%s\n", glGetString(GL_RENDERER));
	fprintf(gpFile, "OpenGL Version :%s\n", glGetString(GL_VERSION));
	fprintf(gpFile, "OpenGL Shading Language (GLSL) Version:%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glGetIntegerv (GL_NUM_EXTENSIONS, &numExtensions);

	for(int i = 0; i < numExtensions; i++)
	{
		fprintf(gpFile, "%s\n", glGetStringi(GL_EXTENSIONS, i));
	}

	//vertex shader
	//create shader
	gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar *vertexShaderSourceCode = 
	"#version 450 core \n" \
	"\n" \
	"in vec4 vPosition; \n" \
	"in vec4 vColor; \n" \
	"uniform mat4 u_mvp_matrix; \n" \
	"out vec4 out_color; \n" \
	"void main(void) \n" \
	"{ \n" \
	"gl_Position = u_mvp_matrix * vPosition; \n" \
	"out_color = vColor; \n" \
	"} \n";

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
	"#version 450 core \n" \
	"\n" \
	"out vec4 FragColor; \n" \
	"in vec4 out_color; \n" \
	"void main(void) \n" \
	"{ \n" \
	"FragColor = out_color; \n" \
	"} \n";

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
	glBindAttribLocation(gShaderProgramObject, ATTRIBUTE_COLOR, "vColor");

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

	const GLfloat pyramidColors[] = 
	{
		 1.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 1.0f,
		 1.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 1.0f,
		 1.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 1.0f,
		 1.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 1.0f,
	};

	const GLfloat cubeVertices[] = 
	{
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f
	};

	const GLfloat cubeColors[] = 
	{
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, &gVaoPyramid);
	glBindVertexArray(gVaoPyramid);

	glGenBuffers(1, &gVboPyramid);
	glBindBuffer(GL_ARRAY_BUFFER, gVboPyramid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVboPpyramidCcolor);
	glBindBuffer(GL_ARRAY_BUFFER, gVboPpyramidCcolor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidColors), pyramidColors, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ATTRIBUTE_COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glGenVertexArrays(1, &gVaoCube);
	glBindVertexArray(gVaoCube);

	glGenBuffers(1, &gVboCube);
	glBindBuffer(GL_ARRAY_BUFFER, gVboCube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &gVboCubeColor);
	glBindBuffer(GL_ARRAY_BUFFER, gVboCubeColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
	glVertexAttribPointer(ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ATTRIBUTE_COLOR);
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

	translateMatrix = translate(-2.0f, 0.0f , -8.0f);
	rotationMatrix = rotate(anglePyramid, 0.0f, 1.0f, 0.0f);
	modelViewMatrix = translateMatrix * rotationMatrix;

	modelViewProjectionMatrix = gPerspectiveProjectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(gMVPU, 1, GL_FALSE, modelViewProjectionMatrix);

	glBindVertexArray(gVaoPyramid);

	glDrawArrays(GL_TRIANGLES, 0, 12);

	glBindVertexArray(0);

	modelViewMatrix = mat4::identity();
	translateMatrix = mat4::identity();
	scaleMatrix = mat4::identity();
	rotationMatrix = mat4::identity();
	modelViewProjectionMatrix = mat4::identity();

	translateMatrix = translate(2.0f, 0.0f , -8.0f);
	scaleMatrix = scale(0.75f, 0.75f, 0.75f);
	rotationMatrix = rotate(angleCube, 1.0f, 0.0f, 0.0f);
	rotationMatrix = rotationMatrix * rotate(angleCube, 0.0f, 1.0f, 0.0f);
	rotationMatrix = rotationMatrix * rotate(angleCube, 0.0f, 0.0f, 1.0f);

	modelViewMatrix = translateMatrix * scaleMatrix * rotationMatrix;

	modelViewProjectionMatrix = gPerspectiveProjectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(gMVPU, 1, GL_FALSE, modelViewProjectionMatrix);

	glBindVertexArray(gVaoCube);

	glDrawArrays(GL_TRIANGLE_FAN,  0, 4);
	glDrawArrays(GL_TRIANGLE_FAN,  4, 4);
	glDrawArrays(GL_TRIANGLE_FAN,  8, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glBindVertexArray(0);

	glUseProgram(0);

	SwapBuffers(ghdc);
}

void update(void)
{
	//code
	anglePyramid = anglePyramid + 1.0f;
	if(anglePyramid > 360.0f)
		anglePyramid = 0.0f;

	angleCube = angleCube + 1.0f;
	if(angleCube > 360.0f)
		angleCube = 0.0f;
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

	if(gVboPpyramidCcolor)
	{
		glDeleteBuffers(1, &gVboPpyramidCcolor);
		gVboPpyramidCcolor = 0;
	}

	if(gVaoCube)
	{
		glDeleteVertexArrays(1, &gVaoCube);
		gVaoCube = 0;
	}

	if(gVboCubeColor)
	{
		glDeleteBuffers(1, &gVboCubeColor);
		gVboCubeColor = 0;
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
		fprintf(gpFile, "DEBUG:File Closed\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}

