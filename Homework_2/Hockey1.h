#include <vector>
#include <string>
#include <iostream>

using namespace std;
class Hockey {
    public:
    Hockey(vector < vector < string> > Games);
    void data_transformation(vector < vector < string> > Games);
    vector < vector < vector < string> > > getData();
    private: 
    vector < vector < string> > all_games;
    vector < vector < vector < string> > > processed_data;
};