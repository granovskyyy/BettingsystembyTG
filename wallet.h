#pragma once
#include <iostream>
#include "userprofile.h"
#include "database.h"
using namespace std;
class Wallet
{
    Database& db;
    public:
    Wallet(Database& database);
    void viewAccountBalance(User & user);
    void TransferMoney(User & user);
    void WithdrawMoney(User & user);
    void setWithdrawalLimit(User& user);
};