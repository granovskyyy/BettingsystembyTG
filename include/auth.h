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
    int mygetch(); //function for hiding password input(UNIX specific)
    User LoginSystem(); //logging in existing user
    void RegisterUser(); //registering new user
    string HiddenPWD(); //function for hiding password
    unsigned int hashPWD(const string& password); //hashing password
    bool ChangePassword(Database& db, User& user); //changing password
    bool isPasswordValid(const string& password); //checking password validity
    bool readValidPassword(string& password); //reading valid password
};