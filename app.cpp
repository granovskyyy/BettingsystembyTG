#include "app.h"
#include "coupons.h"
#include <iostream>
using namespace std;

void App::Run()
{
    vector <User> users;
  
    Authenication auth(users);
   
    
    
    int op;
 
    do
    {
        op=MainMenu();
        switch(op)
        {
            case 0:
                cout<<"Exiting program"<<endl;
                break;
            case 1:
                auth.RegisterUser();
                break;
            case 2:
                User u=auth.LoginSystem();
                if(u.getUsername()=="")
                {
                    continue;
                }
                else
                {
                    UserMenu(u);
                }
                break;
        }
    } while (op!=0);
    
}
void App:: UserMenu(User & user)
{
    int op;

    do 
    {
        cout<<"BETPLANET #69 BEST BETTING SYSTEM"<<endl; 
        cout<<"Welcome user "<<user.getUsername()<<endl;
        cout<<"1. Coupons\n";
        cout<<"2. Wallet \n";
        cout<<"3. Events today\n";
        cout<<"0. Logout"<<endl;
        cin>>op;
        switch(op)
        {
        case 0:
            cout<<"Logging out..."<<endl;
            break;
        case 1:
            CouponMenu(user);
            break;
        case 2:
            WalletMenu(user);
            break;
        case 3:
            cout<<"Under construction"<<endl;
            break;
        default:
            cout<<"Invalid option "<<endl;
            break;
        }
    }while(op!=0);


}
int App::MainMenu()
{
    int op;   
    cout<<"BETPLANET #69 BEST BETTING SYSTEM"<<endl; 
    cout<<"1. Register \n";
    cout<<"2. Login\n";
    cout<<"0. Exit\n";
    cin>>op;
    return op;
}
void App::CouponMenu(User& user)
{
    vector <string> teams;
    Coupons coupon;

    int op; 
    do 
    {
          
        cout<<"BETPLANET #69 BEST BETTING SYSTEM"<<endl; 
        cout<<"1. Teams list\n";
        cout<<"2. Coupons history\n";
        cout<<"0. Exit\n";
        cin>>op;
        switch(op)
        {
            case 0:
                break;
            case 1:
                teams=coupon.SaveTeams();
                cout<<"TEAMS LIST"<<endl;
                for (const auto& team : teams) {
                    cout << team << endl;
                }
                break;
            case 2:
                cout<<"Under construction"<<endl;
                break;
            default:
                cout<<"Invalid option "<<endl;
            break;

        }
    }while(op!=0);
}
void App::WalletMenu(User& user)
{
    Wallet wallet;
    int op; 
    do 
    {
          
        cout<<"BETPLANET #69 BEST BETTING SYSTEM"<<endl; 
        cout<<"1. Account balance\n";
        cout<<"2. Insert money\n";
        cout<<"3. Withdraw money\n";
        cout<<"0. Exit\n";
        cin>>op;
        switch(op)
        {
            case 0:
                break;
            case 1:
                wallet.viewAccountBalance(user);
                break;
            case 2:
                wallet.TransferMoney(user);
                break;
            case 3:
                wallet.WithdrawMoney(user);
                break;
            default:
                cout<<"Invalid option "<<endl;
            break;

        }
    }while(op!=0);

}