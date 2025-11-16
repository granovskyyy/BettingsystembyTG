#include "userprofile.h"
#include <string>
using namespace std;

User::User(string u, string p, string m):username(u),password(p), email(m) {
    u=username;
    p=password;
    m=email;
};
string User::getEmail() const {return email;}
string User::getPassword() const {return password;}
string User::getUsername() const {return username;}


