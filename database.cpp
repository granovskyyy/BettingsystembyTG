#include "database.h"
#include <iostream>
using namespace std;

Database::Database(const string& filename)
{
    if(sqlite3_open(filename.c_str(), &db)!=SQLITE_OK)
    {
        cerr<<"Cannot open DB";
    }

    const char* create_sql =
        "CREATE TABLE if NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "pwd TEXT NOT NULL,"
        "balance REAL DEFAULT 0"
        ");";
 
    sqlite3_exec(db, create_sql, nullptr, nullptr, nullptr);

    const char* create_matches =
        "CREATE TABLE IF NOT EXISTS matches ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "league TEXT NOT NULL,"
        "day INTEGER NOT NULL,"
        "team1 TEXT NOT NULL,"
        "team2 TEXT NOT NULL,"
        "odds1 REAL NOT NULL,"
        "oddsX REAL NOT NULL,"
        "odds2 REAL NOT NULL,"
        "results TEXT"
        ");";

    sqlite3_exec(db, create_matches, nullptr, nullptr, nullptr);

    const char* create_bets =
        "CREATE TABLE IF NOT EXISTS bets("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL,"
        "league TEXT NOT NULL,"
        "team1 TEXT NOT NULL,"
        "team2 TEXT NOT NULL,"
        "bet_type TEXT NOT NULL,"
        "odds REAL NOT NULL,"
        "stake REAL NOT NULL,"
        "poswin REAL NOT NULL,"
        "result TEXT,"
        "status TEXT NOT NULL"
        ");";
    sqlite3_exec(db, create_bets, nullptr, nullptr, nullptr);
}
Database::~Database()
{
    sqlite3_close(db);
}
bool Database::addUser(const string& username, const string& pwd, double balance)
{
    const char* sql= "INSERT INTO users(username,pwd,balance) VALUES (?,?,?)";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,username.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,2,pwd.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt,3,balance);

    bool ok=sqlite3_step(stmt)==SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}
bool Database::getUser(const string& username, string& pwdOut, double& balanceout)
{
    const char* sql= "SELECT pwd,balance FROM users WHERE username =?";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,username.c_str(),-1,SQLITE_TRANSIENT);

    if(sqlite3_step(stmt)!=SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        return false;
    }
    pwdOut=(const char*)sqlite3_column_text(stmt, 0);
    balanceout=sqlite3_column_double(stmt,1);

    sqlite3_finalize(stmt);
    return true;
}
bool Database::updateBalance(const string& username, double newBalance)
{
    const char* sql = "UPDATE users SET balance = ? WHERE username = ?";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_double(stmt,1,newBalance);
    sqlite3_bind_text(stmt,2,username.c_str(),-1,SQLITE_TRANSIENT);

    bool ok=(sqlite3_step(stmt)==SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;

}
bool Database::MatchDay(string league)
{
    const char* sql = "SELECT COUNT(*) FROM matches WHERE league = ?";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,league.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    int count=sqlite3_column_int(stmt,0);
   
    sqlite3_finalize(stmt);
    return count > 0;
}
void Database::addMatch(const MatchEvent& m, string league)
{
    const char* sql= "INSERT INTO matches(league,day,team1,team2,odds1,oddsX,odds2) VALUES(?,?,?,?,?,?,?)";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,league.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,2,1);
    sqlite3_bind_text(stmt,3,m.team1.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,4,m.team2.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt,5,m.odds1);
    sqlite3_bind_double(stmt,6,m.oddsX);
    sqlite3_bind_double(stmt,7,m.odds2);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}
vector <MatchEvent> Database::getMatches(string league)
{
    vector <MatchEvent> out;
    const char* sql = "SELECT team1, team2, odds1, oddsX, odds2 FROM matches WHERE league =?";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,league.c_str(),-1,SQLITE_TRANSIENT);
    
    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        MatchEvent m;
        m.team1=(const char*)sqlite3_column_text(stmt,0);
        m.team2=(const char*)sqlite3_column_text(stmt,1);
        m.odds1=sqlite3_column_double(stmt,2);
        m.oddsX=sqlite3_column_double(stmt,3);
        m.odds2=sqlite3_column_double(stmt,4);
        out.push_back(m);
    }
    sqlite3_finalize(stmt);
    return out;
}
bool Database::addBet(const Bet& b)
{
    const char* sql="INSERT INTO bets (username,league,team1,team2,bet_type,odds,stake,poswin,result,status) VALUES(?,?,?,?,?,?,?,?,?,?)";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,b.username.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,2,b.league.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,3,b.team1.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,4,b.team2.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,5,b.bet_type.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt,6,b.odds);
    sqlite3_bind_double(stmt,7,b.stake);
    sqlite3_bind_double(stmt,8,b.poswin);
    sqlite3_bind_text(stmt,9,b.result.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,10,b.status.c_str(),-1,SQLITE_TRANSIENT);
    bool ok=(sqlite3_step(stmt)==SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}
