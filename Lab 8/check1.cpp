#include <iostream>

int pathwaycounter(int startingx, int startingy) { 
    if (startingx == 0 && startingy == 0) { 
        return 1;
    }
    else if (startingx < 0 || startingy < 0) {
        return 0;
    }
    else {
        int pathways = 0;
        pathways = pathways + pathwaycounter(startingx,startingy - 1);
        pathways = pathways + pathwaycounter(startingx-1,startingy);
        return pathways;
    }   
}





int main() { 


int sum  = pathwaycounter(2,2);
std::cout << sum << std::endl;

}