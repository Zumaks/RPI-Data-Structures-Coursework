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
        freq_map[value]++;
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


// #include <iostream>
// #include <map>
// #include <vector>

// int main() {
//     std::map<int, int> countMap;
//     int maxCount = 0;

//     // insert some test values into the count map
//     countMap[19]++;
//     countMap[83]++;
//     countMap[-12]++;
//     countMap[83]++;
//     countMap[65]++;
//     countMap[19]++;
//     countMap[45]++;
//     countMap[-12]++;
//     countMap[45]++;
//     countMap[19]++;
//     countMap[45]++;
//     // find all integers that occur with maxCount frequency
//     std::vector<int> modes;
//     for (std::map<int, int>::const_iterator it = countMap.begin(); it != countMap.end(); ++it) {
//         if (it->second > maxCount) {
//             maxCount = it->second;
//         }
//     }
//     for (std::map<int, int>::const_iterator it = countMap.begin(); it != countMap.end(); ++it) {
//         if (it->second == maxCount) {
//             modes.push_back(it->first);
//         }
//     }

//     // print the modes to the console
//     std::cout << "Modes:";
//     for (std::vector<int>::const_iterator it = modes.begin(); it != modes.end(); ++it) {
//         std::cout << " " << *it;
//     }
//     std::cout << std::endl;

//     return 0;
// }