#include <iostream>
#include <string.h> 
//to secure passwords
#include "auth.h"
#if defined(_WIN64) 
    int Authenication::mygetch()
    {
        return _getch();
    }
    string Authenication::HiddenPWD() //function to display passwords in secured way
    {
        string password;
        char c;
        while((c=mygetch())!='\r') //enter
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
#else
    int Authenication::mygetch() //special getch function for linux/macos users 
    {
        int ch;
        struct termios old_settings, new_settings;
        tcgetattr(STDIN_FILENO, &old_settings);
        new_settings = old_settings;
        new_settings.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
        return ch;

    }
    string Authenication::HiddenPWD() //function to display passwords in secured way
    {
        string password;
        char c;
        while((c=mygetch())!='\n') //enter
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
#endif
Authenication::Authenication(vector <User>& u, Database& database): users(u), db(database) {}; //constructor for authenication with vector of all users 
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
        string temppwd;
        double tmpBalance;
        if(db.getUser(login,temppwd,tmpBalance))
        {
            cout<<"This nickname is already taken or you are registred"<<endl;
            takenLogin=true;
        }
        else
        {
            break;
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
    unsigned int securePWD=hashPWD(password);
    db.addUser(login,to_string(securePWD),balance);
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
        string storedpwd;
        double userbalance;
        if(!db.getUser(login,storedpwd,userbalance))
        {
            cout<<"No user with this nickname"<<endl;
            return User("","",0);
        }
        int pwdcount=0;
        while(pwdcount<5)
        {
            cout<<"Password"<<endl;
            password=HiddenPWD();
            unsigned int securedPWD=hashPWD(password);
            if(to_string(securedPWD)==storedpwd)
            {
                cout<<"Login successfully"<<endl;
                return User(login,password,userbalance);
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
unsigned int Authenication::hashPWD(const string& password)
{
    int result=0;
    for (char c:password)
    {
        result += c+(result<<3) + (result<<9) -result;

    }
    return result;
}
