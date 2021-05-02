package com.example.Ortho;

import android.content.Context;

import android.opengl.GLES32;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.EGLConfig;

import android.view.MotionEvent;
import android.view.GestureDetector;
import android.view.GestureDetector.OnGestureListener;
import android.view.GestureDetector.OnDoubleTapListener;

import android.view.Gravity;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import android.opengl.Matrix;

public class GLESOrthoView extends GLSurfaceView implements GLSurfaceView.Renderer, OnGestureListener, OnDoubleTapListener
{
	private final Context context;
	private GestureDetector gestureDetector;

	private int vertexShaderObject;
	private int fragmentShaderObject;
	private int shaderProgramObject;

	private int[] vao = new int[1];
	private int[] vbo = new int[1];

	private int modelViewMatrixUniform;

	private float orthographicProjectionMatrix[] = new float[16];

	public GLESOrthoView(Context drawingContext)
	{
		super(drawingContext);

		context = drawingContext;
		setEGLContextClientVersion(3);
		setRenderer(this);

		setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);

		gestureDetector = new GestureDetector(context, this, null, false);
		gestureDetector.setOnDoubleTapListener(this);
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config)
	{
		//OpenGl-ES version check
		String version = gl.glGetString(GL10.GL_VERSION);
		System.out.println("DEBUG:" + version);

		String glslVersion = gl.glGetString(GLES32.GL_SHADING_LANGUAGE_VERSION);
		System.out.println("DEBUG:" + glslVersion);

		initialize(gl);
	}

	@Override
	public void onSurfaceChanged(GL10 unused, int width, int height)
	{
		resize(width, height);
	}

	@Override
	public void onDrawFrame(GL10 unused)
	{
		display();
	}

	@Override
	public boolean onTouchEvent(MotionEvent event)
	{
		//code
		int eventaction = event.getAction();
		if(!gestureDetector.onTouchEvent(event))
			super.onTouchEvent(event);

		return(true);
	}

	@Override
	public boolean onDoubleTap(MotionEvent e)
	{
		//code
		System.out.println("DEBUG:" + "Double Tap");
		return(true);
	}

	@Override
	public boolean onDoubleTapEvent(MotionEvent e)
	{
		//code
		return(true);
	}

	@Override
	public boolean onSingleTapConfirmed(MotionEvent e)
	{
		//code
		System.out.println("DEBUG:" + "Single Tap");
		return(true);
	}

	@Override
	public boolean onDown(MotionEvent e)
	{
		//code
		return(true);
	}

	@Override
	public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocity)
	{
		//code
		return(true);
	}

	@Override
	public void onLongPress(MotionEvent e)
	{
		//code
		System.out.println("DEBUG:" + "Long Press");
	}

	@Override
	public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY)
	{
		//code
		System.out.println("DEBUG:" + "Scroll");
		uninitialize();
		System.exit(0);
		return(true);
	}

	@Override
	public void onShowPress(MotionEvent e)
	{
		//code
	}

	@Override
	public boolean onSingleTapUp(MotionEvent e)
	{
		//code
		return(true);
	}



	private void initialize(GL10 gl)
	{
		//code
		//vertex shader
		//create vertex shader
		vertexShaderObject = GLES32.glCreateShader(GLES32.GL_VERTEX_SHADER);

		//vertex shader source code
		final String vertexShaderSourceCode = String.format
		(
			" #version 320 es" +
			" \n" +
			" in vec4 vPosition;\n" +
			" uniform mat4 u_mvp_matrix;\n" +
			" \n" +
			" void main(void)\n" +
			" {\n" +
			"	gl_Position = u_mvp_matrix * vPosition;\n" +
			" }\n"
		);

		//provide source code to shader object
		GLES32.glShaderSource(vertexShaderObject, vertexShaderSourceCode);

		//compile shader & check for errors
		GLES32.glCompileShader(vertexShaderObject);

		int[] iShaderCompileStatus = new int[1];
		int[] iInfoLogLength = new int[1];

		String szInfoLog = null;

		GLES32.glGetShaderiv(vertexShaderObject, GLES32.GL_COMPILE_STATUS, iShaderCompileStatus, 0);

		if(iShaderCompileStatus[0] == GLES32.GL_FALSE)
		{
			GLES32.glGetShaderiv(vertexShaderObject, GLES32.GL_INFO_LOG_LENGTH, iInfoLogLength, 0);

			if(iInfoLogLength[0] > 0)
			{
				szInfoLog = GLES32.glGetShaderInfoLog(vertexShaderObject);
				System.out.println("DEBUG: Vertex Shader Compilation log = " + szInfoLog);
				uninitialize();
				System.exit(0);
			}
		}


		//Fragment Shader
		//Create Shader 
		fragmentShaderObject = GLES32.glCreateShader(GLES32.GL_FRAGMENT_SHADER);

		//fragment shader source code
		final String fragmentShaderSourceCode = String.format
		(
			" #version 320 es\n" +
			" \n" +
			" precision highp float;\n" +
			" out vec4 FragColor;\n" +
			" \n" +
			" void main(void)\n" +
			" { \n" +
			"	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n" +
			" }\n"
		);

		//provide source code to shader
		GLES32.glShaderSource(fragmentShaderObject, fragmentShaderSourceCode);

		//Compile shader and check errors
		GLES32.glCompileShader(fragmentShaderObject);

		iShaderCompileStatus[0] = 0;
		iInfoLogLength[0] = 0;
		szInfoLog = null;

		GLES32.glGetShaderiv(fragmentShaderObject, GLES32.GL_COMPILE_STATUS, iShaderCompileStatus, 0);

		if(iShaderCompileStatus[0] == GLES32.GL_FALSE)
		{
			GLES32.glGetShaderiv(fragmentShaderObject, GLES32.GL_INFO_LOG_LENGTH, iInfoLogLength, 0);

			if(iShaderCompileStatus[0] > 0)
			{
				szInfoLog = GLES32.glGetShaderInfoLog(fragmentShaderObject);
				System.out.println("DEBUG: Fragment Shader Compilation Log = " + szInfoLog);
				uninitialize();
				System.exit(0);
			}
		}

		//create shader program
		shaderProgramObject = GLES32.glCreateProgram();

		//attach vertex shader to shader program
		GLES32.glAttachShader(shaderProgramObject, vertexShaderObject);

		//attach Fragment shader to shader program
		GLES32.glAttachShader(shaderProgramObject, fragmentShaderObject);

		//binding of vPosition to shader program object
		GLES32.glBindAttribLocation(shaderProgramObject, GLESMacros.ATTRIBUTE_VERTEX, "vPosition");

		//link two shaders together to shader program object
		GLES32.glLinkProgram(shaderProgramObject);

		int[] iShaderProgramLinkStatus = new int[1];
		iInfoLogLength[0] = 0;
		szInfoLog = null;

		GLES32.glGetProgramiv(shaderProgramObject, GLES32.GL_LINK_STATUS, iShaderProgramLinkStatus, 0);
		if(iShaderProgramLinkStatus[0] == GLES32.GL_FALSE)
		{
			GLES32.glGetProgramiv(shaderProgramObject, GLES32.GL_INFO_LOG_LENGTH, iInfoLogLength, 0);
			if(iInfoLogLength[0] > 0)
			{
				szInfoLog = GLES32.glGetShaderInfoLog(shaderProgramObject);
				System.out.println("DEBUG: Shader Program Link Log =" + szInfoLog);
				uninitialize();
				System.exit(0);
			}
		}

		//uniform locations
		modelViewMatrixUniform = GLES32.glGetUniformLocation(shaderProgramObject, "u_mvp_matrix");

		final float triangleVertices[] = new float[]
		{
			0.0f, 50.0f, 0.0f,
			-50.0f, -50.f, 0.0f,
			50.0f, -50.0f, 0.0f
		};

		GLES32.glGenVertexArrays(1, vao, 0);
		GLES32.glBindVertexArray(vao[0]);

		GLES32.glGenBuffers(1, vbo, 0);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, vbo[0]);
		GLES32.glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		ByteBuffer byteBuffer = ByteBuffer.allocateDirect(triangleVertices.length * 4);
		byteBuffer.order(ByteOrder.nativeOrder());

		FloatBuffer verticesBuffer = byteBuffer.asFloatBuffer();
		verticesBuffer.put(triangleVertices);
		verticesBuffer.position(0);

		GLES32.glBufferData(GLES32.GL_ARRAY_BUFFER, triangleVertices.length * 4, verticesBuffer, GLES32.GL_STATIC_DRAW);

		GLES32.glVertexAttribPointer(GLESMacros.ATTRIBUTE_VERTEX, 3, GLES32.GL_FLOAT, false, 0, 0);
		GLES32.glEnableVertexAttribArray(GLESMacros.ATTRIBUTE_VERTEX);
		GLES32.glBindBuffer(GLES32.GL_ARRAY_BUFFER, 0);
		GLES32.glBindVertexArray(0);

		//enable depth testing
		GLES32.glEnable(GLES32.GL_DEPTH_TEST);

		//depth testing
		GLES32.glDepthFunc(GLES32.GL_LEQUAL);

		//back face culling
		GLES32.glEnable(GLES32.GL_CULL_FACE);

		//set projection matrix
		Matrix.setIdentityM(orthographicProjectionMatrix, 0);

	}

	public void resize(int width, int height)
	{
		GLES32.glViewport(0, 0, width, height);

		if(width <= height)
		{
			Matrix.orthoM(orthographicProjectionMatrix, 0, -100.0f, 100.0f, (-100.0f * (height / width)), (100.0f * (height / width)), -100.0f, 100.0f);
		}
		else
		{
			Matrix.orthoM(orthographicProjectionMatrix, 0, (-100.0f * (width / height)), (100.0f * (width / height)),-100.0f, 100.0f, -100.0f, 100.0f);
		}
	}

	public void display()
	{
		//code
		GLES32.glClear(GLES32.GL_COLOR_BUFFER_BIT | GLES32.GL_DEPTH_BUFFER_BIT);

		//use shader program
		GLES32.glUseProgram(shaderProgramObject);

		//drawing
		float[] modelViewMatrix = new float[16];
		float[] modelViewProjectionMatrix = new float[16];

		//set matrices
		Matrix.setIdentityM(modelViewMatrix, 0);
		Matrix.setIdentityM(modelViewProjectionMatrix, 0);

		//evaluate modelViewProjectionMatrix 
		Matrix.multiplyMM(modelViewProjectionMatrix, 0, orthographicProjectionMatrix, 0, modelViewMatrix, 0);

		//pass matrix to shader
		GLES32.glUniformMatrix4fv(modelViewMatrixUniform, 1, false, modelViewProjectionMatrix, 0);

		//bind vao
		GLES32.glBindVertexArray(vao[0]);

		GLES32.glDrawArrays(GLES32.GL_TRIANGLES, 0, 3);

		GLES32.glUseProgram(0);

		requestRender();
	}

	private void uninitialize()
	{
		//code
		//release vao
		if(vao[0] != 0)
		{
			GLES32.glDeleteVertexArrays(1, vao, 0);
			vao[0] = 0;
		}

		//release vao
		if(vbo[0] != 0)
		{
			GLES32.glDeleteBuffers(1, vbo, 0);
			vbo[0] = 0;
		}

		//release shaders
		if(shaderProgramObject != 0)
		{
			if(vertexShaderObject != 0)
			{
				GLES32.glDetachShader(shaderProgramObject, vertexShaderObject);
				GLES32.glDeleteShader(vertexShaderObject);
				vertexShaderObject = 0;
			}

			if(fragmentShaderObject != 0)
			{
				GLES32.glDetachShader(shaderProgramObject, fragmentShaderObject);
				GLES32.glDeleteShader(fragmentShaderObject);
				fragmentShaderObject = 0;
			}

			if(shaderProgramObject != 0)
			{
				GLES32.glDeleteProgram(shaderProgramObject);
				shaderProgramObject = 0;
			}
		}
	}
}







