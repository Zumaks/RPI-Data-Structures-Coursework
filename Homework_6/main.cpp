#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// function to parse the input file and store the positive and negative words and board dimensions
void text_parser(char* file_name,int &height, int &width, vector <string> &pos_words, vector <string> &neg_words) {
    ifstream file;
    file.open(file_name);
    string line;
    int count  = 0;
    while (getline (file, line)) {
        // the first line of the input file contains the board dimensions
        if (count == 0) {
            int white_space_loc = line.find(" ");
            width = stoi(line.substr(0,white_space_loc));
            line.erase(0,white_space_loc);
            height = stoi(line);
        }
        // lines starting with '+' contain positive words and lines starting with '-' contain negative words
        else {
            if(line[0] == '+') { 
                pos_words.push_back(line.substr(2,line.length()));
            }
            else if (line[0] == '-') { 
                neg_words.push_back(line.substr(2,line.length()));
            }
        }
        count += 1;

    }
}

// function to generate all possible combinations of positive words for the board
void generateCombinations(vector<string>& vec, int height, vector < vector < string> > &combinations) {
    int stringnum = vec.size();

    if (stringnum < height) {
        cout << "Error: height is larger than the amount of words present" << endl;
        return;
    }

    vector<int> indexes(height, 0);
    for (int i = 0; i < height; i++) {
        indexes[i] = i;
    }

    // generate all combinations using the indexes
    while (true) {
        vector <string> combo;
        for (int i = 0; i < height; i++) {
            combo.push_back(vec[indexes[i]]);
        }
        combinations.push_back(combo);

        // update the indexes for the next combination
        int i = height - 1;
        while (i >= 0 && indexes[i] == stringnum - height + i) {
            i--;
        }
        if (i < 0) {
            break;
        }
        indexes[i]++;
        for (int j = i + 1; j < height; j++) {
            indexes[j] = indexes[j - 1] + 1;
        }
    }
}

// function to find all permutations of a vector of strings
vector<vector<string> > find_combinations(vector<string> vec) {
    vector<vector<string> > combinations;
    sort(vec.begin(), vec.end());
    while (true) {
        combinations.push_back(vec);
        if (!next_permutation(vec.begin(), vec.end())) {
            break;
        }
    }

    return combinations;
}

// function to create the final board with positive words
void board_creator(vector <string> pos_words,vector < vector <string> > all_sol, int board_size, vector < vector <string> > &final_pos) {
    
    vector < vector <string> > all_sols;
    generateCombinations(pos_words, board_size,all_sols);
    for(int i = 0; i < all_sols.size(); i++) {
        vector<vector<string> > combinations = find_combinations(all_sols[i]);
        for(int z = 0; z < combinations.size() ; z++) { 
            final_pos.push_back(combinations[z]);
        }
    }
}

vector <string> backwards(vector <string> pos_words) { 
    // Initialize an empty vector to hold the reversed strings.
    vector <string> pos_words_backwards; 
    // Loop through each string in the input vector.
    for(unsigned int i = 0; i < pos_words.size(); i++) { 
        string temp_string = "";
        // Loop through each character in the current string in reverse order.
        for(int z =  pos_words[i].length(); z >= 0; z--) {
            temp_string = temp_string + pos_words[i][z];
        }
        // Add the reversed string to the output vector.
        pos_words_backwards.push_back(temp_string);
    }
    // Return the vector of reversed strings.
    return pos_words_backwards;
}





vector<string> rotater(const vector<string> vec) {
    int x = vec.size(); 
    int y = vec[0].size();
    // Create a new vector with dimensions (y, x) filled with ' '
    vector<string> rotater(y, string(x, ' ')); 

    //Loop through rows
    for (int i = 0; i < x; i++) { 
        //Loop through coloumns
        for (int j = 0; j < y; j++) { 
            // Transpose the new vector
            rotater[j][i] = vec[i][j+1]; 
        }
    }

    return rotater; 
}


