#include "usermanagment.h"
#include <iostream>
#include <time.h>
#include <unordered_map>
unordered_map<string, time_t> tempBlocks;
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
bool UserManagment::isBlocked(const string& username)
{
    return db.getIntValue("users","blocked",username)==1;
}
void UserManagment::blockUser(const string& username, int rounds)
{
    db.updateIntValue(username, "blocked", 1);
    db.updateIntValue(username, "block_days", rounds);
    db.updateIntValue(username, "locked_days", 0);
}


bool UserManagment::unblockUser(const string& username)
{
    return db.updateIntValue(username, "block_end_time", 0);
}
void UserManagment::processTimeStep()
{
    db.incrementLockedDays();
    db.unlockUsers();
}
