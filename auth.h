#pragma once
#include "userprofile.h"
#include "database.h"
#include <vector>
#if defined(_WIN64)
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

using namespace std;

class Authenication
{
    vector<User> users;
    Database& db;
    public: 
    Authenication(vector <User>& users, Database& db);
    int mygetch();
    User LoginSystem();
    void RegisterUser();
    string HiddenPWD(); //function for hiding password

};