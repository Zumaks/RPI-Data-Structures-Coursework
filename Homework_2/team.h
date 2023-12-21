#ifndef _team_h_
#define _team_h_
#include <string> 
#include <vector>
using namespace std;
class team {
    public:
    const string getStr_Team_Name() {return str_team_name;}
    int getWin() {return win;}
    int getLoss() {return loss;}
    int getTie() {return tie;}
    float getWinper() {return winper;}
    int getGoals() {return goals;}
    int getPenalties() {return penalties;}


    void setStr_Team_Name(string str_team_name1);
    void setWin(int win1); 
    void setLoss(int loss1); 
    void setTie(int tie1);
    void setWinper(float winper1);
    void setGoals(int goals1);
    void setPenalties(int penalties1);
    
    private:
    string str_team_name;
    int win;
    int loss;
    int tie;
    float winper;
    int goals;
    int penalties;


};

// bool sort_teams(team &a, team &b) {
//     return ((a.getWinper() > b.getWinper()) || ((a.getWinper() == b.getWinper()) && (a.getGoals()> b.getGoals())) || 
//     ((a.getWinper() == b.getWinper()) && (a.getGoals() == b.getGoals()) && (a.getStr_Team_Name()> b.getStr_Team_Name())));
// }
#endif