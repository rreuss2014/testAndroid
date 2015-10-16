package com.rig.project1;

import android.content.Intent;
import android.os.Bundle;
import android.os.Parcelable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

/**
 * Created by Geo on 9/25/15.
 */
public class UsersInformation extends AppCompatActivity {

    Button submit;
    EditText name, pass, _id;

    TextView age, tv;
    SeekBar seek;
    public int current = 0;
    String s = null;
    private Switch mySwitch;
    boolean hardMode = false;
    String gender = " ";
    ClassDB myDB;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.user_info);

        name = (EditText) findViewById(R.id.tvName);
        pass = (EditText) findViewById(R.id.tvPass);
        _id = (EditText) findViewById(R.id.tvPass);
        myDB = new ClassDB(this, null, null, 1);


        mySwitch = (Switch) findViewById(R.id.hardmode);


        age = (TextView) findViewById(R.id.textView3);

        /////
        tv = (TextView) findViewById(R.id.tv);
        ////

        seek = (SeekBar) findViewById(R.id.seekBar);
        seek.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {


            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                current = progress;
            }

            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            public void onStopTrackingTouch(SeekBar seekBar) {
                s = Integer.toString(current);
                age.setText(s);

            }
        });

        mySwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {

            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

                if (isChecked) {
                    hardMode = true;


                } else {
                    hardMode = false;
                }
            }

        });


        //check the current state before we display the screen
        if(mySwitch.isChecked()){
            hardMode = true;

        }
        else {
            hardMode = false;

        }


    }

    public void onRadioButtonClicked(View view) {


        // Is the button now checked?
        boolean checked = ((RadioButton) view).isChecked();

        // Check which radio button was clicked
        switch (view.getId()) {
            case R.id.male:
                if (checked){
                    gender = "male";
                    break;

                }

                    break;
            case R.id.female:
                if (checked){
                    gender = "female";
                    break;

                }

        }
    }


    public void submit(View view) {
        Users user = new Users(name.getText().toString());
        user.set_password(pass.getText().toString());
        myDB.addUser(user);

        Intent k = new Intent(UsersInformation.this, FinalPage.class);
        startActivity(k);
    }
}