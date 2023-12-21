#include <fstream>
#include <list>
#include "inventory.h"
#include <iostream>
using namespace std;
// Function responsible for parsing through each line of input from the customer file and storing data in referenced variables
void text_parser_customer(string& current_line, string& C_ID, string& action, string& time, int& quantity, string& item_name, string& customer_name) {
    int first_space_loc = current_line.find(" ");
    C_ID = current_line.substr(0,first_space_loc);
    current_line.erase(0,first_space_loc+1);

    int second_space_loc = current_line.find(" ");
    action = current_line.substr(0,second_space_loc);
    current_line.erase(0,second_space_loc+1);

    int third_space_loc = current_line.find(" ");
    time = current_line.substr(0,third_space_loc);
    current_line.erase(0,third_space_loc+1);

    int fourth_space_loc = current_line.find(" ");
    quantity = stoi(current_line.substr(0,fourth_space_loc));
    current_line.erase(0,fourth_space_loc+1);

    int fifth_space_loc = current_line.find(" ");
    item_name = current_line.substr(0,fifth_space_loc);
    current_line.erase(0,fifth_space_loc+1);

    int sixth_space_loc = current_line.find(" ");
    customer_name = current_line.substr(0,sixth_space_loc);
    current_line.erase(0,sixth_space_loc+1);
}
//Function responsible for parsing through each line of input from the inventory file and storing data in referenced variables
void text_parser_inventory(string& current_line,string& ID, int& quantity, string& item_name) {
    int first_space_loc = current_line.find(" ");
    ID = current_line.substr(0,first_space_loc);
    current_line.erase(0,first_space_loc+1);

    int second_space_loc = current_line.find(" ");
    quantity = stoi(current_line.substr(0,second_space_loc));
    current_line.erase(0,second_space_loc+1);

    int third_space_loc = current_line.find(" ");
    item_name = current_line.substr(0,third_space_loc);
    current_line.erase(0,third_space_loc+1);
}

