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
vector <MatchEvent> Fixtures::Matchmaking(vector <string> teams)
{
    srand(unsigned(time(0)));
    vector <MatchEvent> matches;
    shuffle(teams.begin(), teams.end(), mt19937(random_device()())); //randomizing teams 
    for(int i=0;i<teams.size();i+=2)
    {
        if(i+1<teams.size())
        {
            matches.push_back(createMatch(teams[i],teams[i+1]));
        }    
    }
    return matches;
}
MatchEvent Fixtures::createMatch(const string& t1, const string& t2)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(1.20,7.00);
    double o1=dist(gen);
    double o2=dist(gen);
    double oX=(o1+o2)/2+0.5;

    MatchEvent ev;
    ev.team1=t1;
    ev.team2=t2;
    ev.odds1=o1;
    ev.odds2=o2;
    ev.oddsX=oX;
    return ev;
}
