#include "usermanagment.h"
#include <iostream>
#include <time.h>

UserManagment::UserManagment(Database& database):db(database) {};
void UserManagment::resetDailyLimit(const string& username)
{
    string lastDay=db.getStringValue("users","last_bet_dat",username); //reseting daily bet limit
    int count=db.getIntValue("users","daily_bet_count",username);
    time_t t=time(nullptr);
    tm* now=localtime(&t);
    char today[11];
    sprintf(today,"%04d-%02d-%02d",now->tm_year+1900,now->tm_mon+1,now->tm_mday);
    if(lastDay!=today)
    {
        db.updateIntValue(username,"daily_bet_count",0); //reseting limit when new day comes 
        db.updateStringValue(username,"last_bet_day",string(today));
    }
}
bool UserManagment::canPlaceBet(const string& username) //check if user can place a bet
{
    resetDailyLimit(username);
    int limit=db.getIntValue("users","daily_bet_limit",username);
    int count=db.getIntValue("users","daily_bet_limit",username);
    if(count>=limit)
    {
        return false;
    }
    if(isBlocked(username))
    {
        return false;
    }
    return true;
}
void UserManagment::registerBet(const string& username) //registering new bet in database
{
    resetDailyLimit(username);
    db.incrementBets(username);
}
double UserManagment::getWithdrawalLimit(const string& username)
{
    return db.getDoubleValue("users","withdrawal_limit",username);

}
bool UserManagment::updateWithdrawalLimit(const string& username,double limit) //setting new withdrawal limit in database
{
    return db.updateDoubleValue("users","withdrawal_limit",limit);
}
bool UserManagment::isBlocked(const string& username)
{
    return db.getIntValue("users", "blocked", username) == 1;
}

bool UserManagment::blockUser(const string& username)
{
    return db.updateIntValue(username, "blocked", 1);
}

bool UserManagment::unblockUser(const string& username)
{
    return db.updateIntValue(username, "blocked", 0);
}
