#pragma once
#include <iostream>
#include "userprofile.h"
using namespace std;
class Wallet
{
    public:
    void viewAccountBalance(User & user);
    void TransferMoney(User & user);
    void WithdrawMoney(User & user);
};