#include "userprofile.h"
#include <string>
using namespace std;

User::User(string u, string p, double b):username(u),password(p), balance(b) {
};
double User::getBalance() const {return balance;}
string User::getPassword() const {return password;}
string User::getUsername() const {return username;}
void User::SetBalance(double b) { balance=b;}

