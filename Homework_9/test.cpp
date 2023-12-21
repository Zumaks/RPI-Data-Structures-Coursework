#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
using namespace std;

int main(){
    vector <list<pair<int,int> > > g;
    g.resize(10);
    for (int i = 0; i < g.size(); i++) {
        cout << "List " << i << ": ";
        for (auto it = g[i].begin(); it != g[i].end(); it++) {
            cout << "(" << it->first << ", " << it->second << ") ";
        }
        cout << endl;
    }
}