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
    void UserMenu(User & user); //menu after login
    int MainMenu(); //start menu
    void CouponMenu(User & user); //coupon menu
    void WalletMenu(User & user); //wallet menu
    void EventMenu(User & user); //event menu
    void ShowActiveBets(User& user); //showing active bets
    void ShowBetHistory(User& user); //showing bet history
    void PlaceBet(User& user); //placing new bet
    void AccountManager(User& user); //managing account
    int readInt(int min,int max); //input validation
    void ResponsibleGambling(User& user);  //functions for limiting account
    void BetsPerGameLimitMenu(User& user); //limiting bets per day
    void StakeLimitMenu(User& user); //limiting stake per bet
    void AccountLockMenu(User& user); //temporary account lock
    void ViewActualLimits(User& user); //viewing actual limits
};