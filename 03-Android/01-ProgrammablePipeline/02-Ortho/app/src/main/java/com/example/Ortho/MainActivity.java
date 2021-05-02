package com.example.Ortho;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;

import android.content.pm.ActivityInfo;
import android.view.View;

public class MainActivity extends AppCompatActivity
{
	private GLESOrthoView glesOrthoView;

	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{

		getWindow().getDecorView().setSystemUiVisibility
		(
			View.SYSTEM_UI_FLAG_IMMERSIVE |
			View.SYSTEM_UI_FLAG_LAYOUT_STABLE |
			View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION |
			View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN |
			View.SYSTEM_UI_FLAG_HIDE_NAVIGATION |
			View.SYSTEM_UI_FLAG_FULLSCREEN
		);

		super.onCreate(savedInstanceState);

		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);

		GLESOrthoView glesOrthoView = new GLESOrthoView(this);
//		AppCompatTextView myTextView = new AppCompatTextView(this);

		//setContentView(R.layout.activity_main);
		setContentView(glesOrthoView);

	}
}