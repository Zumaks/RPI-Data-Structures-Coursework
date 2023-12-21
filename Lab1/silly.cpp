#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;
 int main(int argc, char* argv[]) { 
    int product = 1;
    for(int i=1;i<argc;i++) {
        int num = atoi(argv[i]);
        product = product * num;
    }
    std::cout << "Product :" << product << std::endl ;
    }











