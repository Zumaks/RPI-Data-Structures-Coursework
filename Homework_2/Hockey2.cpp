#include "Hockey2.h"
#include <vector> 
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
Hockey2::Hockey2(vector < vector < vector < string> > > data) {
    stored_processed_data = data;
}
 void Hockey2::team_stats() {
    // team_stats is where the team_stats are calculated
    vector <string> team_name;
    vector < vector <float> > team_stats;
    vector <float> empty_vec ;
    for(int i = 0; i < 6; i++) {
        empty_vec.push_back(0.0);
    }
    // Note : Each 0.0 corresponds to W L T Win% Goals Penalties
    for(int i =0; i < stored_processed_data.size(); i++) {
        // Checking to see if team name already was added to the vector
        if (count(team_name.begin(), team_name.end(), stored_processed_data[i][1][0]) == 0){
            team_name.push_back(stored_processed_data[i][1][0]);
            team_stats.push_back(empty_vec);
            
        }
        if(count(team_name.begin(), team_name.end(), stored_processed_data[i][1][1]) == 0) {
            team_name.push_back(stored_processed_data[i][1][1]);
            team_stats.push_back(empty_vec);
        }
        if(stored_processed_data[i][5][0] < stored_processed_data[i][5][1]) {
            for(int z = 0; z < team_name.size(); z++) {
                if (team_name[z] == stored_processed_data[i][1][1]) {
                    
                }
            }
            // Finding corresponding location of team name in order to determine which position to update the stats, in variable team_stats
            auto it = find(team_name.begin(), team_name.end(), stored_processed_data[i][1][1]);
            int winning_team_loc = it - team_name.begin();
            auto it2 = find(team_name.begin(), team_name.end(), stored_processed_data[i][1][0]);
            int losing_team_loc = it2 - team_name.begin();
            team_stats[winning_team_loc][0] += 1;
            team_stats[winning_team_loc][4] += stoi(stored_processed_data[i][5][1]);

            team_stats[losing_team_loc][1] += 1;
            team_stats[losing_team_loc][4] += stoi(stored_processed_data[i][5][0]);
            
        }
        else if (stored_processed_data[i][5][0] > stored_processed_data[i][5][1]) {
            // Multiple versions to handle all scenarios for games
            auto it = find(team_name.begin(), team_name.end(), stored_processed_data[i][1][0]);
            int winning_team_loc = it - team_name.begin();
            auto it2 = find(team_name.begin(), team_name.end(), stored_processed_data[i][1][1]);
            int losing_team_loc = it2 - team_name.begin();
            team_stats[winning_team_loc][0] += 1;
            team_stats[winning_team_loc][4] += stoi(stored_processed_data[i][5][0]);

            team_stats[losing_team_loc][1] += 1;
            team_stats[losing_team_loc][4] += stoi(stored_processed_data[i][5][1]);
            

        }
        else {
            auto it = find(team_name.begin(), team_name.end(), stored_processed_data[i][1][0]);
            int team_one_loc = it - team_name.begin();
            auto it2 = find(team_name.begin(), team_name.end(), stored_processed_data[i][1][1]);
            int team_two_loc = it2 - team_name.begin();
            team_stats[team_one_loc][2] += 1;
            team_stats[team_one_loc][4] += stoi(stored_processed_data[i][5][0]);

            team_stats[team_two_loc][2] += 1;
            team_stats[team_two_loc][4] += stoi(stored_processed_data[i][5][1]);
            
        }
        //Penalty Total Calculation
        for(int z = 0; z < stored_processed_data[i][3].size(); z++) {
            int delimeter_loc = stored_processed_data[i][3][z].find(" ");
            string pen_team_name = stored_processed_data[i][3][z].substr(0,delimeter_loc);
            auto it = find(team_name.begin(), team_name.end(), pen_team_name);
            int team_pen_loc = it - team_name.begin();

            team_stats[team_pen_loc][5] += 1;

        }
        // Win% Calculation
        for (int z = 0; z < team_stats.size();z++) {
            team_stats[z][3] = (team_stats[z][0] + (0.5 * team_stats[z][2])) / (team_stats[z][0] + team_stats[z][2] + team_stats[z][1]);
        }
    team_names = team_name;
    team_statistics = team_stats;

}
 }
vector <vector <float> > Hockey2::getTeam_Statistics() {
    return team_statistics;
}

