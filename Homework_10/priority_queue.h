#ifndef priority_queue_h_
#define priority_queue_h_

#include <cassert>
#include <iostream>
#include <vector>
#include <map>

// The DistancePixel_PriorityQueue is a customized, non-templated
// priority queue that stores DistancePixel pointers in a heap.  The 
// elements in the heap can be looked up in a map, to quickly find out
// the current index of the element within the heap.

// ASSIGNMENT: The class implementation is incomplete.  Finish the
//   implementation of this class, and add any functions you need.

// =========================================================================

class DistancePixel_PriorityQueue {

 public:
  
  // --------------------------
  // CONSTRUCTORS
  // default constructor
  DistancePixel_PriorityQueue() {}
  // construct a heap from a vector of data
  DistancePixel_PriorityQueue(const std::vector<DistancePixel*> &values) {
    for (std::vector<DistancePixel*>::const_iterator it = values.begin(); it != values.end(); ++it) {
        push(*it);
    }
  }

  // ------------------------
  // ACCESSORS
  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }
  int last_non_leaf() { return (size()-1) / 2; }
  int get_parent(int i) { assert (i > 0 && i < size()); return (i-1) / 2; }
  bool has_left_child(int i) { return (2*i)+1 < size(); }
  bool has_right_child(int i) { return (2*i)+2 < size(); }
  int get_left_child(int i) { assert (i >= 0 && has_left_child(i)); return 2*i + 1; }
  int get_right_child(int i) { assert (i >= 0 && has_right_child(i)); return 2*i + 2; }

  // read the top element
  const DistancePixel* top() const  {
    assert(!m_heap.empty());
    return m_heap[0]; 
  }

  // is this element in the heap?
  bool in_heap(DistancePixel* element) const {
    std::map<DistancePixel*,int>::const_iterator itr = backpointers.find(element);
    return (itr != backpointers.end());
  }

  // add an element to the heap
  void push(DistancePixel* element) {
    std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
    assert (itr == backpointers.end());
    m_heap.push_back(element);
    backpointers[element] = m_heap.size()-1;
    this->percolate_up(int(m_heap.size()-1));
  }

  // the value of this element has been edited, move the element up or down
  void update_position(DistancePixel* element) {
    std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
    assert (itr != backpointers.end());
    this->percolate_up(itr->second);
    this->percolate_down(itr->second);
  }
  
  // remove the top (minimum) element
  void pop() {
    assert(!m_heap.empty());
    int success = backpointers.erase(m_heap[0]);
    assert (success == 1);
    m_heap[0] = m_heap.back();
    m_heap.pop_back();
    this->percolate_down(0);
  }
  
 private:

  // REPRESENTATION
  // the heap is stored in a vector representation (the binary tree
  // structure "unrolled" one row at a time)
  std::vector<DistancePixel*> m_heap;
  // the map stores a correpondence between elements & indices in the heap
  std::map<DistancePixel*,int> backpointers;

  // private helper functions

  void percolate_up(int i) {
  if (i <= 0) {
    // i is already at the root of the heap
    return;
  }
  // not out of boundes
if (i >= int(m_heap.size()) || m_heap.size() == 1) {
      return;
    }

// finds the parent of the current value
// recurses through  and swaps values if necessary
// until it reaches the top of the queue
  int parent = get_parent(i);
  if (*m_heap[i] < *m_heap[parent]) {
    // swap the element at i with its parent
    DistancePixel* temp = m_heap[parent];
    m_heap[parent] = m_heap[i];
    m_heap[i] = temp;
    // update the backpointers
    backpointers[m_heap[i]] = i;
    backpointers[m_heap[parent]] = parent;
    // continue percolating up from the parent
    percolate_up(parent);
  }
}

  
  void percolate_down(int i) {
    
    // makes sure in bounds
    if (i < 0 || i >= int(m_heap.size()) || m_heap.size() == 1) {
      return;
    }

    // finds the smaller child and recurses down until the correct spot is found
    if (has_left_child(i)) {
        int child = get_left_child(i);
        if (has_right_child(i) && *m_heap[get_right_child(i)] < *m_heap[child]) {
            child = get_right_child(i);
        }
        if (*m_heap[child] < *m_heap[i]) {
            // swap the element at i with its child
            DistancePixel* temp = m_heap[child];
            m_heap[child] = m_heap[i];
            m_heap[i] = temp;
            // update the backpointers
            backpointers[m_heap[i]] = i;
            backpointers[m_heap[child]] = child;
            // continue percolating down from the child
            percolate_down(child);
        }
    }
  }
};

#endif
