#include <iostream>
#include "fixtures.h"

using namespace std;


vector <string> Fixtures::SaveTeams(fstream &filename)
{
    
    vector  <string> teams;
    string line;
    while(getline(filename,line)) //saving teams from file to vector 
    {
        if(!line.empty())
        {
            teams.push_back(line);
        }
    }
    filename.close();
    return teams;
}
vector <pair<string,string>> Fixtures::Matchmaking(vector <string> teams)
{
    srand(unsigned(time(0)));
    vector <pair<string,string>> matches;
    shuffle(teams.begin(), teams.end(), mt19937(random_device()()));
    for(int i=0;i<teams.size();i+=2)
    {
        if(i+1<teams.size())
        {
            matches.push_back({teams[i],teams[i+1]});
        }    
    }
    return matches;
}
