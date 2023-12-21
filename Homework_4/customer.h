#include <string>
using namespace std;

class Customer{
    public:
    Customer(string C_ID1, string action1, string time1, int quantity1, string item_name1, string customer_name1);
    string getC_ID() {return C_ID;}
    string getAction() {return action;}
    string getTime() {return time;}
    int getQuantity() {return quantity;}
    string getItem_Name() {return item_name;}
    string getCustomer_Name() {return customer_name;}
    private:
    string C_ID;
    string action;
    string time;
    int quantity;
    string item_name;
    string customer_name;

};