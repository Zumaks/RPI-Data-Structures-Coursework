#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values )
  {
    for (auto value : values) {
        push(value);
    }
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry )
  {
    // add the new element to the end of the heap
  m_heap.push_back(entry);
  
  // bubble up the new element
  int child_index = m_heap.size() - 1;
  while (child_index > 0) {
    int parent_index = (child_index - 1) / 2;
    if (m_heap[child_index] < m_heap[parent_index]) {
      std::swap(m_heap[child_index], m_heap[parent_index]);
      child_index = parent_index;
    } else {
      break;
    }
  }
  }

  void pop() 
  {
    assert( !m_heap.empty() );
    // Move the last element to the root
    m_heap[0] = m_heap.back();
    m_heap.pop_back();
    
    // Move the new root down the heap
    int parent_index = 0;
    while (true) {
        int left_child_index = parent_index * 2 + 1;
        int right_child_index = parent_index * 2 + 2;
        int min_child_index = parent_index;
        if (left_child_index < m_heap.size() && m_heap[left_child_index] < m_heap[min_child_index]) {
            min_child_index = left_child_index;
        }
        if (right_child_index < m_heap.size() && m_heap[right_child_index] < m_heap[min_child_index]) {
            min_child_index = right_child_index;
        }
        if (min_child_index == parent_index) {
            break; // heap property is restored
        }
        std::swap(m_heap[parent_index], m_heap[min_child_index]);
        parent_index = min_child_index;
    }
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
    for (int i = 0; i < heap.size(); i++) {
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;
    if (left_child < heap.size() && heap[left_child] < heap[i]) {
      return false;
    }
    if (right_child < heap.size() && heap[right_child] < heap[i]) {
      return false;
    }
  }
  return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


template <class T>
void heap_sort( std::vector<T> & v )
{
     // create a priority queue with the elements of the vector
    priority_queue<T> pq(v);

    // remove elements from the priority queue and store them back in the vector
    for (int i = 0; i < v.size(); i++) {
        v[i] = pq.top();
        pq.pop();
    }
}

#endif