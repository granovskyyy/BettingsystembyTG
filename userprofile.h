#pragma once
#include <string>
using namespace std;
class User 
{
    string username;
    string password;
    string email;
    public:
    User(string u, string p, string e); //creating new user 
    string getUsername() const;
    string getPassword() const; //getters for users data
    string getEmail() const;
};