#include "usermanagment.h"
#include <iostream>
#include <unordered_map>

UserManagment::UserManagment(Database& database):db(database) {};


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
    db.resetDailyBets();
}
