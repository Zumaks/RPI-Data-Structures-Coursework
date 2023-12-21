#include "inventory.h"
#include <string>
Inventory::Inventory(string ID1, int quantity1, string item_name1) {
    ID = ID1;
    quantity = quantity1;
    original_quantity = quantity1;
    item_name = item_name1;
}

void Inventory::rent(Customer a) {
// Adding customer object to list of current renters if available quantity is present, if not added to pending renters
if (quantity - a.getQuantity() < 0) {
    pending_renters.push_back(a);
}
else {
    renters.push_back(a);
    quantity = quantity - a.getQuantity();
}

}


void Inventory::returns(Customer a) {
// Handling returns by erasing elements from renters/pending_renters list if the specified customer is found in the lists
    if (pending_renters.size() != 0) {
        list <Customer>::iterator it;
            for(it = renters.begin();it != renters.end(); it++) {
                if ((*it).getC_ID() == a.getC_ID()) {
                    renters.erase(it);
                }
            }
        renters.push_back(pending_renters.front());
        pending_renters.pop_front();
    }
    else { 
        list <Customer>::iterator it;
            for(it = renters.begin();it != renters.end(); it++) {
                if ((*it).getC_ID() == a.getC_ID()) {
                    renters.erase(it);
                }
            }
        quantity = quantity + a.getQuantity();
    }

}