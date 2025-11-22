#include "app.h"
#include <iostream>
using namespace std;

App::App(Database& database): db(database), wallet(database) {};
void App::Run()
{
    vector <User> users;
    Database db("C:/Users/rt04/Documents/BettingsystembyTG/users.db");
    Authenication auth(users,db);
    Wallet wallet(db);
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
            EventMenu(user);
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
 

    int op; 
    do 
    {
          
        cout<<"BETPLANET #69 BEST BETTING SYSTEM"<<endl; 
        cout<<"1. Your coupons\n";
        cout<<"2. Coupons history\n";
        cout<<"0. Exit\n";
        cin>>op;
        switch(op)
        {
            case 0:
                break;
            case 1:
                cout<<"Under construction "<<endl;
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
    int op; 
    do 
    {
          
        cout<<"BETPLANET #69 BEST BETTING SYSTEM"<<endl; 
        cout<<"1. Account balance\n";
        cout<<"2. Insert money\n";
        cout<<"3. Withdraw money\n";
        cout<<"0. Exit\n";
        cin>>op;
        string pwd;
        switch(op)
        {
            case 0:
                break;
            case 1:
                
                double balance;
                if(db.getUser(user.getUsername(),pwd,balance))
                {
                    user.SetBalance(balance);
                }
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
void App::EventMenu(User& user)
{
    vector <string> teams;
    vector <pair<string,string>> fixtures; 
    Fixtures fx;
    
    
    
   
    int op;
      do {
        cout<<"BETPLANET #69 BEST BETTING SYSTEM"<<endl; 
        cout<<"1. LaLiga\n";
        cout<<"2. Premier League\n";
        cout<<"3. Ekstraklasa \n";
        cout<<"4. 1 Liga\n";
        cout<<"0. Exit\n";
        cin>>op;
        switch(op)
        {
            case 0:
                break;
            case 1:
                {
                    fstream laliga("C:\\Users\\rt04\\Documents\\BettingsystembyTG\\teams\\laliga.txt"); //your filepath here 
                    teams=fx.SaveTeams(laliga);
                }
                fixtures=fx.Matchmaking(teams);
                for(int i=0;i<fixtures.size();i++)
                {
                    cout<<fixtures[i].first<<" : "<<fixtures[i].second<<endl;
                }
                break;
            case 2:
                {
                    fstream pl("C:\\Users\\rt04\\Documents\\BettingsystembyTG\\teams\\premierleague.txt");
                    teams=fx.SaveTeams(pl);
                }
                fixtures=fx.Matchmaking(teams);
                for(int i=0;i<fixtures.size();i++)
                {
                    cout<<fixtures[i].first<<" : "<<fixtures[i].second<<endl;
                }
                break;
            case 3:
                {
                    fstream eklapa("C:\\Users\\rt04\\Documents\\BettingsystembyTG\\teams\\eklapa.txt");
                    teams=fx.SaveTeams(eklapa);
                }
                fixtures=fx.Matchmaking(teams);
                for(int i=0;i<fixtures.size();i++)
                {
                    cout<<fixtures[i].first<<" : "<<fixtures[i].second<<endl;
                }
                break;
            case 4:
                {
                    fstream wisla("C:\\Users\\rt04\\Documents\\BettingsystembyTG\\teams\\1liga.txt");
                    teams=fx.SaveTeams(wisla);
                }
                fixtures=fx.Matchmaking(teams);
                for(int i=0;i<fixtures.size();i++)
                {
                    cout<<fixtures[i].first<<" : "<<fixtures[i].second<<endl;
                }
                break;
            default:
                cout<<"Invalid option "<<endl;
            break;

        }
        
    }while(op!=0);
}