vector<Bet> Database::getUserBets(const string& username)
{
    vector<Bet> out;

    const char* sql =
        "SELECT id, league, team1, team2, bet_type, odds, stake, poswin, result, status "
        "FROM bets WHERE username = ?";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Bet b;

        b.id       = sqlite3_column_int(stmt, 0);
        b.username = username;
        b.league   = (const char*)sqlite3_column_text(stmt, 1);
        b.team1    = (const char*)sqlite3_column_text(stmt, 2);
        b.team2    = (const char*)sqlite3_column_text(stmt, 3);
        b.bet_type = (const char*)sqlite3_column_text(stmt, 4);
        b.odds     = sqlite3_column_double(stmt, 5);
        b.stake    = sqlite3_column_double(stmt, 6);
        b.poswin   = sqlite3_column_double(stmt, 7);
        b.result   = (const char*)sqlite3_column_text(stmt, 8);
        b.status   = (const char*)sqlite3_column_text(stmt, 9);

        out.push_back(b);
    }

    sqlite3_finalize(stmt);
    return out;
}
bool Database::updateBetStatus(int betID,const string& status)
{
    const char* sql = "UPDATE bets SET status=? WHERE id=?";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,status.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,2,betID);
    bool ok=(sqlite3_step(stmt)==SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}
bool Database::updateBetResult(int betID,const string& result)
{
    const char* sql = "UPDATE bets SET result=? WHERE id=?";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,result.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,2,betID);
    bool ok=(sqlite3_step(stmt)==SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}
vector <Bet> Database::getPendingBets(const string& league)
{
    vector <Bet> out;
    const char* sql="SELECT id,username,league,team1, team2,bet_type, odds,stake, poswin FROM bets WHERE league=? AND status ='PENDING'";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,league.c_str(),-1,SQLITE_TRANSIENT);

    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        Bet b;
        b.id=sqlite3_column_int(stmt,0);
        b.username=(const char*)sqlite3_column_text(stmt,1);
        b.league=(const char*)sqlite3_column_text(stmt,2);
        b.team1=(const char*)sqlite3_column_text(stmt,3);
        b.team2=(const char*)sqlite3_column_text(stmt,4);
        b.bet_type=(const char*)sqlite3_column_text(stmt,5);
        b.odds=sqlite3_column_double(stmt,6);
        b.stake=sqlite3_column_double(stmt,7);
        b.poswin=sqlite3_column_double(stmt,8);
        b.status="PENDING";
        b.result="";
        out.push_back(b);
    }
    sqlite3_finalize(stmt);
    return out;
}
bool Database::updateMatchResult(int matchID, const string& result)
{
    const char* sql= "UPDATE matches SET result =? WHERE id =?";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,result.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,2,matchID);
    bool ok =(sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return ok;
}
vector <MatchEvent> Database::getMatchesID(const string& league)
{
    vector<MatchEvent> out;

    const char* sql ="SELECT id,team1,team2, odds1,oddsX,odds2,result FROM matches WHERE league=?";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, league.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        MatchEvent m;

        m.id=sqlite3_column_int(stmt,0);
        m.team1=(const char*)sqlite3_column_text(stmt,1);
        m.team2=(const char*)sqlite3_column_text(stmt,2);
        m.odds1=sqlite3_column_double(stmt,3);
        m.oddsX=sqlite3_column_double(stmt,4);
        m.odds2=sqlite3_column_double(stmt,5);
        m.result=(const char*)sqlite3_column_text(stmt,6);
        out.push_back(m);

        out.push_back(m);
    }

    sqlite3_finalize(stmt);
    return out;
}

