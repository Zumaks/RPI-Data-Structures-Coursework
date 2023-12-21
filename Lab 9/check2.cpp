#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input_file(argv[1]);
    if (!input_file) {
        cout << "Error: Unable to open input file " << argv[1] << endl;
        return 1;
    }

    map<int, int> freq_map;
    int value;
    while (input_file >> value) {
        pair<map<int, int>::iterator, bool> result = freq_map.insert(make_pair(value, 1));
        if (!result.second) {
            ++(result.first->second);
        }
    }

    vector<int> modes;
    int max_freq = 0;
    for (map<int, int>::iterator it = freq_map.begin(); it != freq_map.end(); ++it) {
        if (it->second > max_freq) {
            modes.clear();
            modes.push_back(it->first);
            max_freq = it->second;
        } else if (it->second == max_freq) {
            modes.push_back(it->first);
        }
    }

    cout << "Modes:";
    for (vector<int>::iterator it = modes.begin(); it != modes.end(); ++it) {
        cout << " " << *it;
    }
    cout << endl;

    return 0;
}