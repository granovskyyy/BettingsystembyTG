#pragma once
#include "userprofile.h"
#include <vector>
#include <termios.h>
#include <unistd.h>


using namespace std;

class Authenication
{
    vector<User> users;
    public: 
    Authenication(vector <User>& users);
    int mygetch();
    User LoginSystem();
    void RegisterUser();
    string HiddenPWD(); //function for hiding password

};