#include <GL\freeglut.h>
#include <math.h>
#include <stdio.h>

bool bFullscreen=false;

void main(int argc, char **argv)
{
	//code
	//Function Declarations
	void initialize(void);
	void display(void);
	void resize(int , int );
	void keyboard(unsigned char , int , int );
	void mouse(int , int , int , int );
	void uninitialize(void);

	//Function Calls
	 glutInit(&argc, argv);							//initialization
	 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);	//DisplayMode
	 glutInitWindowSize(800, 600);					//Window Size
	 glutInitWindowPosition(100, 100);				//Window Position
	 glutCreateWindow("GLUT: Akshay Chandawale");	//Create Window with title

	 initialize();

	 glutDisplayFunc(display);
	 glutReshapeFunc(resize);
	 glutKeyboardFunc(keyboard);
	 glutMouseFunc(mouse);
	 glutCloseFunc(uninitialize);

	 glutMainLoop();								//glutmainloop gameloop 

	// return (0);
	 
}


void initialize(void)
{
	//code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

float x=0.0f,y =0.0f;
void display(void)
{
	float i=0;
	
	//code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		//x=x+1.25f;
		//y=y+1.50f;
		
		//drawing triangle with the help of three vertices
		glBegin(GL_TRIANGLES);
		
			for(i=0; i<6.5;i=i+0.01f )
			{
			glColor3f(1.0f, 0.0f, 0.0f); //red 
			glVertex3f(0.0f, 0.0f, 0.0f);//p(-1,1)

			glColor3f(1.0f, 1.0f, 0.0f);//green
			glVertex3f( (float(cos(i+0.0f))), (float(sin(i+0.0f))), 0.0f);//q(-1,-1)

			glColor3f(1.0f, 1.0f, 0.0f);//blue
			glVertex3f((float(cos(i+0.01f))), (float(sin(i+0.01f))), 0.0f);//q(-1,-1)
			printf("\n%.2f",&i);
			}
			
		glEnd();
	
	glFlush();

}

void resize(int width, int height)
{
	//code
	if(height <= 0)
		height=1;
	glViewport(0, 0, GLsizei(width), GLsizei(height));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	//code
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		break;

	case 'f':
	case 'F':
		if(bFullscreen == false)
		{
			glutLeaveFullScreen();
			bFullscreen=true;
		}
		else
		{
			glutFullScreen();
			bFullscreen=false;
		}
		break;

	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	//code
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		break;

	case GLUT_RIGHT_BUTTON:
		glutLeaveMainLoop();
		break;

	default:
		break;
	}
}

void uninitialize(void)
{
	//code
}
