#pragma once 
#include "userprofile.h"
#include "auth.h"
#include "wallet.h"
#include "fixtures.h"
#include "database.h"
#include "usermanagment.h"
#include <iomanip>
class BetSystem;
using namespace std;
class App
{
    Database db;
    Wallet wallet;
    BetSystem bets;
    UserManagment userManagment;
    public:
    App(Database& database);
    void Run(); //staring app 
    void UserMenu(User & user);
    int MainMenu();
    void CouponMenu(User & user);
    void WalletMenu(User & user);
    void EventMenu(User & user);
    void ShowActiveBets(User& user);
    void ShowBetHistory(User& user);
    void PlaceBet(User& user);
    void AccountManager(User& user);
    int readInt(int min,int max);
    void ResponsibleGambling(User& user); 
    //limits menus 
    void BetsPerGameLimitMenu(User& user); 
    void StakeLimitMenu(User& user);
    void AccountLockMenu(User& user);
    void ViewActualLimits(User& user);
    //changing password
    void ChangePasswordMenu(User& user);
};