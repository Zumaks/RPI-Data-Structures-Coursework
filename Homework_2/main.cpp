#include <iostream> 
#include <string>
#include <fstream> 
#include <vector>
#include "Hockey1.h"
#include "Hockey2.h"
#include <fstream>
#include "team.h"
#include "player.h"
#include <algorithm>
#include <stdio.h>
#include <string.h>

// #include "Hockey2.h"
using namespace std;

bool sort_teams(team &a, team &b) {
  // Function responsible for sorting through the vector of teams
    return ((a.getWinper() > b.getWinper()) || ((a.getWinper() == b.getWinper()) && (a.getGoals()> b.getGoals())) || 
    ((a.getWinper() == b.getWinper()) && (a.getGoals() == b.getGoals()) && (a.getStr_Team_Name() < b.getStr_Team_Name())));
}

bool sort_players(Player &a, Player &b) {
  // Function responsible for sorting through the vector of players
    return (((a.getGoals() + a.getAssists())> (b.getGoals() + b.getAssists())) || ((a.getGoals() + a.getAssists()) == (b.getGoals() + b.getAssists()) && (a.getPenalties() < b.getPenalties()))
     || ((a.getGoals() + a.getAssists()) == (b.getGoals() + b.getAssists()) && (a.getPenalties() == b.getPenalties()) && (a.getPlayer_Name() < b.getPlayer_Name())));
}


vector < vector < string> > text_parser(char* text_name) {
  // Function responsible for parsing the input text into a 2d vector of strings matching the format of the original file
  ifstream text_input;
    text_input.open(text_name);
    string line;
    vector <string> lines; 
    vector < vector < string> > all_games;
    
   while (getline (text_input, line)) {
        lines.push_back(line);
        if(line == ""){
          all_games.push_back(lines);
          lines.clear();
        }
    }
    return all_games;
}


void Writer(vector <team> sorted_team, vector <Player> player_names, vector <float> custom_stats, vector<string> player_names2,char* name, char* option) {
  // Function is responsible for iterating through vector of classes depending on which stat type was chosen by the user and outputting
  // it all into the user specified file
  ofstream myfile;
  myfile.open(name);

  if(strcmp("--team_stats",option) == 0) {
    myfile << "Team Name     W   L   T   Win%  Goals  Penalties" << endl;
    for(int i = 0; i < sorted_team.size(); i++) {
      myfile << sorted_team[i].getStr_Team_Name() << "   ";
      myfile << sorted_team[i].getWin() << "   ";
      myfile << sorted_team[i].getLoss() << "   ";
      myfile << sorted_team[i].getTie() << "   ";
      myfile << sorted_team[i].getWinper() << "   ";
      myfile << sorted_team[i].getGoals() << "   ";
      myfile << sorted_team[i].getPenalties() << endl;
    }
}
  else if(strcmp("--player_stats",option) == 0) {
    myfile << "Player Name         Team         Goals  Assists  Penalties" << endl;

    for(int i = 0; i < player_names.size(); i++) {
      myfile << player_names[i].getPlayer_Name() << "   ";
      myfile << player_names[i].getStr_Team_Name() << "   ";
      myfile << player_names[i].getGoals() << "   ";
      myfile << player_names[i].getAssists() << "   ";
      myfile << player_names[i].getPenalties() << endl;
    }
  
  }
  else if (strcmp("--custom_stats",option) == 0) {
    myfile << "Player Name      Efficiency" << endl;
    for(int i = 0; i < custom_stats.size(); i++) {
      myfile << player_names2[i] << "    " <<  custom_stats[i] << endl;

    }
  }
  myfile.close();
}



int main(int argc, char* argv[]) {
  vector < vector < string> > all_games = text_parser(argv[1]);
  Hockey Games(all_games);
  Games.data_transformation(all_games);
  vector < vector < vector < string> > > vec3 = Games.getData();
  
  Hockey2 processing(vec3);
  processing.team_stats();
  vector <string> team_names = processing.getTeam_Names();
  vector <vector <float> > team_stats = processing.getTeam_Statistics();
  // Setting up the class vector by feeding it all parts of the processed team_stats
  vector <team> teams;
  for(int i =0; i < team_stats.size(); i++) {
    team a;
    a.setStr_Team_Name(team_names[i]);
    a.setWin(team_stats[i][0]);
    a.setLoss(team_stats[i][1]);
    a.setTie(team_stats[i][2]);
    a.setWinper(team_stats[i][3]);
    a.setGoals(team_stats[i][4]);
    a.setPenalties(team_stats[i][5]);
    teams.push_back(a);
  }

  sort(teams.begin(),teams.end(),sort_teams);

  processing.player_stats();
  vector <string> player_names = processing.getPlayer_Names();
  vector <string> player_teams = processing.getPlayer_Teams();
  vector <vector <float> > player_stats = processing.getPlayer_Statistics();
  vector <float> custom_stats = processing.custom_stats();
    // Setting up the player class vector by feeding it all parts of the processed player_stats
  vector <Player> players;
  for(int i =0; i < player_stats.size(); i++) {
    Player a;
    a.setPlayer_Name(player_names[i]);
    a.setStr_Team_Name(player_teams[i]);
    a.setGoals(player_stats[i][0]);
    a.setAssists(player_stats[i][1]);
    a.setPenalties(player_stats[i][2]);
    players.push_back(a);
  }
  sort(players.begin(),players.end(),sort_players);

  


  Writer(teams,players,custom_stats,player_names,argv[2],argv[3]);



}