#include <iostream>
#include <vector>
#include <string>

using namespace std;

void generateCombinations(vector<string>& strVec, int groupLength, vector < vector < string> > &groups) {
    int numStrings = strVec.size();

    if (numStrings < groupLength) {
        cout << "Error: group length is greater than the number of strings in the vector." << endl;
        return;
    }

    vector<int> indices(groupLength, 0);
    for (int i = 0; i < groupLength; i++) {
        indices[i] = i;
    }

    while (true) {
        vector <string> group;
        for (int i = 0; i < groupLength; i++) {
            group.push_back(strVec[indices[i]]);
        }
        groups.push_back(group);

        int i = groupLength - 1;
        while (i >= 0 && indices[i] == numStrings - groupLength + i) {
            i--;
        }
        if (i < 0) {
            break;
        }
        indices[i]++;
        for (int j = i + 1; j < groupLength; j++) {
            indices[j] = indices[j - 1] + 1;
        }
    }
}

vector<vector<string> > findPermutations(vector<string> inputVec) {
    vector<vector<string> > permutations;
    sort(inputVec.begin(), inputVec.end());

    while (true) {
        permutations.push_back(inputVec);
        if (!next_permutation(inputVec.begin(), inputVec.end())) {
            break;
        }
    }

    return permutations;
}

int main() {
    vector<string> strVec ;
    strVec.push_back("apple");
    strVec.push_back("banana");
    strVec.push_back("cherry");
    strVec.push_back("date");
    int groupLength = 2;
    vector < vector <string> > all_sols;
    generateCombinations(strVec, groupLength,all_sols);
    for(int i = 0; i < all_sols.size(); i++) {
        vector<vector<string> > perms = findPermutations(all_sols[i]);
        for(int z = 0; z < perms.size() ; z++) { 
            for(int x = 0; x < perms[z].size() ; x++) { 
                cout << perms[z][x] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}


