#include <vector>
#include <string>
using namespace std;
class Hockey2 {

    public:
    Hockey2(vector < vector < vector < string> > > data);
    void player_stats();
    void team_stats();
    vector <float> custom_stats();
    vector <vector <float> > getTeam_Statistics();
    vector <string> getTeam_Names();
    vector <string> getPlayer_Names();
    vector <vector <float> > getPlayer_Statistics();
    vector <string> getPlayer_Teams();

    private:
    vector < vector < vector < string> > > stored_processed_data;
    vector <vector <float> > team_statistics;
    vector <string> team_names;

    vector <string> player_names;
    vector <vector <float> > player_statistics;
    vector <string> player_teams;


};