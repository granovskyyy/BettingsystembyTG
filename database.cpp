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
