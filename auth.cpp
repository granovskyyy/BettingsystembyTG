#include <iostream>
#include <string.h>
#include <conio.h> //to secure passwords 

#include "auth.h"

Authenication::Authenication(vector <User>& u): users(u){}; //constructor for authenication with vector of all users 
string Authenication::HiddenPWD() //function to display passwords in secured way
{
    string password;
    char c;
    while((c=_getch())!='\r') //enter
    {
        if(c=='\b')
        {
            if(!password.empty())
            {
                cout<<"\b \b"; //backspace 
                password.pop_back();
            }

        }
        else
        {
            password +=c; //password changed to stars
            cout<<"*";
        }
    }
    cout<<endl;
    return password;
}
void Authenication::RegisterUser() //registering new user 
{
    string login, password;
    double balance;
    bool takenLogin;
    cout<<"Register on BetPlanet"<<endl;
    do
    {
        takenLogin=false;    //checking if login is taken (no same logins in database)
        cout<<"Enter nickname "<<endl;
        getline(cin>>ws,login);
        for(const User&u:users)
        {
            if(u.getUsername()==login)
            {
                cout<<"This nickname is already taken or you are registred"<<endl;
                takenLogin=true;
                break;
                
            }
        }
    }while(takenLogin);
      

        bool ValidPWD=false;
        while(!ValidPWD)
        {
            cout<<"Enter password "<<endl;
            cout<<"Your password must be: \n"
            "->at least 8 digit long \n"
            "->at least one number "<<endl;
            password=HiddenPWD();
            if(password.length()<8)
            {
                cout<<"Password too short"<<endl;
                continue;
            }
            bool hasDigit=false;
            for(char c:password)
            {
                
                if(isdigit(c))
                {
                hasDigit=true;
                }
            }
            if(!hasDigit)
            {
                cout<<"Password must contain at least one number"<<endl;
                continue;
            }
            ValidPWD=true;
        };

    User user1(login,password,balance);
    users.push_back(user1); //adding new user to data base 
    cout<<"Welcome on BetPlanet!"<<endl;

  
}
User Authenication::LoginSystem() //logging to system 
{   
    string login, password;
    double balance;
    
    while(true)
    {
        cout<<"Login: "<<endl;
        getline(cin>>ws,login);
        bool founduser=false; //to check if user is found in database
        User logged("","",0);
        for(User i:users) //looking for user in database 
        {
            if(i.getUsername()==login)
            {
                founduser=true;
                logged=i;
                break;
            }
        }
        if(!founduser)
        {
            cout<<"No user with these data"<<endl;
            break;
        }
        int pwdcount=0;
        while(pwdcount<5)
        {
            cout<<"Password"<<endl;
            password=HiddenPWD();
            if(logged.getPassword()==password)
            {
                cout<<"Login successfully"<<endl;
                return logged;
            }
            else
            {
                pwdcount++;
                cout<<"Wrong password. Try again"<<endl;
            };
            
        }
        cout<<"Too many attempts of logging in"<<endl; 
        break;
    }
    return User("","",0);
}
