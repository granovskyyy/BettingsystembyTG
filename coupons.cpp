#include <iostream>
#include "coupons.h"

using namespace std;

vector <string> Coupons::SaveTeams()
{
    vector  <string> teams;
    fstream file("/Users/tomekgranowski/BettingsystembyTG/teams.txt"); //your file path
    string line;
    while(getline(file,line))
    {
        if(!line.empty())
        {
            teams.push_back(line);
        }

    }
    file.close();
    return teams;
}