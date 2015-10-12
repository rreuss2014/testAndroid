package com.rig.database;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    EditText name, pass, _id;
    TextView tv;
    ClassDB myDB;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        name = (EditText) findViewById(R.id.Name);
        pass = (EditText) findViewById(R.id.Password);
        _id = (EditText) findViewById(R.id.Password);
        tv = (TextView) findViewById(R.id.db);
        myDB = new ClassDB(this, null, null, 1);


    }

    public void addButtonClicker(View v)
    {
        Users user = new Users(name.getText().toString());
        user.set_password(pass.getText().toString());
        myDB.addUser(user);
        printDatabase();

    }

    public void deleteButtonClicker(View v)
    {
        String input = name.getText().toString();
        myDB.deleteUser(input);
        printDatabase();

    }

    public void updateButtonClicker(View v)
    {
        Users user = new Users(name.getText().toString());
        user.set_password(pass.getText().toString());
        user.set_id(Integer.valueOf(_id.getText().toString()));
        myDB.updateUser(user);
        printDatabase();
    }

    public void printDatabase()
    {
        String data = myDB.databaseToString();
        tv.setText(data);
        name.setText("");
        pass.setText("");
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
