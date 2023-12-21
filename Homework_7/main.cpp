#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "fighter.h"
#include <set>
#include <algorithm>

//You may add additional typedefs, includes, etc. up here

//This is the only array you are allowed to have in your program.
const std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

//Feel free to put forward declarations here

using namespace std;
// Function responsible for processing all data from frame_data files
void text_parser_database(char* &file_name,map <string,Fighter> &storage, set<string> &second_storage) {
	//Opening and reading file with getline
	ifstream file;
	file.open(file_name);
	string current_line;
	int count = 0;
	while (getline (file, current_line)) {
		count = count + 1;
		// Skip first line of file due to frame_data file format
		if(count == 1) {
			continue;
		}
		string temp_str;
		// Loops through current line
		for (unsigned int i = 0; i < current_line.size(); i++) {
		// Extracts and organizes data from file into simpler format
		// Check if character is a digit
        if (isdigit(current_line[i])) {
            string num_str;
            num_str += current_line[i];
            while (i < current_line.size() - 1 && isdigit(current_line[i + 1])) {
                num_str += current_line[i + 1];
                i++;
            }
            temp_str += " " + num_str;
        } 
		// Check if character is not a space and not a digit
		else if (current_line[i] != ' ' && isdigit(current_line[i]) == false) {
            temp_str += current_line[i];
        } 
		// Check if character is not a space but is a digit
		else if (current_line[i] != ' ' && isdigit(current_line[i])) {
            temp_str += " " + current_line[i];
        }
    }
		// Get the index of the first whitespace in the temp string
		int first_whitespace_loc = temp_str.find(" ");
		// Get name from frame_data by the location of whitespace
		string name = temp_str.substr(0,first_whitespace_loc);
		storage[name] = Fighter();
		storage[name].setName(name);
		second_storage.insert(name);
		// Erase everything up until and including found whitespace location for simplicity in repetition of this process
    	temp_str.erase(0,first_whitespace_loc+1);

		// Get the index of the second whitespace in the temp string and set the fighter's jab
		int second_whitespace_loc = temp_str.find(" ");
		storage[name].setJab(stoi(temp_str.substr(0,second_whitespace_loc)));
		temp_str.erase(0,second_whitespace_loc+1);

		// Get the index of the third whitespace in the temp string and set the fighter's forward tilt
		int third_whitespace_loc = temp_str.find(" ");
		storage[name].setForward_Tilt(stoi(temp_str.substr(0,third_whitespace_loc)));
		temp_str.erase(0,third_whitespace_loc+1);

		// Get the index of the fourth whitespace in the temp string and set the fighter's up tilt
		int fourth_whitespace_loc = temp_str.find(" ");
		storage[name].setUp_Tilt(stoi(temp_str.substr(0,fourth_whitespace_loc)));
		temp_str.erase(0,fourth_whitespace_loc+1);

		// Get the index of the fifth whitespace in the temp string and set the fighter's down tilt
		int fifth_whitespace_loc = temp_str.find(" ");
		storage[name].setDown_Tilt(stoi(temp_str.substr(0,fifth_whitespace_loc)));
		temp_str.erase(0,fifth_whitespace_loc+1);

		// Get the index of the sixth whitespace in the temp string and set the fighter's forward smash
		int sixth_whitespace_loc = temp_str.find(" ");
		storage[name].setForward_Smash(stoi(temp_str.substr(0,sixth_whitespace_loc)));
		temp_str.erase(0,sixth_whitespace_loc+1);

		// Get the index of the seventh whitespace in the temp string and set the fighter's up smash
		int seventh_whitespace_loc = temp_str.find(" ");
		storage[name].setUp_Smash(stoi(temp_str.substr(0,seventh_whitespace_loc)));
		temp_str.erase(0,seventh_whitespace_loc+1);

		// Get the index of the eighth whitespace in the temp string and set the fighter's down smash
		int eighth_whitespace_loc = temp_str.find(" ");
		storage[name].setDown_Smash(stoi(temp_str.substr(0,eighth_whitespace_loc)));

		temp_str.erase(0,eighth_whitespace_loc+1);

	}	
}

