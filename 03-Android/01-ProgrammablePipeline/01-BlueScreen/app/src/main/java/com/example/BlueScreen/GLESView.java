package com.example.BlueScreen;

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

public class GLESView extends GLSurfaceView implements GLSurfaceView.Renderer, OnGestureListener, OnDoubleTapListener
{
	private GestureDetector gestureDetector;
	private final Context context;

	public GLESView(Context drawingContext)
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
		draw();
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
		GLES32.glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	}

	public void resize(int width, int height)
	{
		GLES32.glViewport(0, 0, width, height);
	}

	public void draw()
	{
		GLES32.glClear(GLES32.GL_COLOR_BUFFER_BIT | GLES32.GL_DEPTH_BUFFER_BIT);
	}
}







