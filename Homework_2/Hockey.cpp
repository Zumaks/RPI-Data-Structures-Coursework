#include "Hockey1.h"
#include <iostream>
#include <fstream>

Hockey::Hockey(vector < vector < string> > Games) {
    all_games = Games;
}


void Hockey::data_transformation(vector < vector < string> > games) {
// This class function is responsible for transforming the 2d string games containing an exact copy of the file in string form into
// a 3d vector of all the most important statistics and points of data required.
    vector < vector < vector < string> > >transformed_games;
    vector < vector < string> > current_game;
    for(int i = 0; i < games.size(); i++){

        vector <string> temp_vec1;
        temp_vec1.push_back(games[i][0]);
        current_game.push_back(temp_vec1);
        int at_location = games[i][1].find("at");
        string away = games[i][1].substr(at_location + 2);
        away.erase(remove_if(away.begin(), away.end(), ::isspace),away.end());
        string home = games[i][1].substr(0,at_location);
        home.erase(remove_if(home.begin(), home.end(), ::isspace),home.end());
        vector<string> temp_vec2;
        temp_vec2.push_back(home);
        temp_vec2.push_back(away);
        current_game.push_back(temp_vec2);
        vector<string> goals;
        vector <string> penalties;
        vector <string> assisters;
        vector <string> final_score;
        for(int z = 2; z < games[i].size(); z++){
            // The keywords of each action line from the file are analyzed in order to determine what the necessary actions are
            if (games[i][z].substr(0,7) == "PERIOD"){
                continue;
            }
            else if(games[i][z].substr(0,6) == "FINAL") {
              games[i][z+1].erase(remove_if( games[i][z+1].begin(),  games[i][z+1].end(), ::isspace), games[i][z+1].end());
              char away_team_score_char = games[i][z + 1][games[i][z + 1].length() - 1] ;
              char home_team_score_char = games[i][z + 2][games[i][z + 2].length() - 1];
              string away_team_score;
              away_team_score += away_team_score_char;
              string home_team_score;
              home_team_score += home_team_score_char;
              final_score.push_back(away_team_score);
              final_score.push_back(home_team_score);
              break;
            }
            else if(games[i][z].substr(0,9) == "OVERTIME"){
                continue;
            }
            else {
                // The Data Transformation is done by slowly erasing each part of the string while saving most important information
                int first_space_loc =  games[i][z].find(" ");
                games[i][z].erase(0,first_space_loc+1);
                int second_space_loc =  games[i][z].find(" ");
                string action_team_name = games[i][z].substr(0,second_space_loc);
                games[i][z].erase(0,second_space_loc+1);
                int third_space_loc =  games[i][z].find(" ");
                if(games[i][z].substr(0,third_space_loc) == "goal") {
                    games[i][z].erase(0,third_space_loc+1);
                    int fourth_space_loc = games[i][z].find(" ");
                    string player_name = action_team_name + " " + games[i][z].substr(0,fourth_space_loc);
                    goals.push_back(player_name);
                    int bracket_one_loc = games[i][z].find("( ");
                    games[i][z].erase(0,bracket_one_loc+2);
                    int bracket_two_loc = games[i][z].find(" )");
                    games[i][z].erase(bracket_two_loc,games[i][z].length());
                    int name_dividing_space_loc = games[i][z].find(" ");
                    if (games[i][z].find_first_not_of(' ') != std::string::npos && isspace(games[i][z][name_dividing_space_loc+1]) == false) {
                      string only_assister = action_team_name + " " + games[i][z];
                      assisters.push_back(only_assister);
                    }
                    else if (games[i][z].find_first_not_of(' ') == std::string::npos) {
                        continue;
                    }
                    else {
                      string assister_one = action_team_name + " " + games[i][z].substr(0,name_dividing_space_loc);
                      assisters.push_back(assister_one);
                      string assister_two = action_team_name + " " + games[i][z].substr(name_dividing_space_loc+1);
                      assisters.push_back(assister_two);
                    }
                }
                else if (games[i][z].substr(0,third_space_loc) == "penalty") {
                    games[i][z].erase(0,third_space_loc+1);
                    int fourth_space_loc = games[i][z].find(" ");
                    string player_pen_name = action_team_name + " " + games[i][z].substr(0,fourth_space_loc);
                    penalties.push_back(player_pen_name);
                }

            }
        }
    // The processed data is appended into current games a vector of vectors containing all information from the current game being 
    // analayzed.
    current_game.push_back(goals);
    current_game.push_back(penalties);
    current_game.push_back(assisters);
    current_game.push_back(final_score);
    transformed_games.push_back(current_game);
    current_game.clear();
    }
    processed_data = transformed_games;
}
vector < vector < vector < string> > > Hockey::getData() {
    return processed_data;
}