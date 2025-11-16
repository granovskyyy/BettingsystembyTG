#pragma once
#include "userprofile.h"
#include <vector>
using namespace std;

class Authenication
{
    vector<User> users;
    public: 
    Authenication(vector <User>& users);
    User LoginSystem();
    void RegisterUser();
    string HiddenPWD(); //function for hiding password

};