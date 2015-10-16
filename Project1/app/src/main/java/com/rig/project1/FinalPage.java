package com.rig.project1;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

/**
 * Created by Geo on 9/30/15.
 */
public class FinalPage extends AppCompatActivity {

//    TextView tvText;
//    ClassDB db;

    LinearLayout l;
    int rows;
    ClassDB db;


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.final_page);
//
//        tvText = (TextView) findViewById(R.id.usersInfo);
//
//        db = new ClassDB(this, null, null, 1);
//        String data = db.databaseToString();
//        tvText.setText(data);


        l = (LinearLayout) findViewById(R.id.l);
        db = new ClassDB(this, null, null, 1);
        rows = db.numRows();
        if (rows >= 10) {
            rows = 10;
        }
        for (int i = 0; i <= rows - 1; i++) {
            String rowData = db.getRowUserData(i);
            Button newButton = new Button(this);
            newButton.setId(i + 1);
            newButton.setText(rowData);
            newButton.setOnClickListener(btnclick);
            newButton.setLayoutParams(new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
                    ViewGroup.LayoutParams.WRAP_CONTENT));
            l.addView(newButton);
        }



    }


    View.OnClickListener btnclick = new View.OnClickListener() {

        @Override
        public void onClick(View view) {

            switch(view.getId()){
                case 1:
                    l.setBackgroundColor(Color.BLUE);
                    break;
                //Second button click
                case 2:
                    l.setBackgroundColor(Color.RED);
                    break;
                case 3:
                    //third button click
                    break;
                case 4:
                    //fourth button click
                    break;

                default:
                    break;
            }

        }
    };


//    public void goBackToStart(View view) {
//        Intent intent = new Intent(this, UsersInformation.class);
//        startActivity(intent);
//    }
}
