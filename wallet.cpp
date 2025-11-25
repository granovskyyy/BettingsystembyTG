#include "wallet.h"
#include <iostream>
using namespace std;
Wallet::Wallet(Database &database) :db(database) {};
void Wallet::viewAccountBalance(User & user)
{
    cout<<"Your balance: "<<user.getBalance()<<endl; //function used to view your acc balance 
}
void Wallet::TransferMoney(User & user)
{
    double amount;
    cout<<"Enter amount of money to deposit on BetPlanet"<<endl;
    cin>>amount;
    if(amount<0) //function to deposit money 
    {
        cout<<"Wrong amount"<<endl;
        amount=0;
    }
    double newBalance=user.getBalance()+amount;
    user.SetBalance(newBalance);
    db.updateBalance(user.getUsername(),user.getBalance());
    cout<<"After money deposit: "<<user.getBalance()<<endl;



}
void Wallet::WithdrawMoney(User & user) //function to withdraw money 
{
    double amount;
    cout<<"Enter amount of money to withdraw from BetPlanet"<<endl;
    cin>>amount;
    double currentBalance=user.getBalance();
    double limit=db.getWithdrawalLimit(user.getUsername());
    if(amount>limit)
    {
        cout<<"Operation failed. Your withdraw limit is: "<<limit<<endl;
        amount=0;
    }
    if(amount>currentBalance)  
    {
        cout<<"Operation failed. Not enough funds"<<endl;
        amount=0;
    }
    double newBalance=currentBalance-amount;
    user.SetBalance(newBalance);
    db.updateBalance(user.getUsername(),user.getBalance());
    cout<<"After money withdraw: "<<user.getBalance()<<endl;
    
}
void Wallet::setWithdrawalLimit(User& user)
{
    double newlimit;
    cout<<"Enter withdrawal limit"<<endl;
    cout<<"Current limit: "<<db.getWithdrawalLimit(user.getUsername())<<endl;
    cin>>newlimit;
    if(!cin ||newlimit<=0)
    {
        cin.clear();
        cin.ignore(10000,'\n');
        cout<<"Invalid limit"<<endl;
        newlimit=0;
    }
    db.updateWithdrawalLimit(user.getUsername(),newlimit);
    cout<<"New limit set succesfully to: "<<newlimit<<endl;
}
