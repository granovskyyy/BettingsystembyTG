#include "app.h"
#include "betsystem.h"
#include <iostream>
using namespace std;

App::App(Database& database): db(database), wallet(database),bets(database),userManagment(database){};
vector <User> users;
Database db("data/users.db");
Authenication auth(users,db);
Wallet wallet(db);
BetSystem bets(db);
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
        
        cout<<"WELCOME TO BETTING APP "<<endl; 
        cout<<"User "<<user.getUsername()<<endl;
        cout<<"1. Coupons\n";
        cout<<"2. Wallet \n";
        cout<<"3. Events today\n";
        cout<<"4. Account Management\n";
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
    cout<<"BETTING APP "<<endl; 
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
          
        cout<<"COUPON MENU"<<endl; 
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
          
        cout<<"WALLET MENU "<<endl; 
        cout<<"1. Account balance\n";
        cout<<"2. Insert money\n";
        cout<<"3. Withdraw money\n";
        cout<<"4. Withdrawal limits\n";
        cout<<"0. Exit\n";
        op=readInt(0,4);
        string pwd;
        switch(op)
        {
            case 0:
                break;
            case 1:
                cout<<"ACCOUNT BALANCE"<<endl;
                double balance;
                if(db.getUser(user.getUsername(),pwd,balance))
                {
                    user.SetBalance(balance);
                }
                wallet.viewAccountBalance(user);
                break;
            case 2:
                cout<<"INSERT MONEY"<<endl;
                wallet.TransferMoney(user);
                break;
            case 3:
                cout<<"WITHDRAW MONEY"<<endl;
                wallet.WithdrawMoney(user);
                break;
            case 4:
                cout<<"WITHDRAWAL LIMITS"<<endl;
                wallet.setWithdrawalLimit(user);
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
    vector <string> leagues={"LaLiga", "PremierLeague","Ekstraklasa","1liga","Bundesliga","SerieA"};
    Fixtures fx;
    int op;
      do {
       
        cout<<"EVENT MENU "<<endl; 
        cout<<"1. LaLiga\n";
        cout<<"2. Premier League\n";
        cout<<"3. Bundesliga\n";
        cout<<"4. Serie A\n";
        cout<<"5. Ekstraklasa \n";
        cout<<"6. 1 Liga\n";
        cout<<"7. Results\n";
        cout<<"0. Exit\n";
        op=readInt(0,7);
        string league;
        string filepath;
        
        switch(op)
        {
            case 0:
                break;
            case 1:
                league="LaLiga";
                filepath="data/teams/laliga.txt"; 
                break;
            case 2:
                league="PremierLeague";
                filepath="data/teams/premierleague.txt"; 
                break;     
            case 3:
                league="Bundesliga";
                filepath="data/teams/bundesliga.txt"; 
                break;  
            case 4:
                league="SerieA";
                filepath="data/teams/seriea.txt"; 
                break;      
            case 5:
                league="Ekstraklasa";
                filepath="data/teams/eklapa.txt"; 
                break;
            case 6:
                league="1liga";
                filepath="data/teams/1liga.txt"; 
                break;
            case 7:
                if(leagues.empty())
                {
                    cout<<"Wait for final results"<<endl;
                    continue;
                }
                for(auto& l:leagues)
                {
                    bets.resolveLeague(l);
                }
                userManagment.processTimeStep();
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
        if(db.getIntValue("users","daily_bet_limit",user.getUsername()) <= db.getIntValue("users","daily_bet_count",user.getUsername()) || userManagment.isBlocked(user.getUsername()))
        {
            cout<<"Your account is temporarily blocked. Cannot place bets"<<endl;
            return;
        }
        cout<<"PLACE A BET"<<endl;
        cout<<"1. LaLiga\n";
        cout<<"2. Premier League\n";
        cout<<"3. Bundesliga\n";
        cout<<"4. Serie A\n";
        cout<<"5. Ekstraklasa \n";
        cout<<"6. 1 Liga\n";
        cout<<"0. Back\n";
        op=readInt(0,6);
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
                league="Bundesliga";
                break;
            case 4:
                league="SerieA";
                break;             
            case 5:
                league="Ekstraklasa";
                break;
            case 6:
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
        cout<<"Choose bet type (1/X/2)"<<endl;
        cin>>yourbet;
        if(yourbet!="1" && yourbet!="X" && yourbet!="2")
        {
            cout<<"Invalid bet type \n";
            continue;
        }
        double stake;
        cout<<"Stake amount: "<<endl;
        cin>>stake;
        if(stake<=0 || stake >user.getBalance() || stake > db.getDoubleValue("users","max_stake_limit",user.getUsername())) //checking is stake valid 
        {
            cout<<"Invalid stake "<<endl;
            continue;
        }
        if(bets.newBet(user.getUsername(),matches[index],league,yourbet,stake))
        {
            user.SetBalance(user.getBalance()-stake);
            db.updateBalance(user.getUsername(),user.getBalance());
            cout<<"Bet placed successfully"<<endl;
            db.incrementBets(user.getUsername());
            
        }
        else
        {
            cout<<"Could not place a bet"<<endl;
        }
    }while(op!=0);
}
void App::AccountManager(User &user)
{
    int op;
      do {
        cout<<"ACCOUNT MANAGEMENT"<<endl;
        cout<<"1.Change password\n";
        cout<<"2.Limits \n";
        cout<<"0. Back\n";
        op=readInt(0,2);
        string league;
        switch(op)
        {
            case 0:
                break;
            case 1:
                auth.ChangePassword(db,user);
                break;
            case 2:
                ResponsibleGambling(user);
                break;             
            default:
                cout<<"Invalid option "<<endl;
                continue;
        }
    }while(op!=0);
}
void App::ResponsibleGambling(User& user)
{
    int op;
      do {
       
        cout<<"LIMITS"<<endl;
        cout<<"1.Bets per day limit\n";
        cout<<"2.Stake limit\n";
        cout<<"3.Temporary account block (24h/7d/30d)\n";
        cout<<"4.View actual limits\n";
        cout<<"0.Back\n";
        op=readInt(0,4);
        string league;
        switch(op)
        {
            case 0:
                break;
            case 1:
                BetsPerGameLimitMenu(user);
                break;
            case 2:
                StakeLimitMenu(user);
                break;             
            case 3:
                AccountLockMenu(user);
                break;
            case 4:
                ViewActualLimits(user);
                break;
            default:
                cout<<"Invalid option "<<endl;
                continue;
        }
    }while(op!=0);
}

void App::BetsPerGameLimitMenu(User& user)
{
    int newLimit;
    cout<<"SET DAILY BET LIMIT"<<endl;
    cout << "Enter new daily bet limit: ";
    newLimit = readInt(1, 100); //range to 100 bets daily
    db.updateIntValue(user.getUsername(), "daily_bet_limit", newLimit);
    cout << "Daily bet limit updated to: " << newLimit << "\n\n";
}

void App::ViewActualLimits(User& user)
{
    cout << "ACTIVE LIMITS \n";

    int dailyLimit = db.getIntValue("users","daily_bet_limit", user.getUsername());
    double stakeLimit = db.getDoubleValue("users", "max_stake_limit", user.getUsername());
    int blocked = db.getIntValue("users", "blocked", user.getUsername());

    cout << "Daily bet limit: " << dailyLimit << "\n";
    cout << "Max stake per bet: " << stakeLimit << "\n";

    if(blocked==0)
        cout << "Account status: Active\n";
    else
        cout << "Account locked \n";

    cout << "\n";
}
void App::StakeLimitMenu(User& user)
{
    cout<<"STAKE LIMIT MENU"<<endl;
    cout<<"Enter new stake limit amount: "<<endl;
    double newLimit;
    cin>>newLimit;
    if(!cin || newLimit<=0)
    {
        cin.clear();
        cin.ignore(10000,'\n');
        cout<<"Invalid limit"<<endl;
        return;
    }
    db.updateDoubleValue(user.getUsername(),"max_stake_limit",newLimit);
    cout<<"Stake limit updated to: "<<newLimit<<endl;

};
void App::AccountLockMenu(User& user)
{
    
    int op;
      do {
       
        cout<<"ACCOUNT LOCK MENU"<<endl;
        cout<<"1.Block 24h\n";
        cout<<"2.Block 72h\n";
        cout<<"3.Block 1 week\n";
        cout<<"0.Back\n";
        op=readInt(0,4);
        string league;
        switch(op)
        {
            case 0:
                break;
            case 1:
                userManagment.blockUser(user.getUsername(), 1);
                cout<<"Account blocked for 24h"<<endl;
                break;
            case 2:
                userManagment.blockUser(user.getUsername(), 3);
                cout<<"Account blocked for 72h"<<endl;
                break;             
            case 3:
                userManagment.blockUser(user.getUsername(), 7);
                cout<<"Account blocked for 1 week"<<endl;
                break;
            default:
                cout<<"Invalid option "<<endl;
                continue;
        }
    }while(op!=0);
};