// Function responsible for parsing through each line in the queries file
void text_parser_queries(string &current_line, string &action_type, string &specifier1, string &specifier2) {

	// Finds first whitespace to obtain action type 
	int first_whitespace_loc = current_line.find(" ");
	action_type = current_line.substr(0,first_whitespace_loc);
    current_line.erase(0,first_whitespace_loc+1);

	// Finds second whitespace to obtain the first specifier
	int second_whitespace_loc = current_line.find(" ");
	specifier1 = current_line.substr(0,second_whitespace_loc);
	current_line.erase(0,second_whitespace_loc+1);

	// Finds third whitespace to obtain the second specifier
	int third_whitespace_loc = current_line.find(" ");
	specifier2 = current_line.substr(0,third_whitespace_loc);
	current_line.erase(0,third_whitespace_loc+1);


}

// Checks to see if the user inputted name is in the frame_data file 
bool valid_specifier1_checker(string specifier1, set <string> &second_storage) {
	int specifier_count = second_storage.count(specifier1);
	if (specifier_count != 0) {
		return true;
	}
	else {
		return false;
	}
}




int main(int argc, char** argv){
	// Argument parsing
	if(argc != 4){
		std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
		return -1;
	}

	std::ifstream dbfile(argv[1]);
	if(!dbfile){
		std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
	}

	std::ifstream infile(argv[2]);
	if(!infile){
		std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
	}

	std::ofstream outfile(argv[3]);
	if(!outfile){
		std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
	}
	///////Fill in the rest of main below:

	//Setting up variables to pass into frame_data parser function
	map <string,Fighter > storage;
	set<string> second_storage;
	text_parser_database(argv[1],storage,second_storage);
	// Opening query file in reading mode, and the user specified output file in writing mode
	ifstream file;
	file.open(argv[2]);
	ofstream writer_file;
	writer_file.open(argv[3]);
	string current_line;
	while (getline (file, current_line)) {
		//Setting up variables to pass into query parser function
		string action_type;
		string specifier1;
		string specifier2;
		text_parser_queries(current_line,action_type,specifier1,specifier2);
		// Checking what the current queries actiont type is
		if(action_type == "-q") {
			// Checking to see if input is valid using valid_specifier1_checker function
			if(valid_specifier1_checker(specifier1,second_storage) == false) {
				writer_file << "Invalid character name: " << specifier1 << endl;
				writer_file << endl;
				continue;
			}
			// Checking what statistic is to be outputted for user inputted character
			if (specifier2 == "jab") {
				writer_file <<  storage[specifier1].getName() << " " << specifier2 <<": "<<storage[specifier1].getJab() << endl;
			}
			else if (specifier2 == "forward-tilt") {
				writer_file << storage[specifier1].getName() << " " << specifier2 <<": "<< storage[specifier1].getForward_Tilt() << endl;
			} 
			else if (specifier2 == "up-tilt" ) {
				writer_file << storage[specifier1].getName() << " " << specifier2 <<": "<<storage[specifier1].getUp_Tilt() << endl;
			}
			else if (specifier2 == "down-tilt") {
				writer_file << storage[specifier1].getName() << " " << specifier2 <<": "<< storage[specifier1].getDown_Tilt() << endl;
			}
			else if (specifier2 == "forward-smash") {
				writer_file << storage[specifier1].getName() << " " << specifier2 <<": "<<storage[specifier1].getForward_Smash() << endl;
			}
			else if (specifier2 == "up-smash") {
				writer_file << storage[specifier1].getName() << " " << specifier2 <<": "<< storage[specifier1].getUp_Smash() << endl;
			}
			else if(specifier2 == "down-smash") {
				writer_file << storage[specifier1].getName() << " " << specifier2 <<": "<<storage[specifier1].getDown_Smash() << endl;
			}
			else if (specifier2 == "all") {
				writer_file <<  storage[specifier1].getName() << " " << "down-smash" <<": "<<storage[specifier1].getDown_Smash() << endl;
				writer_file <<  storage[specifier1].getName() << " " << "down-tilt" <<": "<< storage[specifier1].getDown_Tilt() << endl;
				writer_file <<  storage[specifier1].getName() << " " << "forward-smash" <<": "<<storage[specifier1].getForward_Smash() << endl;
				writer_file <<  storage[specifier1].getName() << " " << "forward-tilt" <<": "<< storage[specifier1].getForward_Tilt() << endl;
				writer_file <<  storage[specifier1].getName() << " " << "jab" <<": "<<storage[specifier1].getJab() << endl;
				writer_file <<  storage[specifier1].getName() << " " << "up-smash" <<": "<< storage[specifier1].getUp_Smash() << endl;
				writer_file <<  storage[specifier1].getName() << " " << "up-tilt" <<": "<<storage[specifier1].getUp_Tilt() << endl;
				
			}
			// Ensuring that if an invalid move is given this error message is printed
			else {
				writer_file << "Invalid move name: " << specifier2 <<  endl;
			}
			writer_file << endl;
		}
		else if (action_type == "-f") {
			// Setting up a temporary map to gather all character frame data for a user specified move 
			map <string, int> frames;
			map<string, Fighter>::iterator it;
			// A counter variable is added to ensure that when an invalid move name is present, the function does not output
			int count = 0;
			//Looping through a map with the fighter name as the key and fighter object as the value
			for (it = storage.begin(); it != storage.end(); ++it) {
				//Checking which move the user specified
				if(specifier1 == "jab") {
					frames[((*it).second).getName()] = ((*it).second).getJab();
				}
				else if(specifier1 == "forward-tilt") {
					frames[((*it).second).getName()] = ((*it).second).getForward_Tilt();
				}
				else if (specifier1== "up-tilt") {
					frames[((*it).second).getName()] = ((*it).second).getUp_Tilt();
				}
				else if (specifier1 == "down-tilt") {
					frames[((*it).second).getName()] = ((*it).second).getDown_Tilt();
				}
				else if (specifier1 == "forward-smash") {
					frames[((*it).second).getName()] = ((*it).second).getForward_Smash();
				}
				else if (specifier1 == "up-smash") {
					frames[((*it).second).getName()] = ((*it).second).getUp_Smash();
				}
				else if (specifier1 == "down-smash") {
					frames[((*it).second).getName()] = ((*it).second).getDown_Smash();
				}
				else {
					writer_file << "Invalid move name: " << specifier2 <<  endl;
					count = count + 1;
					continue;
				}
				}
			//Creating a new map which sorts all the elements in the previously created map
			// A set of strings is used as the key to ensure characters with the same frame data are not lost
			if (count == 0) {
				map<int, set<string> > sorted_frames;
				for (map<string, int>::iterator it = frames.begin(); it != frames.end(); ++it) {
					sorted_frames[it->second].insert(it->first);
				}
				int counter = 0;
				int max_iterations = stoi(specifier2);
				writer_file << "-f " << specifier1 << " " << specifier2 << endl;
				//Outputting results 
				for (map<int, set<string> >::iterator it = sorted_frames.begin(); it != sorted_frames.end() && counter < max_iterations; ++it) {
					std::set<string>::iterator it2;
					for (it2 = it->second.begin(); it2 != it->second.end() && counter < max_iterations; ++it2) {
						counter++;
						writer_file << (*it2) << " " << it->first << endl;
						}
					}
				writer_file << endl;
				}
			
		}
		else if (action_type == "-s") {
			// Setting up a temporary map to gather all character frame data for a user specified move 
			map <string, int> frames;
			map<string, Fighter>::iterator it;
			// A counter variable is added to ensure that when an invalid move name is present, the function does not output
			int count = 0;
			// Once again looping through the map created via the frame_data parser function
			for (it = storage.begin(); it != storage.end(); ++it) {
				//Checking which move the user specified
				if(specifier1 == "jab") {
					frames[((*it).second).getName()] = ((*it).second).getJab();
				}
				else if(specifier1 == "forward-tilt") {
					frames[((*it).second).getName()] = ((*it).second).getForward_Tilt();
				}
				else if (specifier1== "up-tilt") {
					frames[((*it).second).getName()] = ((*it).second).getUp_Tilt();
				}
				else if (specifier1 == "down-tilt") {
					frames[((*it).second).getName()] = ((*it).second).getDown_Tilt();
				}
				else if (specifier1 == "forward-smash") {
					frames[((*it).second).getName()] = ((*it).second).getForward_Smash();
				}
				else if (specifier1 == "up-smash") {
					frames[((*it).second).getName()] = ((*it).second).getUp_Smash();
				}
				else if (specifier1 == "down-smash") {
					frames[((*it).second).getName()] = ((*it).second).getDown_Smash();
				}
				else {
					writer_file << "Invalid move name: " << specifier1 << "\n" << endl;
					count = count + 1;
					break;
				}
				}
			if (count == 0) {
				//Creating a new map which sorts all the elements in the previously created map
				// A set of strings is used as the key to ensure characters with the same frame data are not lost
				map<int, set<string> > sorted_frames;
				for (map<string, int>::iterator it = frames.begin(); it != frames.end(); ++it) {
					sorted_frames[it->second].insert(it->first);
				}
				int counter = 0;
				int max_iterations = stoi(specifier2);
				writer_file << "-s " << specifier1 << " " << specifier2 << endl;
				// Elements in the sorted map are iterated through backwards to get the slowest characters rather than the fastest
				for (map<int, set<string> >::iterator it = --sorted_frames.end(); it != sorted_frames.begin() && counter < max_iterations; --it) {
					std::set<string>::iterator it2;
					for (it2 = it->second.begin(); it2 != it->second.end() && counter < max_iterations; ++it2) {
						counter++;
						writer_file << (*it2) << " " << it->first << endl;
					}
					}
				writer_file << endl;
			}
			
		}	
		else if (action_type == "-d") {
			// Setting up a temporary map to gather all character frame data for a user specified move 
			map <string, int> frames;
			// A counter variable is added to ensure that when an invalid move name is present, the function does not output
			int count = 0;
			map<string, Fighter>::iterator it;
			// Looping through the map created via the frame_data parser function
			for (it = storage.begin(); it != storage.end(); ++it) {
				//Checking which move the user specified
				if(specifier1 == "jab") {
					frames[((*it).second).getName()] = ((*it).second).getJab();
				}
				else if(specifier1 == "forward-tilt") {
					frames[((*it).second).getName()] = ((*it).second).getForward_Tilt();
				}
				else if (specifier1== "up-tilt") {
					frames[((*it).second).getName()] = ((*it).second).getUp_Tilt();
				}
				else if (specifier1 == "down-tilt") {
					frames[((*it).second).getName()] = ((*it).second).getDown_Tilt();
				}
				else if (specifier1 == "forward-smash") {
					frames[((*it).second).getName()] = ((*it).second).getForward_Smash();
				}
				else if (specifier1 == "up-smash") {
					frames[((*it).second).getName()] = ((*it).second).getUp_Smash();
				}
				else if (specifier1 == "down-smash") {
					frames[((*it).second).getName()] = ((*it).second).getDown_Smash();
				}
				else {
					writer_file << "Invalid move name: " << specifier2 <<  endl;
					count = count + 1;
					continue;
				}
				}
				if(count == 0) {
					// Outputting results
					writer_file << "-d " << specifier1 << " " << specifier2 << endl;
					for (map<string, int>::iterator it = frames.begin(); it != frames.end(); ++it) {
						if(it->second == stoi(specifier2)) {
							writer_file << it->first<< endl;
						}
					}
					writer_file << endl;
				}
		}
	}





















	return 0;
}
