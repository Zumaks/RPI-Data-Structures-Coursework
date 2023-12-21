
/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <algorithm>
#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE
using namespace std;
///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

// Define a templated operator >= to compare two objects of type T
template <class T>
bool operator>=(const T& lhs, const T& rhs) {
    return lhs >= rhs;
}

// Define a templated operator== to compare two objects of type T
template <class T>
bool operator==(const T& lhs, const T& rhs) {
    return lhs == rhs;
}

// Define a B+ tree class which forms the B+ tree datastructure itself
template <class T> class BPlusTree{

	public: 
    // Constructor to initialize the B+ tree with a given maximum degree
	BPlusTree(int max_degree) { max_d = max_degree;}
	void insert(const T& element);
    // Print the B+ tree sideways to a file
    void print_sideways(ofstream &file) {
        // If the root node has no keys, the tree is empty
        if (root_->keys.size() == 0) {
            file << "Tree is empty." << endl;
        }
        }
    // Print the B+ tree in breadth-first search order to a file
    void print_BFS(ofstream &file) {
        // If the root node has no keys, the tree is empty
        if (root_->keys.size() == 0) {
            file << "Tree is empty." << endl;
        }
        }
    // Find the level at which the element is supposed to be for use with the contains function
	BPlusTreeNode<T>* find(T element);

	private:
    // Pointer to the root node of the B+ tree
	BPlusTreeNode<T>* root_ = new BPlusTreeNode<T>();
    // Maximum degree of the B+ tree
	int max_d;

};

template <class T>
void BPlusTree<T>::insert(const T& element) {
    if (root_->keys.size() < max_d && root_->children.size() == 0) {
        // If the root node is not full and is a leaf node, insert into the root
        root_->keys.push_back(element);
        sort(root_->keys.begin(), root_->keys.end());
    } else {
        // Otherwise, traverse the tree to find the appropriate leaf node
        BPlusTreeNode<T>* node = root_;
        while (!node->is_leaf()) {
            int i = 0;
            while (i < node->keys.size() && element > node->keys[i]) {
                i++;
            }
            node = node->children[i];
        }

        // Insert the element into the identified leaf node
        node->keys.push_back(element);
        sort(node->keys.begin(), node->keys.end());
    }
}


template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(T element) {
	BPlusTreeNode<T>* node = root_;
    // Traverse the tree until a leaf node is reached
	while (!node->is_leaf()) {
        // Find the index of the child to follow
		int counter = 0;
		while (counter < node->keys.size() && element >= node->keys[counter]) {
			counter++;
		}
		node = node->children[counter];
	}
    // Search the leaf node for the element
	for (int i = 0; i < node->keys.size(); i++) {
		if (node->keys[i] == element) {
			return node;
		}
	}
    // If the element is not found, return a null pointer
	return nullptr;
}


#endif
