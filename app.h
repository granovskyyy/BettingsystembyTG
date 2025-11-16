#pragma once 
#include "userprofile.h"
#include "auth.h"
using namespace std;
class App
{
    public:
    void Run();
    void UserMenu(User & user);
    int MainMenu();
};