bool WordFinder(const vector<string>& board, const vector<string>& words, int row, int letter, int direction) {
    // Check if the given row and letter are within the bounds of the board
    if (row < 0 || letter < 0 || row >= board.size() || letter >= board[row].size()) {
        return false;
    }
    // Initialize an empty string to store the current word being formed
    string cur_word;
    // Traverse the board in the specified direction until the end of the board is reached or no word is found
    for (int x = row, y = letter; x >= 0 && x < board.size() && y >= 0 && y < board[x].size(); y += direction / 3 - 1, y += direction % 3 - 1) {
        cur_word += board[x][y]; 
        // Check if the current word is in the list of words to find
        for (int i = 0; i < words.size(); i++) {
            if (words[i] == cur_word)
                // If the word is found, return true
                return true; 
        }
    }
    // If the word is not found, return false
    return false; 
}

bool recursive_search_board(const vector<string>& board, const vector<string>& cur_words, int row, int let) {
    // If the row index is greater than or equal to the size of the grid, return false
    if (row >= board.size()) {
        return false;
    }
    // If the column index is greater than or equal to the size of the row, search the next row
    if (let >= board[row].size()) {
        return recursive_search_board(board, cur_words, row + 1, 0);
    }
    // Loop through all possible directions to search ins
    for (int i = 0; i < 9; i++) {
        // Skip the center direction (current position)
        if (i == 4) {
            continue;
        }
        // If a word is found using the WordFinder function, return true
        if (WordFinder(board, cur_words, row, let, i)) {
            return true;
        }

    }
    // If no word is found at the current position, search the next column
    return recursive_search_board(board, cur_words, row, let + 1);
}

bool search_for_words(const vector<string>& board, const vector<string>& words) {
    return recursive_search_board(board, words, 0, 0);
}



int main(int argc, char* argv[]) {   
    // Declare variables to store input data and computed results 
    int height = 0;
    int width = 0;
    vector <string> pos_words;
    vector <string> neg_words;
    vector <vector <string> > all_pos;
    vector <vector <string> > all_pos_backwards;
    vector <vector <string> > all_neg;
    vector <vector <string> > final_pos;
    vector <vector <string> > final_pos_backwards;


    // Parse input data and store in variables
    text_parser(argv[1],height,width,pos_words,neg_words);
    vector <string> backwards_pos = backwards(pos_words);
    vector <string> backwards_neg = backwards(neg_words);
    // Generate forward and backward boards from positive words
    board_creator(pos_words,all_pos,height,final_pos);
    board_creator(backwards_pos,all_pos_backwards,height,final_pos_backwards);


    // Rotate each board and add rotated boards to list of all possible solutions
    vector < vector < string > > all_possible_solutions;

    for(int i = 0; i < final_pos.size(); i++) {
        vector <string> reversed_current = rotater(final_pos[i]);
        all_possible_solutions.push_back(reversed_current);
        all_possible_solutions.push_back(final_pos[i]);
    }

    for(int i = 0; i < final_pos_backwards.size(); i++) {
        vector <string> reversed_current = rotater(final_pos_backwards[i]);
        all_possible_solutions.push_back(reversed_current);
        all_possible_solutions.push_back(final_pos_backwards[i]);
    }
    // Find all valid solutions that don't contain any negative words
    vector <vector <string> > all_valid_solutions;
    for(int i = 0; i < all_possible_solutions.size(); i++) {
        bool cur_val = search_for_words(all_possible_solutions[i],neg_words);
        if (!cur_val) {
            all_valid_solutions.push_back(all_possible_solutions[i]);
        }
    }
    // Write results to output file depending on user specified format type
    if (argv[3] == "one_solution") {
        ofstream writer;
        writer.open(argv[2]);
        for(int i = 0; i < all_valid_solutions.size(); i++) {
            for(int z = 0; z < all_valid_solutions[i].size(); z++) {
                writer << all_valid_solutions[i][z] << " ";
        }
        writer << endl;
        }
    }
    else {

    }
    ofstream writer;
    writer.open(argv[2]);
    for(int i = 0; i < all_valid_solutions.size(); i++) {
        for(int z = 0; z < all_valid_solutions[i].size(); z++) {
            writer << all_valid_solutions[i][z] << " ";
    }
    writer << endl;
    }
}

