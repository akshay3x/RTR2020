package com.example.HelloWorld;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import androidx.appcompat.widget.AppCompatTextView;

import android.content.pm.ActivityInfo;
import android.graphics.Color;
import android.view.Gravity;

import android.view.View;


public class MainActivity extends AppCompatActivity
{

	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{

		super.onCreate(savedInstanceState);

		AppCompatTextView myTextView = new AppCompatTextView(this);
		getWindow().getDecorView().setBackgroundColor(Color.rgb(0, 0, 0));
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);



		myTextView.setText("Hello World!!!");
		myTextView.setTextSize(60);
		myTextView.setTextColor(Color.rgb(0, 255, 0));
		myTextView.setBackgroundColor(Color.rgb(0, 0, 0));
		myTextView.setGravity(Gravity.CENTER);

		//setContentView(R.layout.activity_main);
		setContentView(myTextView);

	}
}