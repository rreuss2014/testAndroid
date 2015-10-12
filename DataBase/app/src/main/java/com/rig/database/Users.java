package com.rig.database;

/**
 * Created by ikergonzalez on 9/21/15.
 */
public class Users {

    private int _id;
    private String _user;
    private String _password;

    public Users()
    {


    }

    public Users (String u)
    {
        this._user = u;
    }

    public int get_id() {
        return _id;
    }

    public void set_id(int _id) {
        this._id = _id;
    }

    public String get_user() {
        return _user;
    }

    public void set_user(String _user) {
        this._user = _user;
    }

    public String get_password() {
        return _password;
    }

    public void set_password(String _password) {
        this._password = _password;
    }
}
