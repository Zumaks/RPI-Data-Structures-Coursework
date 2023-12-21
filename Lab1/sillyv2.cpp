#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;
 int main(int argc, char* argv[]) { 
    std::vector <std::string> all_words;
    for(int i=1;i<argc;i++) {
        all_words.push_back(argv[i]);
        sort(all_words.begin(), all_words.end());
    }
    for(int i=0;i<all_words.size();i++) {
		std::cout << "Sorted Words: " << all_words[i]<< std::endl ;
    }
    }


 
 
 
 
 
 
 
 
 
 
 
