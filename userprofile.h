#pragma once
#include <string>
using namespace std;
class User 
{
    string username;
    string password;
    double balance;
    public:
    User(string u, string p, double b = 0.0); //creating new user 
    string getUsername() const;
    string getPassword() const; //getters for users data
    double getBalance() const;
    void SetBalance(double b);
};