package com.rig.project1;

import android.content.Intent;
import android.graphics.Point;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.Menu;
import android.view.MenuItem;

import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

import android.os.Handler;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.content.Context;

public class MainActivity extends AppCompatActivity {


    private int hits = 0; // number of spots hit
    private int misses = 0; // current misses
    private TextView hitsTextView; // displays high score
    private TextView missesTextView; // displays current score
    private ImageView moleImage;
    private ImageView topmissingImage;
    private ImageView bottommissingImage;
    private ProgressBar progressBar;
    private int progressStatus = 0;
    private int progessIntMax = 10;
    private TextView tvLevel;
    private int lvl = 1;

    private int moleSpeed = 2000;

    Random rX = new Random();
    Random rY = new Random();


    Timer moveMole = new Timer();
    TimerTask moleTask = new MoleTimerTask(MainActivity.this);

    int screenWidth = 0;
    int screenHeight = 0;


    private Handler mHandler = new Handler();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //get the with and size of the screen
        Display display = getWindowManager().getDefaultDisplay();
        Point size = new Point();
        display.getSize(size);
        screenWidth = size.x;
        screenHeight = size.y;


        global gN = (global)getApplication();
        if(gN.isHardMode() == true){
            moleSpeed -= 350;
        }
        else
            moleSpeed = 2000;




        Button resetButton = (Button) findViewById(R.id.button1);
        resetButton.setOnClickListener(resetListener);

        hitsTextView = (TextView) findViewById(R.id.highScoreTextView);
        missesTextView = (TextView) findViewById(R.id.scoreTextView);


        moleImage = (ImageView) findViewById(R.id.themole);
        moleImage.setOnClickListener(moleListener);
        moleImage.bringToFront();
        resetButton.bringToFront();


        moveMole.scheduleAtFixedRate(moleTask, 0, moleSpeed);


        topmissingImage = (ImageView) findViewById(R.id.topmissingView);
        topmissingImage.setOnClickListener(topmissListener);
        topmissingImage.setAlpha(0);

        bottommissingImage = (ImageView) findViewById(R.id.bottommissingView);
        bottommissingImage.setOnClickListener(bottommissListener);
        bottommissingImage.setAlpha(0);

        progressBar = (ProgressBar) findViewById(R.id.pBar);
        progressBar.setMax(progessIntMax);
        //progressBar.s

        tvLevel = (TextView) findViewById(R.id.tvLevel);
        tvLevel.setText("LEVEL " + lvl);


    }

    public void backActivity(View view) {
        Intent intent = new Intent(this, UsersInformation.class);
        startActivity(intent);

    }

    public void finishGame(View view) {


        global gN = (global) getApplication();
        gN.setLevel(lvl);
        Intent intent2 = new Intent(this, HighScore.class);
        //finish();
        startActivity(intent2);

    }


    public class MoleTimerTask extends TimerTask {

        private Context context;

        // Write Custom Constructor to pass Context
        public MoleTimerTask(Context con) {
            this.context = con;
        }

        public void run() {

            new Thread(new Runnable() {
                @Override
                public void run() {

                    mHandler.post(new Runnable() {
                        @Override
                        public void run() {

                            moleImage.setX(rX.nextInt(screenWidth));
                            moleImage.setY(rY.nextInt(screenHeight));


                        }
                    });
                }

            }).start();

        }

    }

    private OnClickListener topmissListener = new OnClickListener() {
        public void onClick(View v) {
            misses++;
            //stop the progress bar from going negative
            if (progressStatus < 0) {
                progressStatus = 0;
            }
            progressStatus--;
            progressBar.setProgress(progressStatus);
            displayScores();


        }
    };

    private OnClickListener bottommissListener = new OnClickListener() {
        public void onClick(View v) {
            misses++;
            //stop the progress bar from going negative
            if (progressStatus < 0) {
                progressStatus = 0;
            }
            progressStatus--;
            progressBar.setProgress(progressStatus);
            displayScores();


        }
    };


    private OnClickListener moleListener = new OnClickListener() {
        public void onClick(View v) {

            hits++;
            NextLevel();
            progressStatus++;
            progressBar.setProgress(progressStatus);
            displayScores();


        }
    };

    private void NextLevel() {
        if (progressStatus == progressBar.getMax()) {

            progressStatus = 0;
            progressBar.setProgress(progressStatus);

            progessIntMax = progessIntMax + 10;
            progressBar.setMax(progessIntMax);
            lvl = lvl + 1;
            tvLevel.setText("LEVEL " + lvl);


            Log.d("MainActivity", "setProgress " + progressBar.getMax());

        }
    }


    private OnClickListener resetListener = new OnClickListener() {
        public void onClick(View v) {

            progressBar.setProgress(0);

            hits = 0;
            misses = 0;
            progressStatus = 0;
            progressBar.setProgress(progressStatus);
            progessIntMax = 10;
            progressBar.setMax(progessIntMax);
            lvl = 1;
            tvLevel.setText("LEVEL " + lvl);
            displayScores();
        }
    };


    private void displayScores() {
        // display the high score, current score and level
        hitsTextView.setText(
                getString(R.string.hit_score) + " " + hits);
        missesTextView.setText(
                getString(R.string.misses) + " " + misses);
    } // end function displayScores



}