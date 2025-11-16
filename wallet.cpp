#include "wallet.h"
#include <iostream>
using namespace std;

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
    }
    double currentBalance=user.getBalance();
    double newBalance=currentBalance+amount;
    user.SetBalance(newBalance);
    cout<<"After money deposit: "<<user.getBalance()<<endl;



}
void Wallet::WithdrawMoney(User & user) //function to withdraw money 
{
    double amount;
    cout<<"Enter amount of money to withdraw from BetPlanet"<<endl;
    cin>>amount;
    double currentBalance=user.getBalance();
    if(amount>currentBalance)  
    {
        cout<<"Operation failed"<<endl;
    }
    double newBalance=currentBalance-amount;
    user.SetBalance(newBalance);
    cout<<"After money withdraw: "<<user.getBalance()<<endl;
    
}