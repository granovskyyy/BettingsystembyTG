#pragma once 
#include "userprofile.h"
#include "auth.h"
#include "wallet.h"
#include "fixtures.h"
#include "database.h"
using namespace std;
class App
{
    Database& db;
    Wallet wallet;
    public:
    App(Database& database);
    void Run();
    void UserMenu(User & user);
    int MainMenu();
    void CouponMenu(User & user);
    void WalletMenu(User & user);
    void EventMenu(User & user);
};