// A simple "caller ID" program
#include <map>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// add a number, name pair to the phonebook
void add(map<int,string>&phonebook, int number, string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(map<int,string>&phonebook, int number) {
  if (phonebook[number] == "") 
    cout << "unknown caller!" << endl;
  else 
    cout << phonebook[number] << " is calling!" << endl;
}


int main() {
  // create the phonebook; initially all numbers are unassigned
  map<int, string> mymap;
  add(mymap,10000, "UNASSIGNED");

  // add several names to the phonebook
  add(mymap, 1111, "fred");
  add(mymap, 2222, "sally");
  add(mymap, 3333, "george");

  // test the phonebook
  identify(mymap, 2222);
  identify(mymap, 4444);
}