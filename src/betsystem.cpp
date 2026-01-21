#include "betsystem.h"
#include <iostream>
#include <string>
#include "database.h"
using namespace std;
BetSystem::BetSystem(Database& database): db(database){};
bool BetSystem::newBet(const string& username, const MatchEvent& match, const string& league, const string& betType, double stake)
{
    double odds=0;
    if(betType=="1")
    {
        odds=match.odds1;
    }
    else if(betType=="X")
    {
        odds=match.oddsX;
    }
    else
    {
        odds=match.odds2;
    }
    double win=stake*odds;
    Bet b;
    b.username=username;
    b.league=league;
    b.team1=match.team1;
    b.team2=match.team2;
    b.bet_type=betType;
    b.odds=odds;
    b.stake=stake;
    b.poswin=win;
    b.result="";
    b.status="PENDING";
    return db.addBet(b);
}
vector <Bet> BetSystem::getUserBets(const string& username)
{
    return db.getUserBets(username);
}
string BetSystem::MatchPredictor() 
{
    int r=rand()%100;
    if(r<30)
    {
        return "1";  //team 1 wins
    }
    else if(r<70)
    {
        return "X"; //draw
    }
    else
    {
        return "2"; //team 2 wins
    }
}
void BetSystem::resolveBets(const string& league)
{
    auto matches=db.getMatches(league);  
    auto bets=db.getPendingBets(league);
    for(auto& b:bets) //won bet 
    {
        string result=MatchPredictor();
        db.updateBetResult(b.id,result);
        if(result==b.bet_type)
        {
            string pwd;
            double balance=0;
            db.getUser(b.username,pwd,balance);
            double newBalance=balance+b.poswin;
            db.updateBetStatus(b.id,"WON");
            db.updateBalance(b.username,newBalance);
        }
        else{ //lost bet 
            db.updateBetStatus(b.id,"LOST");
        }
    }
}
void BetSystem::resolveMatches(const string& league)
{
    auto matches=db.getMatchesID(league); 
    for(auto& m:matches)
    {
        string result=MatchPredictor();
        db.updateMatchResult(m.id,result);
        cout<<"Final score"<<m.team1<<" vs "<<m.team2<<" =>"<<result<<endl;
    }
}
void BetSystem::resolveLeague(const string& league)
{
    resolveBets(league);
    resolveMatches(league);
}