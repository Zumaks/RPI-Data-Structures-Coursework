#include <string>
using namespace std;
class Animal {
    public: 
    Animal(string Name);

    //Acc
    void getWeight() const;
    void setWeight(); 
    void getName() const;
    bool getisland() const ; 
    bool getiswater() const;
    bool getiscarnivore() const;
    bool getisherbivour() const;
    bool getisamphibious() const;
    void setName();
    void setisland(); 
    void setiswater();
    void setiscarnivore();
    void setisherbivour();
    void setisamphibious();

    private:
    int weight;
    string Name;
    bool island() ; 
    bool iswater();
    bool iscarnivore();
    bool isherbivour();
    bool isamphibious();
};