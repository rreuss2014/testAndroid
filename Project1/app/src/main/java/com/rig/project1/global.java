package com.rig.project1;

import android.app.Application;

import java.util.Vector;

/**
 * Created by matthew on 9/1/2015.
 */
public class global extends Application {
    String name;
    String pass;
    String age;
    int level;
    boolean ifSetUp = false;
    boolean hardMode = false;
    String gender;

    Vector<Integer> levelArray = new Vector();
    Vector<String> nameArray = new Vector();
    Vector<String> ageArray = new Vector();
    Vector<String> genderArray = new Vector();




    public void setUpVectors () {
        levelArray.add(1);
        levelArray.add(2);
        levelArray.add(3);
        nameArray.add("Bill");
        nameArray.add("Jane");
        nameArray.add("Luke");
    }

    public String getName (){
        return this.name;
    }

    public void setName(String s){
        this.name = s;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public String getPass (){
        return this.pass;
    }
    public void setPass(String s){
        this.pass = s;
    }

    public String getAge (){
        return this.age;
    }
    public void setAge(String s){
        this.age = s;
    }

    public int getLevel (){return this.level;}
    public void setLevel(int i){this.level = i;}

    public String getNameArray (int i){return this.nameArray.elementAt(i);}
    public void setNameArray(String j){this.nameArray.add(j);}

    public int getLevelArray (int i){return this.levelArray.elementAt(i);}
    public void setLevelArray(int i){this.levelArray.add(i);}

    public boolean getIf(){
        return this.ifSetUp;
    }

    public void setIf(boolean s){
        this.ifSetUp = s;
    }

    public boolean isHardMode() {
        return hardMode;
    }

    public void setHardMode(boolean hardMode) {
        this.hardMode = hardMode;
    }

    public String getAgeArray (int i){return this.ageArray.elementAt(i);}
    public void setAgeArray(String k){this.ageArray.add(k);}

    public String getGenderArray (int i){return this.genderArray.elementAt(i);}
    public void setGenderArray(String k){this.genderArray.add(k);}

}


