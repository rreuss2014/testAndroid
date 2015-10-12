package com.rig.database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * Created by ikergonzalez on 9/21/15.
 */
public class ClassDB extends SQLiteOpenHelper {

    private static final int TABLE_VERSION = 1;
    private static final String DATABASE_NAME = "class.db";
    public static final String TABLE_USERS = "users";
    public static final String COLUMN_ID = "_id";
    public static final String COLUMN_USERNAME = "name";
    public static final String COLUMN_USERPASS = "pass";


    public ClassDB(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, DATABASE_NAME, factory, TABLE_VERSION);
    }


    @Override
    public void onCreate(SQLiteDatabase db) {

        String query = "CREATE TABLE " + TABLE_USERS + "(" +
                COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                COLUMN_USERNAME + " TEXT, " +
                COLUMN_USERPASS + " TEXT " + ");";

        db.execSQL(query);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

        db.execSQL("DROP IF TABLE EXISTS " + TABLE_USERS);
        onCreate(db);
    }

    //Add a row of a user instance
    public void addUser(Users user)
    {
        ContentValues cv = new ContentValues();
        cv.put(COLUMN_USERNAME,user.get_user());
        cv.put(COLUMN_USERPASS,user.get_password());
        SQLiteDatabase db = getWritableDatabase();
        db.insert(TABLE_USERS, null, cv);
        db.close();
    }

    //Delete a row
    public void deleteUser(String userName)
    {
        SQLiteDatabase db = getWritableDatabase();
        db.execSQL("DELETE FROM " + TABLE_USERS + " WHERE " + COLUMN_USERNAME + "=\"" + userName + "\";");
    }

    public void updateUser(Users user)
    {
        ContentValues cv = new ContentValues();
        cv.put(COLUMN_USERNAME,user.get_user());
        cv.put(COLUMN_USERPASS,user.get_password());
        SQLiteDatabase db = getWritableDatabase();
        db.update(TABLE_USERS, cv, "_id " + "=" + user.get_id(), null );
        db.close();


    }
    //Print out database
    public String databaseToString()
    {
        String dbString = "";
        SQLiteDatabase db = getWritableDatabase();
        String query = "SELECT * FROM " + TABLE_USERS + " WHERE 1";

        //Cursor point to a location in your results
        Cursor c = db.rawQuery(query, null);

        c.moveToFirst();

        while(!c.isAfterLast())
        {
            if(c.getString(c.getColumnIndex("name")) != null)
            {
                dbString += c.getString(c.getColumnIndex("_id"));
                dbString += " ";
                dbString += c.getString(c.getColumnIndex("name"));
                dbString += " ";
                dbString += c.getString(c.getColumnIndex("pass"));
                dbString += "\n";

            }
            c.moveToNext();
        }
        db.close();
        return dbString;
    }
}

//git hub test

