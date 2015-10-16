package com.rig.project1;

import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RelativeLayout;
import android.widget.TextView;

/**
 * Created by Geo on 9/25/15.
 */
public class HighScore extends AppCompatActivity {

    global gN;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.highscore);

        Button myButton3 = new Button(this);
        myButton3.setId(99);
        myButton3.setText("Go back");

        myButton3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(HighScore.this, UsersInformation.class));
            }
        });


        //this is what we need to get the info form activity one
        gN = (global) getApplication();
        gN.nameArray.add(gN.getName());
        gN.levelArray.add(gN.getLevel());
        gN.ageArray.add(gN.getAge());
        gN.genderArray.add(gN.getGender());




        // gN.levelArray.add(gN.getLevel());


//        pass.setText(gN.getPass());

        //Displays the entire array.
        //Log.d("HighScore", "NAME ARRAY   " + gN.getNameArray(0));

        Log.d("HighScore", "LVL ARRAY   " + gN.nameArray.size());


        Button[] buttons = new Button[10];


        RelativeLayout myLayout = new RelativeLayout(this);



        RelativeLayout.LayoutParams goBackParams =
                new RelativeLayout.LayoutParams(
                        RelativeLayout.LayoutParams.WRAP_CONTENT,
                        RelativeLayout.LayoutParams.WRAP_CONTENT);


        goBackParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
        myLayout.addView(myButton3, goBackParams);


        int prevButtonViewId = 0;

        for (int i = 1; i <= gN.nameArray.size(); i++) {

            buttons[i - 1] = new Button(this);
            buttons[i - 1].setText(gN.getNameArray(i - 1) + "\n" + "Level " + gN.getLevelArray(i - 1));
            //buttons[i - 1].setId(i);

            //new stuff
            int curButtonViewId = prevButtonViewId + 1;
            buttons[i - 1].setId(i);

            final RelativeLayout.LayoutParams params =
                    new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT,
                            RelativeLayout.LayoutParams.WRAP_CONTENT);

            params.addRule(RelativeLayout.BELOW, prevButtonViewId);
            buttons[i-1].setLayoutParams(params);

            prevButtonViewId = curButtonViewId;
            myLayout.addView(buttons[i - 1]);

            buttons[i-1].setOnClickListener(getOnClick(buttons[i-1]));


            //Log.d("HighScore", "NAME ARRAY   " + gN.nameArray);


        }
        setContentView(myLayout);


    }

    View.OnClickListener getOnClick(final Button button){
        return new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(v.getId() == 1){

//                gN.setName(gN.getNameArray(0));
//                gN.setLevel(gN.getLevelArray(0));

                  setGlobal(v);

                }else if (v.getId() == 2){
                    setGlobal(v);

                }else if (v.getId() == 3){
                    setGlobal(v);

                }else if (v.getId() == 4){
                    setGlobal(v);

                }else if (v.getId() == 5){
                    setGlobal(v);

                }else if (v.getId() == 6){
                    setGlobal(v);

                }else if (v.getId() == 7){
                    setGlobal(v);

                }

                Intent intent3 = new Intent(HighScore.this, FinalPage.class);
                startActivity(intent3);

            }


        };
    }

    public void setGlobal (View v){
        gN.setName(gN.getNameArray(v.getId() - 1));
        gN.setLevel(gN.getLevelArray(v.getId() - 1));
        gN.setAge(gN.getAgeArray(v.getId() - 1));
        gN.setGender(gN.getGenderArray(v.getId()-1));
    }


}