int main(int argc, char *argv[]) {
// Setting up and defining variables used to open files and store data
    ifstream inventory;
    ifstream customer;
    customer.open(argv[2]);
    inventory.open(argv[1]);
    string current_line;
    list <Inventory> inv_list;
    list <Customer> cust_list;
// Reading Customer File
    while (getline(customer, current_line)) {
        string C_ID;
        string action;
        string time;
        int quantity;
        string item_name;
        string customer_name;
        if (current_line[0] == 'C') {
            text_parser_customer(current_line,C_ID, action,time,quantity,item_name, customer_name);
                 cust_list.push_back(Customer(C_ID, action,time,quantity,item_name, customer_name));
        }
        else {
            cerr << "Invalid customer information found for ID " << current_line[0] << current_line[1] << current_line[2] << current_line[3] << current_line[4] << "in the customer file" << endl;
        }

    }
// Reading Inventory File
    string current_line2;
    while (getline(inventory, current_line2)) {
        string ID;
        int quantity;
        string item_name;
        if (current_line2[0] == 'T') {
            text_parser_inventory(current_line2,ID, quantity, item_name);
            inv_list.push_back(Inventory(ID, quantity, item_name));
        }
        // Error Checking 
        else {
            cerr << "Invalid inventory ID " << current_line2[0] << current_line2[1] << current_line2[2] <<  current_line2[3] << current_line2[4] << "found in the inventory file." << endl;
        }
    }
// Checking to see what action type the customer request is and preforming that action (rent/return)
    list <Customer>::iterator it;
    for(it = cust_list.begin();it != cust_list.end(); it++) {
        if((*it).getAction() == "return") {
            list <Inventory>::iterator it2;
            for(it2 = inv_list.begin();it2 != inv_list.end(); it2++) {
                if ((*it).getItem_Name() == (*it2).getID()) {
                    (*it2).returns(*it);
                }
            }

        }
        else if ((*it).getAction() == "rent") {
            list <Inventory>::iterator it2;
            for(it2 = inv_list.begin();it2 != inv_list.end(); it2++) {
                if ((*it).getItem_Name() == (*it2).getID()) {
                    (*it2).rent(*it);
                }
            }
        }
    }






//Sorting Inventory List:
list <Inventory> new_inv_list;
list <Inventory>::iterator it12 = inv_list.begin();
for(it12 = inv_list.begin();it12 != inv_list.end(); it12++) {
    if(new_inv_list.size() == 0) {
        new_inv_list.push_back((*it12));
    }
    else {
        list <Inventory>::iterator it13 = new_inv_list.begin();
        while(it13 != new_inv_list.end() && (*it13).getID() < (*it12).getID()) {
            ++it13;
            }
        new_inv_list.insert(it13,(*it12));
    }
}

// Sorting Customer List:
list <Customer> new_cust_list;
list <Customer>::iterator it11 = cust_list.begin();
for(it11 = cust_list.begin();it11 != cust_list.end(); it11++) {
    if (new_cust_list.size() == 0) {
        new_cust_list.push_back((*it11));
    }
    else {
        list <Customer>::iterator it10 = new_cust_list.begin();
        while(it10 != new_cust_list.end() && (*it10).getC_ID() < (*it11).getC_ID()) {
            ++it10;
            }
        new_cust_list.insert(it10,(*it11));
    }
}
// Writing to the inventory file:
ofstream inv_file;
inv_file.open(argv[3]);
list <Inventory>::iterator it3;
    for(it3 = new_inv_list.begin();it3 != new_inv_list.end(); it3++) {
        inv_file << (*it3).getID() << " " << (*it3).getQuantity() << " " << (*it3).getItem_Name() << endl;
        list <Customer> renters = (*it3).get_renters();
        list <Customer> pending_renters = (*it3).get_pending_renters();
        list <Customer> new_renters;
        list <Customer> new_pending_renters;
        // Sorting renters list by C_ID if more than one element in renters
        if (renters.size() > 1) { 
            list <Customer>::iterator it16 = renters.begin();
            for(it16 = renters.begin();it16 != renters.end(); it16++) {
                if (new_renters.size() == 0) {
                    new_renters.push_back((*it16));
                }
                else {
                    list <Customer>::iterator it17 = new_renters.begin();
                    while(it17 != new_renters.end() && (*it17).getC_ID() < (*it16).getC_ID()) {
                        ++it17;
                        }
                    new_renters.insert(it17,(*it16));
                }
            }
        }
        // Sorting pending_renters list by C_ID if more than one element in renters
        else if (pending_renters.size() > 1) { 
            list <Customer>::iterator it14 = pending_renters.begin();
            for(it14 = pending_renters.begin();it14 != pending_renters.end(); it14++) {
                if (new_pending_renters.size() == 0) {
                    new_pending_renters.push_back((*it14));
                }
                else {
                    list <Customer>::iterator it15 = new_pending_renters.begin();
                    while(it15 != new_pending_renters.end() && (*it15).getC_ID() < (*it14).getC_ID()) {
                        ++it15;
                        }
                    new_pending_renters.insert(it15,(*it14));
                }
            }

        }
        else  {
            //If sorting not required outputting without sortings
            if (renters.size() == 0 && pending_renters.size() == 0) { 
            inv_file << "\n";
            continue;
        }
        else if (renters.size() != 0 && pending_renters.size() == 0){
            list <Customer>::iterator it4;
            inv_file << "Rental Customers: " ;
            for(it4 = renters.begin();it4 != renters.end(); it4++) {
                inv_file << (*it4).getC_ID() << " " <<  (*it4).getCustomer_Name() << " (" << (*it4).getQuantity() << ") ";
            }
            inv_file << endl;
            inv_file << "\n";
            continue;
        }
        else if (renters.size() == 0 && pending_renters.size() != 0) {
            list <Customer>::iterator it5;
            inv_file << "Pending Customers: " ;
            for(it5 = pending_renters.begin();it5 != pending_renters.end(); it5++) {
                inv_file << (*it5).getC_ID() << " " <<  (*it5).getCustomer_Name() << " (" << (*it5).getQuantity() << ") ";
            }
            inv_file << endl;
            inv_file << "\n";
            continue;
        }
        else {
            list <Customer>::iterator it4;
            inv_file << "Rental Customers: " ;
            for(it4 = renters.begin();it4 != renters.end(); it4++) {
                inv_file << (*it4).getC_ID() << " " <<  (*it4).getCustomer_Name() << " (" << (*it4).getQuantity() << ") ";
            }
            inv_file << endl;

            list <Customer>::iterator it5;
            inv_file << "Pending Customers: " ;
            for(it5 = pending_renters.begin();it5 != pending_renters.end(); it5++) {
                inv_file << (*it5).getC_ID() << " " <<  (*it5).getCustomer_Name() << " (" << (*it5).getQuantity() << ") ";
            }
            inv_file << endl;

            inv_file << "\n";
            continue;
        }
        }

// If sorting required outputting sorted version of renters and pending_renters called new_renters and new_pending_renters
        if (new_renters.size() == 0 && new_pending_renters.size() == 0) { 
            inv_file << "\n";
            continue;
        }
        else if (new_renters.size() != 0 && new_pending_renters.size() == 0){
            list <Customer>::iterator it4;
            inv_file << "Rental Customers: " ;
            for(it4 = new_renters.begin();it4 != new_renters.end(); it4++) {
                inv_file << (*it4).getC_ID() << " " <<  (*it4).getCustomer_Name() << " (" << (*it4).getQuantity() << ") ";
            }
            inv_file << endl;
            inv_file << "\n";
        }
        else if (new_renters.size() == 0 && new_pending_renters.size() != 0) {
            list <Customer>::iterator it5;
            inv_file << "Pending Customers: " ;
            for(it5 = new_pending_renters.begin();it5 != new_pending_renters.end(); it5++) {
                inv_file << (*it5).getC_ID() << " " <<  (*it5).getCustomer_Name() << " (" << (*it5).getQuantity() << ") ";
            }
            inv_file << endl;
            inv_file << "\n";
        }
        else {
            list <Customer>::iterator it4;
            inv_file << "Rental Customers: " ;
            for(it4 = new_renters.begin();it4 != new_renters.end(); it4++) {
                inv_file << (*it4).getC_ID() << " " <<  (*it4).getCustomer_Name() << " (" << (*it4).getQuantity() << ") ";
            }
            inv_file << endl;

            list <Customer>::iterator it5;
            inv_file << "Pending Customers: " ;
            for(it5 = new_pending_renters.begin();it5 != new_pending_renters.end(); it5++) {
                inv_file << (*it5).getC_ID() << " " <<  (*it5).getCustomer_Name() << " (" << (*it5).getQuantity() << ") ";
            }
            inv_file << endl;

            inv_file << "\n";
        }


    }



// Writing to the Customer File:
ofstream cust_file;
cust_file.open(argv[4]);

list <Customer>::iterator it6;
list <string> duplicate_checker;
    for(it6 = new_cust_list.begin();it6 != new_cust_list.end(); it6++) {
// Checking for duplicate elements. Customer list is based on actions not customers themselves hence duplicates are present
        bool found_dupe = false;
        list <string>::iterator it9;
        for(it9 = duplicate_checker.begin(); it9 != duplicate_checker.end(); it9++) {
            if ((*it6).getC_ID() == *it9) {
                found_dupe = true;
                break;
            }
        }
        if(found_dupe == true) {
            continue;
        }
        else { 
            duplicate_checker.push_back((*it6).getC_ID());
        }
        list <Inventory>::iterator it7;
        // Formatting output
        string temp_renters;
        string temp_pending_renters;
        for(it7 = new_inv_list.begin();it7 != new_inv_list.end(); it7++) {
            list <Customer> renters = (*it7).get_renters();
            list <Customer> pending_renters = (*it7).get_pending_renters();
            list <Customer>::iterator it8;
            for(it8 = renters.begin();it8 != renters.end(); it8++) {
                if ((*it6).getC_ID() == (*it8).getC_ID()) { 
                    temp_renters = temp_renters + " " + (*it7).getID() +" "+"(" + to_string((*it8).getQuantity())+")";
                }
            }


            list <Customer>::iterator it9;
            for(it9 = pending_renters.begin();it9 != pending_renters.end(); it9++) {
                if ((*it6).getC_ID() == (*it9).getC_ID()) { 
                    temp_pending_renters = temp_pending_renters +" " + (*it7).getID() +   " "+"(" +to_string((*it9).getQuantity()) + ")";
                }
            }




        }
    // Creating the output
    if (temp_renters.length() == 0 && temp_pending_renters.length() == 0) { 
        continue;
    }
    else if (temp_renters.length() == 0 && temp_pending_renters.length() != 0) { 
        cust_file << (*it6).getC_ID() << " " << (*it6).getCustomer_Name() << endl;
        cust_file << "Pending:" << temp_pending_renters << endl;
        cust_file << "\n";
    }

    else if (temp_renters.length() != 0 && temp_pending_renters.length() == 0) { 
        cust_file << (*it6).getC_ID() << " " << (*it6).getCustomer_Name() << endl;
        cust_file << "Rentals:" << temp_renters << endl;
        cust_file << "\n";
    }
    else { 
        cust_file << (*it6).getC_ID() << " " << (*it6).getCustomer_Name() << endl;
        cust_file << "Rentals:" << temp_renters << endl;
        cust_file << "Pending:" << temp_pending_renters << endl;
        cust_file << "\n";

    }
    }
    cust_file.close();
}