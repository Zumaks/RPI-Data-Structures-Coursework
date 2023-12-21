#ifndef _player_h_
#define _player_h_
#include <string> 
#include <vector>
using namespace std;


class Player {
    public:
    const string getPlayer_Name() {return player_name;}
    const string getStr_Team_Name() {return str_team_name;}
    int getGoals() {return goals;}
    int getPenalties() {return penalties;}
    int getAssists(){return assists;}
    void setStr_Team_Name(string str_team_name1);
    void setPlayer_Name(string player_name1);
    void setPenalties(int penalties1);
    void setGoals(int goals1);
    void setAssists(int assists1);
    



    private:
    string player_name;
    string str_team_name;
    int goals;
    int penalties;
    int assists;
};
// bool sort_players(Player &a, Player &b) {
//     return (((a.getGoals() + a.getAssists())> (b.getGoals() + b.getGoals())) || ((a.getGoals() + a.getAssists()) == (b.getGoals() + b.getGoals()) && (a.getPenalties() < b.getPenalties()))
//      || ((a.getGoals() + a.getAssists()) == (b.getGoals() + b.getGoals()) && (a.getPenalties() == b.getPenalties()) && (a.getPlayer_Name() > b.getPlayer_Name())));
// }
#endif