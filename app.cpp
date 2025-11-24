#include "app.h"
#include "betsystem.h"
#include <iostream>
using namespace std;

App::App(Database& database): db(database), wallet(database),bets(database) {};
int App::readInt(int min, int max)  //function to prevent unexcepted inputs
{
    int val;
    while(true)
    {
        cout<<">";
        if(cin >>val)
        {
            if(val>=min && val <= max)
                return val;
            cout<<"Invalid option, choose between "<<min<<" and "<<max<<"\n";
        }
        else
        {
            cin.clear();
            cin.ignore(10000,'\n');
            cout<<"Invalid input. Enter number\n";
        }
    }
}
void App::Run()
{
    vector <User> users;
    Database db("C:/Users/rt04/Documents/BettingsystembyTG/users.db");
    Authenication auth(users,db);
    Wallet wallet(db);
    BetSystem bets(db);
 
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
        cout<<"4. Account Managment\n";
        cout<<"0. Logout"<<endl;
        op=readInt(0,4);
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
        case 4:
            AccountManager(user); 
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
    op=readInt(0,2);
    return op;
}
void App::CouponMenu(User& user)
{
 

    int op; 
    do 
    {
          
        cout<<"BETPLANET #69 BEST BETTING SYSTEM"<<endl; 
        cout<<"1. Place coupon\n";
        cout<<"2. Your coupons\n";
        cout<<"3. Coupons history\n";
        cout<<"0. Exit\n";
        op=readInt(0,3);
        switch(op)
        {
            case 0:
                break;
            case 1:
                PlaceBet(user);
                break;
            case 2:
                ShowActiveBets(user);
                break;
            case 3:
                ShowBetHistory(user);
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
        op=readInt(0,3);
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
            break;

        }
    }while(op!=0);

}
void App::EventMenu(User& user)
{
    vector <string> teams;
    vector <MatchEvent> fixtures; 
    vector <string> leagues={"LaLiga", "PremierLeague","Ekstraklasa","1liga"};
    Fixtures fx;
    int op;
      do {
       
        cout<<"BETPLANET #69 BEST BETTING SYSTEM"<<endl; 
        cout<<"1. LaLiga\n";
        cout<<"2. Premier League\n";
        cout<<"3. Ekstraklasa \n";
        cout<<"4. 1 Liga\n";
        cout<<"5. Results\n";
        cout<<"0. Exit\n";
        op=readInt(0,5);
        string league;
        string filepath;
        
        switch(op)
        {
            case 0:
                break;
            case 1:
                league="LaLiga";
                filepath="C:\\Users\\rt04\\Documents\\BettingsystembyTG\\teams\\laliga.txt"; //YOUR FILEPATH HERE
                break;
            case 2:
                league="PremierLeague";
                filepath="C:\\Users\\rt04\\Documents\\BettingsystembyTG\\teams\\premierleague.txt"; //YOUR FILEPATH HERE
                    break;             
            case 3:
                league="Ekstraklasa";

                filepath="C:\\Users\\rt04\\Documents\\BettingsystembyTG\\teams\\eklapa.txt"; //YOUR FILEPATH HERE
                    break;
            case 4:
                league="1liga";
                filepath="C:\\Users\\rt04\\Documents\\BettingsystembyTG\\teams\\1liga.txt"; //YOUR FILEPATH HERE
                break;
            case 5:
                if(leagues.empty())
                {
                    cout<<"Wait for final results"<<endl;
                    continue;
                }
                for(auto& l:leagues)
                {
                    bets.resolveLeague(l);
                }
                continue;
            default:
                cout<<"Invalid option "<<endl;
                continue;
        }

        if (!db.MatchDay(league))
            {
                fstream file(filepath);
                teams = fx.SaveTeams(file);
                fixtures = fx.Matchmaking(teams);
                for(int i=0;i<fixtures.size();i++)
                {
                    db.addMatch(fixtures[i], league); //saving matches to database to use them in betting
                }
            }
            fixtures=db.getMatches(league);
            cout<<fixed<<setprecision(2);
            cout<<league<<" MATCHES"<<endl;
        for(auto &m: fixtures)
            {
                cout<<m.team1<<" : "<<m.team2<<"\n"
                <<"WIN 1: "<<m.odds1<<"\n"
                <<"DRAW: "<<m.oddsX<<"\n"
                <<"WIN 2: "<<m.odds2<<"\n"
                <<endl;
        }
    }while(op!=0);
}
void App::ShowActiveBets(User& user)
{
    auto bets=db.getUserBets(user.getUsername());
    cout<<"ACTIVE BETS"<<endl;
    bool any=false;
    for(auto&b :bets)
    {
        if(b.status=="PENDING")
        {
            any=true;
            cout<<"Match: "<<b.team1<<" vs"<<b.team2<<endl;
            cout<<"League: "<<b.league<<endl;
            cout<<"Bet: "<<b.bet_type<<" @ "<<b.odds<<endl;
            cout<<"Stake: "<<b.stake<<endl;
            cout<<"Possible win: "<<b.poswin<<endl;
            cout<<"Status: "<<b.status<<endl;
            cout<<"-------------------"<<endl;
        }

    }
    if(!any)
    {
        cout<<"No active bets"<<endl;
    }
    cout<<endl;
}
void App::ShowBetHistory(User& user)
{
    auto bets=db.getUserBets(user.getUsername());
    cout<<"BET HISTORY"<<endl;
    bool any=false;
    for(auto&b :bets)
    {
        if(b.status=="WON"||b.status=="LOST")
        {
            any=true;
            cout<<"Match: "<<b.team1<<" vs"<<b.team2<<endl;
            cout<<"League: "<<b.league<<endl;
            cout<<"Bet: "<<b.bet_type<<" @ "<<b.odds<<endl;
            cout<<"Stake: "<<b.stake<<endl;
            cout<<"Possible win: "<<b.poswin<<endl;
            cout<<"Status: "<<b.status<<endl;
            cout<<"-------------------"<<endl;
        }

    }
    if(!any)
    {
        cout<<"No bet history"<<endl;
    }
    cout<<endl;
}
void App::PlaceBet(User & user)
{
    
    int op;
      do {
       
        cout<<"BETPLANET #69 BEST BETTING SYSTEM"<<endl; 
        cout<<"PLACE A BET"<<endl;
        cout<<"1. LaLiga\n";
        cout<<"2. Premier League\n";
        cout<<"3. Ekstraklasa \n";
        cout<<"4. 1 Liga\n";
        cout<<"0. Back\n";
        op=readInt(0,4);
        string league;
        switch(op)
        {
            case 0:
                break;
            case 1:
                league="LaLiga";
                break;
            case 2:
                league="PremierLeague";
                break;             
            case 3:
                league="Ekstraklasa";
                break;
            case 4:
                league="1liga";
                break;
            default:
                cout<<"Invalid option "<<endl;
                continue;
        }
        auto matches=db.getMatches(league);
        if(matches.empty())
        {
            cout<<"No matches avaible for this league"<<endl;
            continue;
        }
        cout<<league<<" MATCHES"<<endl;
        for(int i=0;i<matches.size();i++)
            {
                cout<<(i+1)<<". "
                <<matches[i].team1<<" : "<<matches[i].team2<<"\n"
                <<"1 : "<<matches[i].odds1<<"\n"
                <<"X: "<<matches[i].oddsX<<"\n"
                <<"2: "<<matches[i].odds2<<"\n"
                <<endl;
        }
        int index;
        cout<<"Choose match number"<<endl;
        cin>>index;
        if(index<1 || index>matches.size())
        {
            cout<<"Invalid index \n";
            continue;
        }
        index--;
        string yourbet;
        cout<<"Choose bet type (1/X/2)";
        cin>>yourbet;
        if(yourbet!="1" && yourbet!="X" && yourbet!="2")
        {
            cout<<"Invalid bet type \n";
            continue;
        }
        double stake;
        cout<<"Stake amount: "<<endl;
        cin>>stake;
        if(stake<=0 || stake >user.getBalance())
        {
            cout<<"Invalid stake "<<endl;
            continue;
        }
        if(bets.newBet(user.getUsername(),matches[index],league,yourbet,stake))
        {
            user.SetBalance(user.getBalance()-stake);
            db.updateBalance(user.getUsername(),user.getBalance());
            cout<<"Bet placed successfully"<<endl;
        }
        else
        {
            cout<<"Could not place a bet"<<endl;
        }
    }while(op!=0);
}
void App::ViewScores(User& user)
{
     int op;
      do {
       
        cout<<"BETPLANET #69 BEST BETTING SYSTEM"<<endl; 
        cout<<"SCORES "<<endl;
        cout<<"1. LaLiga\n";
        cout<<"2. Premier League\n";
        cout<<"3. Ekstraklasa \n";
        cout<<"4. 1 Liga\n";
        cout<<"0. Back\n";
        op=readInt(0,4);
        string league;
        switch(op)
        {
            case 0:
                break;
            case 1:
                bets.resolveLeague("LaLiga");
                break;
            case 2:
                bets.resolveLeague("PremierLeague");
                break;             
            case 3:
                bets.resolveLeague("Ekstraklasa");
                break;
            case 4:
                bets.resolveLeague("1liga");
                break;
            default:
                cout<<"Invalid option "<<endl;
                continue;
        }
    }while(op!=0);
}
void App::AccountManager(User &user)
{
    int op;
      do {
       
        cout<<"BETPLANET #69 BEST BETTING SYSTEM"<<endl; 
        cout<<"Account Manager "<<endl;
        cout<<"1.Change password\n";
        cout<<"2.Limits \n";
        cout<<"3. Delete account\n";
        cout<<"0. Back\n";
        op=readInt(0,3);
        string league;
        switch(op)
        {
            case 0:
                break;
            case 1:
                cout<<"Under construction"<<endl;
                break;
            case 2:
                cout<<"Under construction"<<endl;
                break;             
            case 3:
                cout<<"Under construction"<<endl;
                break;
            default:
                cout<<"Invalid option "<<endl;
                continue;
        }
    }while(op!=0);
}