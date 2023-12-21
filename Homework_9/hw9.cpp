#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "hashtable.h"
#include <set>
using namespace std;

// Function to parse input from standard input
void text_parser_input(int &kmer, vector <string> &queries, string &output_file, int &table_size, float &occupancy){
	string current_line;
	while (getline (cin, current_line)) {
        int first_whitespace_loc = current_line.find(" ");
        // Parse query line
        if (current_line.substr(0,first_whitespace_loc) == "query") {
            current_line.erase(0,first_whitespace_loc+1);
            string temp_str = "";
            int second_whitespace_loc = current_line.find(" ");
            temp_str = temp_str + current_line.substr(0,second_whitespace_loc);
            current_line.erase(0,second_whitespace_loc+1);
            temp_str = temp_str + current_line;
            queries.push_back(temp_str);
        }
        // Parse kmer line
        else if (current_line.substr(0,first_whitespace_loc) == "kmer"){
            current_line.erase(0,first_whitespace_loc+1);
            kmer = stoi(current_line);
        }
        // Parse genome line
        else if (current_line.substr(0,first_whitespace_loc) == "genome") {
            current_line.erase(0,first_whitespace_loc+1);
            output_file = current_line;
        }
        // Parse occupancy line
        else if (current_line.substr(0,first_whitespace_loc) == "occupancy") {
            current_line.erase(0,first_whitespace_loc+1);
            occupancy = stoi(current_line);
        }
        // Parse table size line
        else if (current_line.substr(0,first_whitespace_loc) == "table_size") {
            current_line.erase(0,first_whitespace_loc+1);
            table_size = stoi(current_line);
        }
        // Parse quit line
        else if (current_line.substr(0,first_whitespace_loc) == "quit") {
            break;
        }
    }
}

// Function to parse genome from file
string text_parser_genome(string genome_file,int const &kmer,vector <string> &lines) {
    ifstream file;
    vector <string> temp;
	file.open(genome_file);
	string current_line;
    // Divide file into kmers and store in temp
	while (getline (file, current_line)) {
        while(current_line.length() != 0) {
            temp.push_back(current_line.substr(0,kmer));
            current_line.erase(0,kmer);
        }
    }
    string whole_file = "";
    // Concatenate all kmers into whole_file string
    for(unsigned int i = 0; i < temp.size(); i++) {
        whole_file = whole_file + temp[i];
    }
    // Store all kmers into lines
    for(unsigned int i = 0; i < whole_file.length(); i++) {
        lines.push_back(whole_file.substr(i,kmer));
    }
    return whole_file;


}

int main(int argc, char* argv[]) {
    //Initialize variables
    string output_file;
    int kmer;
    int table_size = 100;
    float occupancy = 0.5;
    vector <string> queries;
    vector <string> kmerkeys;

    // call helper functions to process user specified input
    text_parser_input(kmer,queries,output_file,table_size,occupancy);
    string whole_file = text_parser_genome(output_file,kmer,kmerkeys);

    // initialize empty hash table of user specified size
    HashTable genome_hashtable(table_size);

    // insert k-mers into hash table with start and end position in genome
    for(int i = 0; i < kmerkeys.size(); i++) {
        long int start_position = i;
        long int end_position = start_position + kmer-1;
        genome_hashtable.insert(kmerkeys[i],make_pair(start_position,end_position));
    }
     // if occupancy of hash table exceeds given limit, resize and rehash all k-mers
    if(genome_hashtable.occupancy_check(occupancy) == true) {
        genome_hashtable.resize(table_size*2);
        for(int i = 0; i < kmerkeys.size(); i++) {
            genome_hashtable.remove(kmerkeys[i]);
        }
        for(int i = 0; i < kmerkeys.size(); i++) {
            long int start_position = i;
            long int end_position = start_position + kmer-1;
            genome_hashtable.insert(kmerkeys[i],make_pair(start_position,end_position));
        }
    }
    // call .get() to obtain all substrings matching current query and check following characters for mismatches
    for(int i = 0; i < queries.size(); i++) {
        int counter = 0;
        vector <pair<int,int> > found_pairs = genome_hashtable.get(queries[i].substr(1,kmer));
        if (found_pairs.size() != 0) {
            for(unsigned int z = 0; z < found_pairs.size(); z++) {
                int rest_of_len = queries[i].length() - kmer;
                string genome_rest_of_string = whole_file.substr(found_pairs[z].second,rest_of_len);
                string query_rest_of_string = queries[i].substr(kmer,rest_of_len);
                int mismatch_num = stoi(queries[i].substr(0,1));
                int mismatch_counter = 0;
                 // check for number of mismatches
                for(unsigned int d = 0; d < rest_of_len; d++) {
                    if(genome_rest_of_string[d] != query_rest_of_string[d]) {
                            mismatch_counter += 1;
                        }
                    }
                // if number of mismatches is within limit, print out query and match info
                if(mismatch_counter <= mismatch_num) {
                    cout << "Query: " << queries[i].substr(1,queries[i].length()-1) << endl;
                    cout << found_pairs[z].first << " " << mismatch_counter << " "<<  whole_file.substr(found_pairs[z].first,queries[i].length()-1) << endl;
                    counter += 1;
                    }
                }    
            // if no matches found, print out query and "No Match"
            if (counter == 0) {
                cout << "Query: " << queries[i].substr(1,queries[i].length()-1) << endl;
                cout << "No Match" << endl;
            }
        }
        
    }
    return 0;
}