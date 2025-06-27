#include<cstddef>
#include<functional>
#include<iostream>
#include"list_iterator.h"

#ifndef L_LIST_H
#define L_LIST_H

template<typename T>
class List;

template<typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& theList);

template<typename T>
std::istream& operator>>(std::istream& in, List<T>& theList);

template<typename T>
struct Node {
    T data;
    Node* next;
    Node* previous;
    
    Node() = delete;

    Node(const Node& other) = default;

    Node(const T& dat);
};


template<typename T>
class List {  
  Node<T>* _head;
  Node<T>* _tail;
  size_t _size;

  public:
    
  /*
   * Constructors!
   * */
  
  /// @brief default constructor
  List();

  /// @brief copy constructor
  /// @param other list to copy from
  List(const List& other);

  /// @brief move constructor
  /// @param other list to move from
  List(List&& other);

  /// @brief constructs a list from begin to end
  /// @tparam ForwardIterator a forward iterator
  /// @param begin beginning of the iteration
  /// @param end ending of the iteration
  template<class ForwardIterator>
  List(ForwardIterator begin, ForwardIterator end);

  ~List();

  /*
   * Member Functions!
   * */

  /// @brief returns a reference to the first value in the list
  /// @return a reference to a T
  /// @throws std::out_of_range if the list is empty
  T& front();

  /// @brief returns a const reference to the first value in the list
  /// @return a const reference to a T
  /// @throws std::out_of_range if the list is empty
  const T& front() const;
  
  /// @brief returns a const reference to the last value in the list
  /// @return a const reference to a T
  /// @throws std::out_of_range if the list is empty
  T& back();
  
  /// @brief returns a reference to the last value in the list
  /// @return a reference to a T
  /// @throws std::out_of_range if the list is empty
  const T& back() const;

  /// @brief returns true if the list is empty, false if not
  /// @return a boolean
  bool empty() const;

  /// @brief returns the number of items in the list
  /// @return size_t
  size_t size() const;

  /// @brief adds a new item to the start of the list
  void push_front(const T& item);

  /// @brief removes the first item in the list, and returns it
  /// @return T
  /// @throws std::out_of_range if the list is empty
  T pop_front();

  /// @brief adds a new item to the end of the list
  void push_back(const T& item);

  /// @brief removes the last item in the list, and returns it
  /// @return T
  /// @throws std::out_of_range if the list is empty
  T pop_back();

  /// @brief attempts to remove the first instance of the parameter
  /// @return bool if the parameter was found and removed
  /// @param the item to be removed
  bool remove(const T& item); 

  /// @brief attempts to remove the first instance where the parameter is true
  /// @return bool if the parameter was found and removed
  /// @param a function that returns true if an element should be removed
  bool remove(std::function<bool(T&)> query);

  /// @brief attempts to remove every instance of the parameter
  /// @return bool if the parameter was found and removed
  /// @param the item to be removed
  bool remove_all(const T& item);

  /// @brief attempts to remove every instance where the parameter is true
  /// @return bool if the parameter was found and removed
  /// @param a function that returns true if an element should be removed
  bool remove_all(std::function<bool(T&)> query);

  /// @brief empties the list
  void clear();

  /// @brief checks if the list contains the parameter
  /// @return bool if the parameter is in the list
  /// @param the parameter to check
  bool contains(const T& item);

  /// @brief checks if the list contains an instance where the parameter is true
  /// @return bool if the parameter is true
  /// @param a function that returns a bool
  bool contains(std::function<bool(T&)> query);

  /// @brief determines the number of times the parameter appears in the list
  /// @return int
  /// @param the parameter to check
  int count(const T& item);

  /// @brief determines the number of times the parameter is true in the list
  /// @return int
  /// @param a function that returns a bool
  int count(std::function<bool(T&)> query);

  /// @brief for each item in the list, call a function with that item as a parameter
  /// @param a function that takes the items in the list
  void foreach(std::function<void(T&)> action);

  /// @brief creates a new list from the initial list using a mapping funciton
  /// @tparam U the type of the new list
  /// @param mapper a mapping function taking type T (the initial list type) and returning type U
  /// @return the new list
  template<typename U>
  List<U> map(std::function<U(T&)> mapper);

  /// @brief aggregates the list into a single output
  /// @param accumulator the function to run on each element, taking the result and the current element
  /// @return the results of the aggregation
  /// @throws std::out_of_range if the list is empty
  T aggregate(std::function<T(T&, T&)> accumulator);

  /// @brief aggregates the list into a single output
  /// @tparam U the type of the output
  /// @param start the starting value of the aggregation
  /// @param accumulator the function to run on each element, taking the result and the current element
  /// @return the results of the aggregation
  /// @throws std::out_of_range if the list is empty
  template<typename U>
  U aggregate(U start, std::function<U(U&, T&)> accumulator);

  /// @brief aggregates the list into a single output
  /// @tparam U the type of the output
  /// @param first A function to run on the first element to initialize the aggregation
  /// @param accumulator the function to run on each element, taking the result and the current element
  /// @return the results of the aggregation
  /// @throws std::out_of_range if the list is empty
  template<typename U>
  U aggregate(std::function<U(T&)> first, std::function<U(U&, T&)> accumulator);

  /*
   * Operators!
   * */

  List<T>& operator=(const List<T>& other);

  List<T>& operator=(List<T>&& other);

  List<T> operator+(const List<T>& other) const;

  List<T>& operator+=(const List<T>& other);

  bool operator==(const List<T>& other) const;

  bool operator!=(const List<T>& other) const;

  friend std::ostream& operator<< <>(std::ostream& out, const List<T>& theList);

  friend std::istream& operator>> <>(std::istream& in, List<T>& theList);

  /*
   * Iterators!
   * */
  ListIterator<T, int> begin();
 
  ListIterator<T, int> end();

  ConstListIterator<T, int> cbegin() const;

  ConstListIterator<T, int> cend() const;

  ListIterator<T, int> rbegin();

  ListIterator<T, int> rend();

  ConstListIterator<T, int> crbegin() const;

  ConstListIterator<T, int> crend() const;

private:
  
  void remove_node(Node<T>* node);

  void copy_from(const List<T>& other);

  void move_from(List<T>& other);

};

#include "l_list.inc"

#endif
