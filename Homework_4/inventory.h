#include <fstream>
#include <list>
#include <string> 
#include "customer.h"
using namespace std;
class Inventory {
    public: 
    Inventory(string ID1, int quantity1, string item_name1);
    string getID() {return ID;}
    int getQuantity() {return quantity;}
    string getItem_Name() {return item_name;}
    void rent(Customer a);
    void returns(Customer a);
    list<Customer> get_renters() {return renters;}
    list<Customer> get_pending_renters() {return pending_renters;}
    private:
    list <Customer> renters;
    list <Customer> pending_renters;
    string ID;
    int quantity;
    int original_quantity;
    string item_name;
};