vector <string> Hockey2::getTeam_Names() {
    return team_names;
}
void Hockey2::player_stats() {
    // This class function is responsible for calculating the player stats
    vector < string > player_name;
    vector <string> player_team;
    vector < vector <float> > player_stats;
    vector <float> empty_vec ;
    for(int i = 0; i < 3; i++) {
        empty_vec.push_back(0.0);
    }

    // Note : Each 0 corresponds to Goals Assists Penalties
    for(int i =0; i < stored_processed_data.size(); i++) {
            //Similairly to team_stats the 3d vector is broken down into its components to retrieve the goals, assits and penalties
            // categories and in order to process this data in a manner which can later be sorted by another class function.
            // Here we calcualate the goals scored by each player
            for(int z = 0; z < stored_processed_data[i][2].size(); z++){
                vector <string> temp_vec;
                int bracket_one_loc = stored_processed_data[i][2][z].find(" ");
                string player_team_name = stored_processed_data[i][2][z].substr(0,bracket_one_loc);
                stored_processed_data[i][2][z].erase(0,bracket_one_loc+1);
                if (count(player_name.begin(), player_name.end(), stored_processed_data[i][2][z]) == 0){
                    player_team.push_back(player_team_name);
                    player_name.push_back(stored_processed_data[i][2][z]);
                    player_stats.push_back(empty_vec);
                    player_stats[player_stats.size()-1][0] += 1;
                }
                else {
                    auto it = find(player_name.begin(), player_name.end(), stored_processed_data[i][2][z]);
                    int player_loc = it - player_name.begin();
                    player_stats[player_loc][0] += 1;
                }
            }


            // This portion is responsible for the penalties
            for(int z = 0; z < stored_processed_data[i][3].size(); z++){
                vector <string> temp_vec;
                int bracket_one_loc = stored_processed_data[i][3][z].find(" ");
                string player_team_name = stored_processed_data[i][3][z].substr(0,bracket_one_loc);
                stored_processed_data[i][3][z].erase(0,bracket_one_loc+1);
                if (count(player_name.begin(), player_name.end(), stored_processed_data[i][3][z]) == 0){
                    player_team.push_back(player_team_name);
                    player_name.push_back(stored_processed_data[i][3][z]);
                    player_stats.push_back(empty_vec);
                    player_stats[player_stats.size()-1][2] += 1;
                }
                else {
                    auto it = find(player_name.begin(), player_name.end(), stored_processed_data[i][3][z]);
                    int player_loc = it - player_name.begin();
                    player_stats[player_loc][2] += 1;
                }
            }
            // And lastly here I calculate the assists.
            for(int z = 0; z < stored_processed_data[i][4].size(); z++){
                vector <string> temp_vec;
                int bracket_one_loc = stored_processed_data[i][4][z].find(" ");
                string player_team_name = stored_processed_data[i][4][z].substr(0,bracket_one_loc);
                stored_processed_data[i][4][z].erase(0,bracket_one_loc+1);
                int bracket_two_loc = stored_processed_data[i][4][z].find(" ");
                if (isalpha(stored_processed_data[i][4][z][stored_processed_data[i][4][z].find(" ") + 1]) ){
                    vector <string> temp_vec;
                    temp_vec.push_back(stored_processed_data[i][4][z].substr(0,bracket_two_loc));
                    stored_processed_data[i][4][z].erase(0,bracket_two_loc+1);

                    temp_vec.push_back(stored_processed_data[i][4][z]);
                    for (int x = 0; x < 2; x++) {
                        string cur_player = temp_vec[x];
                        if (count(player_name.begin(), player_name.end(),cur_player) == 0){
                            player_team.push_back(player_team_name);
                            player_name.push_back(cur_player);
                            player_stats.push_back(empty_vec);
                            player_stats[player_stats.size()-1][1] += 1;
                        }
                        else {
                            auto it = find(player_name.begin(), player_name.end(), cur_player);
                            int player_loc = it - player_name.begin();
                            player_stats[player_loc][1] += 1;
                }
                    }

                }
                else {
                    string cur_player = stored_processed_data[i][4][z].substr(0,stored_processed_data[i][4][z].find(" "));
                    if (count(player_name.begin(), player_name.end(), cur_player) == 0){
                        player_team.push_back(player_team_name);
                        player_name.push_back(cur_player);
                        player_stats.push_back(empty_vec);
                        player_stats[player_stats.size()-1][1] += 1;
                        }
                    else {
                        auto it = find(player_name.begin(), player_name.end(), cur_player);
                        int player_loc = it - player_name.begin();
                        player_stats[player_loc][1] += 1;
                }
                }
            }

    }
    player_names = player_name;
    player_teams = player_team;
    player_statistics = player_stats;
}
vector <vector <float> > Hockey2::getPlayer_Statistics() {
    return player_statistics;
}

vector <string> Hockey2::getPlayer_Names() {
    return player_names;
}

vector <string> Hockey2::getPlayer_Teams() {
    return player_teams;
}


vector<float> Hockey2::custom_stats() {
    // Effieciency rating custom stat
    vector <float> player_efficiency;
    for(int i = 0; i < player_statistics.size(); i++) {
        player_efficiency.push_back(player_statistics[i][0] + player_statistics[i][1] - player_statistics[i][2]);
    }
    return player_efficiency;
}