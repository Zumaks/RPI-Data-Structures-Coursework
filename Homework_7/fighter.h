#include <string>
using namespace std;
class Fighter{ 
    
    public:

    Fighter() {}
    string getName() {return name;}
    int getJab() {return jab;}
    int getForward_Tilt() {return forward_tilt;}
    int getUp_Tilt() {return up_tilt;}
    int getDown_Tilt() {return down_tilt;}
    int getForward_Smash() {return forward_smash;}
    int getUp_Smash() {return up_smash;}
    int getDown_Smash() {return down_smash;}

    void setName(string input_name) {name = input_name;}
    void setJab(int input_jab) {jab = input_jab;}
    void setForward_Tilt(int input_forward_tilt) {forward_tilt = input_forward_tilt;}
    void setUp_Tilt(int input_up_tilt) {up_tilt = input_up_tilt;}
    void setDown_Tilt(int input_down_tilt) {down_tilt = input_down_tilt;}
    void setForward_Smash(int input_forward_smash) {forward_smash = input_forward_smash;}
    void setUp_Smash(int input_up_smash) {up_smash = input_up_smash;}
    void setDown_Smash(int input_down_smash) {down_smash = input_down_smash;}

    private:
    string name;
    int jab;
    int forward_tilt;
    int up_tilt;
    int down_tilt;
    int forward_smash;
    int up_smash;
    int down_smash;

};