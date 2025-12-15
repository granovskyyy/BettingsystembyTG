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
    void viewAccountBalance(User & user); //viewing account balance
    void TransferMoney(User & user); //inserting money
    void WithdrawMoney(User & user); //withdrawing money
    void setWithdrawalLimit(User& user); //setting withdrawal limit
};