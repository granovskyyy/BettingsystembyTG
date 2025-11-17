#pragma once 
#include "userprofile.h"
#include "auth.h"
#include "wallet.h"
#include "fixtures.h"
using namespace std;
class App
{
    public:
    void Run();
    void UserMenu(User & user);
    int MainMenu();
    void CouponMenu(User & user);
    void WalletMenu(User & user);
    void EventMenu(User & user);
};