#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

// Node Class for use in linked list when two keys are the same
class Node {
    public:
    pair<int,int> positions;
    Node* next;
    Node(pair<int,int> d) : positions(d), next(nullptr) {}
};

// Hash Function taken from lecture
int hashFunction(string key) {
    // This implementation comes from
    // http://www.partow.net/programming/hashfunctions/
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++) {
        hash ^= ((hash << 5) + key[i] + (hash >> 2));
    }
    return hash;
}   

// HashTable class serving as the hash table data structure
class HashTable{
    public:
    HashTable(int size) {
        // Resize the table vector to the specified size
        table.resize(size);
    }
    // Function to insert a key-value pair into the HashTable
    void insert(string key, pair<int,int> positions){
        // Generate a hashed key for the given key
        int hashed_key = hashFunction(key);
        // Get the index of the table vector to insert the key-value pair
        int index = hashed_key % table.size();
         // Check if the list at the calculated index is empty
        if(table[index].size() == 0) {
            // If the list is empty, create a new node and add it to the bucket
            Node* first = new Node(make_pair(positions.first,positions.second));
            first->next = nullptr;
            table[index].push_back(make_pair(key,first));
        }
        else {
            // If the list is not empty, iterate over its contents to find the matching key
            list <pair<string,Node*> > ::iterator it;
            int count = 0;
            for(it = table[index].begin(); it != table[index].end(); it++){
                // If a matching key is found, add the new position to its node
                if((*it).first == key) {
                    count = count + 1;
                    if ((*it).second->next != nullptr) {
                        Node* temp = new Node(make_pair(positions.first,positions.second));
                        Node* current = (*it).second ;
                        // Traverse to the end of the linked list to append the new node
                        while(current->next != nullptr) {
                            current = current->next;
                        }
                        current->next = temp;
                    }
                    else {
                        // If the linked list has only one element, create a new node and add it to the linked list
                        Node* temp = new Node(make_pair(positions.first,positions.second));
                        (*it).second->next = temp;
                    }
                }
            }
            // If the matching key is not found, create a new node and add it to the list
            if (count == 0 ) {
                Node* first = new Node(make_pair(positions.first,positions.second));
                table[index].push_back(make_pair(key,first));
            }
        } 
    }
    // Function to retrieve the positions associated with a given key
    vector <pair<int,int> > get(string key) {
        vector <pair<int,int> > cur_pairs;
        int hashed_key = hashFunction(key);
        int index = hashed_key % table.size();
        list <pair<string,Node*> > ::iterator it;
        for(it = table[index].begin(); it != table[index].end(); it++){
            if((*it).first == key) {
                // If the node has multiple positions, traverse the linked list to retrieve them all
                if ((*it).second->next != nullptr) {
                    Node* temp = (*it).second ;
                    while(temp->next != nullptr) {
                        cur_pairs.push_back(make_pair(temp->positions.first,temp->positions.second));
                        temp = temp->next;
                    }
                    cur_pairs.push_back(make_pair(temp->positions.first,temp->positions.second));
                    }
                else {
                    // If the node has only one position, add it to the vector
                    cur_pairs.push_back(make_pair((*it).second->positions.first,(*it).second->positions.second));
                    }
            }
        }
        return cur_pairs;

    }

    // Function to remove a key-value pair from the HashTable
    void remove(string key) {
        // Calculate the index of the key using hash function
        int hashed_key = hashFunction(key);
        int index = hashed_key % table.size();
        // Iterate over the stl list at the calculated index
        list <pair<string,Node*> > ::iterator it;
        for(it = table[index].begin(); it != table[index].end(); it++){
            // If the key is found, delete all associated nodes in the linked list
            if((*it).first == key) {
                Node* current = (*it).second;
                while (current != nullptr) {
                    Node* temp = current;
                    current = current->next;
                    delete temp;
                }
                // Remove the key-value pair from the linked list
                table[index].erase(it);
                break;
                }
        }

        
    }
    // This function checks the occupancy rate of the hash table by counting the number of occcupied
    // slots in the table and comparing it to the size of the table.
    bool occupancy_check(float const &occupancy) {
        int occupied = 0;
        for(unsigned int  i = 0; i < table.size(); i++) {
            list <pair<string,Node*> > ::iterator it;
            for(it = table[i].begin(); it != table[i].end(); it++){
                occupied += 1;
            }
        }
        // If the occupancy rate is greater than the specified occupancy limit, return true
        if ((occupied/table.size()) > occupancy) {
            return true;
        }
        // Otherwise, return false
        else {
            return false;
        }
    }
    // This function resizes the hash table to the given value.
    void resize(int const &val) {
        // Change the size of the table vector to the given value
        table.resize(val);
    }


    private:
    // This is the table itself which consists of a vector of stl lists each of which contains pairs which
    // have both the key and a linked list in case a key can be found at more than one position.
    std::vector<list<pair<string,Node*> > > table;

};