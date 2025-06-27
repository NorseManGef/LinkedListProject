#include <functional>
#include <iterator>
#include <sstream>
#include<stdexcept>

#pragma once

#ifdef CLANGD_ONLY
#include"l_list.h"
#endif

#define TT template<typename T>
#define TU template<typename U>
#define TTU TT TU
#define LT List<T>
#define LU List<U>

#define IT ListIterator<T, int>
#define CIT ConstListIterator<T, int>

#define CHECK_NOT_EMPTY() if(_size==0) throw std::out_of_range("list is empty")

/*
 * Constructors!
 * */

TT LT::List():
  _head(nullptr),
  _tail(nullptr),
  _size(0)
{}

TT LT::List(const List& other){
  copy_from(other);
}

TT LT::List(List&& other){
  move_from(other);
}

TT template<class ForwardIterator> LT::List(ForwardIterator begin, ForwardIterator end):
  _head(nullptr),
  _tail(nullptr),
  _size(0)
{
  for(ForwardIterator current = begin; current!=end; ++current){
    push_back(*current);
  }
}

TT LT::~List(){
  clear();
}

TT Node<T>::Node(const T& dat):
  data(dat),
  next(nullptr),
  previous(nullptr)
{}

/*
 * Member Functions!
 * */

TT T& LT::front(){
  CHECK_NOT_EMPTY();
  return _head->data;
}

TT const T& LT::front() const{
  CHECK_NOT_EMPTY();
  return _head->data;
}

TT T& LT::back(){
  CHECK_NOT_EMPTY();
  return _tail->data;
}

TT const T& LT::back() const{
  CHECK_NOT_EMPTY();
  return _tail->data;
}

TT bool LT::empty() const{
  return _size==0;
}

TT size_t LT::size() const{
  return _size;
}

TT void LT::push_front(const T& item){
  Node<T>* newNode = new Node(item);
  if(_head==nullptr){
    _head = newNode;
    _tail = newNode;
  } else {
    newNode->next = _head;
    _head->previous = newNode;
    _head = newNode;
  }
  ++_size;
}

TT T LT::pop_front(){
  CHECK_NOT_EMPTY();
  T temp = _head->data;
  if(_head==_tail){
    delete _head;
    _head = nullptr;
  } else {
    _head = _head->next;
    delete _head->previous;
    _head->previous = nullptr;
  }
  --_size;
  return temp; 
}

TT void LT::push_back(const T& item){
  Node<T>* newNode = new Node(item);
  if(_tail==nullptr){
    _head = newNode;
    _tail = newNode;
  } else {
    newNode->previous = _tail;
    _tail->next = newNode;
    _tail = newNode;
  }
  ++_size;
}

TT T LT::pop_back(){
  CHECK_NOT_EMPTY();
  T temp = _tail->data;
  if(_head==_tail){
    delete _tail;
    _tail = nullptr;
    _head = nullptr; // makes sure other functions know the list is empty
  } else {
    _tail = _tail->previous;
    delete _tail->next;
    _tail->next = nullptr;
  }
  --_size;
  return temp; 
}

TT bool LT::remove(const T& item){
  if(_head==nullptr){ return false; }
  for(Node<T>* node = _head; node!=nullptr; node = node->next){
    if(node->data==item){
      remove_node(*node);
      return true; 
    }
  }
  return false;
}

TT bool LT::remove(std::function<bool(T&)> query){
  if(_head==nullptr){ return false; }
  for(Node<T>* node = _head; node!=nullptr; node = node->next){
    if(query(node->data)){
      remove_node(node);
      return true;
    }
  }
  return false;
}

TT bool LT::remove_all(const T& item){
  if(_head==nullptr){ return false; }
  bool track = false;
  for(Node<T>* node = _head; node!=nullptr; node = node->next){
    if(node->data==item){
      node = node->next;
      remove_node(*(node->previous));
      track = true;
      continue;
    }
    node = node->next;
  }
  return track;
}

TT bool LT::remove_all(std::function<bool(T&)> query){
  if(_head==nullptr){ return false; }
  bool track = false;
  for(Node<T>* node = _head; node!=nullptr; node = node->next){
    if(query(node->data)){
      node = node->next;
      remove_node(node->previous);
      track = true;
      continue;
    }
    node = node->next;
  }
}

TT void LT::clear(){
  while(_head!=nullptr){
    Node<T>* node = _head;
    _head = _head->next;
    delete node;
  }
  _size = 0;
}

TT bool LT::contains(const T& item){
  if(_head==nullptr){ return false; }
  for(Node<T>* node = _head; node!=nullptr; node = node->next){
    if(node->data==item){
      return true;
    }
  }
  return false;
}

TT bool LT::contains(std::function<bool(T&)> query){
  if(_head==nullptr){ return false; }
  for(Node<T>* node = _head; node!=nullptr; node = node->next){
    if(query(node->data)){
      return true;
    }
  }
  return false;
}

TT int LT::count(const T& item){
  if(_head==nullptr){ return false; }
  int count = 0;
  for(Node<T>* node = _head; node!=nullptr; node = node->next){
    if(node->data==item){
      ++count;
    }
  }
  return count;
}

TT int LT::count(std::function<bool(T&)> query){
  if(_head==nullptr){ return false; }
  int count = 0;
  for(Node<T>* node = _head; node!=nullptr; node = node->next){
    if(query(node->data)){
      ++count;
    }
  }
  return count;
}

TT void LT::foreach(std::function<void(T&)> action){
  for(Node<T>* node = _head; node!=nullptr; node = node->next){
    action(node->data);
  }
}

TTU LU LT::map(std::function<U(T&)> mapper){
  LU newList; 
  for(Node<T>* node = _head; node!=nullptr; node = node->next){
    newList.push_back(mapper(node->data));
  }
  return newList;
}

TT T LT::aggregate(std::function<T(T&, T&)> accumulator){
  CHECK_NOT_EMPTY();
  Node<T>* node = _head;
  T result = node->data;
  node = node->next;
  for(; node!=nullptr; node = node->next){
    result = accumulator(result, node->data);
  }
  return result;
}

TTU U LT::aggregate(U start, std::function<U(U&, T&)> accumulator){
  CHECK_NOT_EMPTY();
  U result = start;
  for(Node<T>* node = _head; node!=nullptr; node = node->next){
    result = accumulator(result, node->data);
  }
  return result;
}

TTU U LT::aggregate(std::function<U(T&)> first, std::function<U(U&, T&)> accumulator){
  CHECK_NOT_EMPTY();
  Node<T>* node = _head;
  U result = first(node->data);
  node = node->next;
  for(; node!=nullptr; node = node->next){
    result = accumulator(result, node->data);
  }
  return result;
}

/*
 * Operators!
 * */

TT LT& LT::operator=(const LT& other){
  if(this!=other){
    if(_head!=nullptr){
      clear();
    }
    copy_from(other);
  }
  return *this;
}

TT LT& LT::operator=(LT&& other){
  if(*this!=other){
    clear();
    move_from(other);
  }
  return *this;
}

TT LT LT::operator+(const LT& other) const{
  LT newList;
  for(Node<T>* node = _head; node!=nullptr; node = node->next){
    newList.push_back(node->data);
  }
  for(Node<T>* node = other._head; node!=nullptr; node = node->next){
    newList.push_back(node->data);
  }
  return newList;
}

TT LT& LT::operator+=(const LT& other){ 
  for(Node<T>* node = other._head; node!=nullptr; node = node->next){
    push_back(node->data);
  }
  return *this;
}

TT bool LT::operator==(const LT& other) const{
  if(_size!=other._size){ return false; }
  Node<T>* nodeSelf = _head;
  Node<T>* nodeOther = other._head;
  while(nodeSelf!=nullptr && nodeOther!=nullptr){
    if(nodeSelf->data != nodeOther->data){
      return false;
    }
    
    nodeSelf = nodeSelf->next;
    nodeOther = nodeOther->next;
  }
  return true;
}

TT bool LT::operator!=(const LT& other) const{
  if(_size==other._size && other._head !=nullptr && _head!=nullptr){
    Node<T>* nodeOther = other._head;
    for(Node<T>* nodeSelf = _head; nodeSelf!=nullptr; nodeSelf = nodeSelf->next){
      if(nodeSelf->data != nodeOther->data){
        return true;
      }
      nodeOther = nodeOther->next;
    }
    return false;
  }
  if(other._head==nullptr && _head==nullptr){
    return false;
  }
  return true;
}

TT std::ostream& operator<<(std::ostream& out, const LT& theList){
  Node<T>* node = theList._head;
  for(; node->next!=nullptr; node=node->next){
    out << node->data;
    out << " ";
  }
  out << node->data;
  return out;
}

TT std::istream& operator>>(std::istream& in, LT& theList){
  std::string theString;
  std::getline(in, theString);

  std::stringstream str(theString);
  theList.push_back(std::istream_iterator<T>(str), std::istream_iterator<T>());
  return in;
}

/*
 * Iterators!
 * */

TT IT LT::begin(){
  return IT(_head, false);
}

TT IT LT::end(){
  return IT(_tail, false);
}

TT CIT LT::cbegin() const{
  return CIT(_head, false);
}

TT CIT LT::cend() const{
  return CIT(_tail, false);
}

TT IT LT::rbegin(){
  return IT(_head, true);
}

TT IT LT::rend(){
  return IT(_tail, true);
}

TT CIT LT::crbegin() const{
  return CIT(_head, true);
}

TT CIT LT::crend() const{
  return CIT(_tail, true);
}

/*
 * Private Functions!
 * */

TT void LT::remove_node(Node<T>& node){
  if(node.previous != nullptr) node.previous->next = node.next;
  else _head = node.next;
  if(node.next != nullptr) node.next->previous = node.previous;
  else _tail = node.previous;
  --_size;
}

TT void LT::copy_from(const List<T>& other){
  for(Node<T>* nodeOther = other._head; nodeOther!=nullptr; nodeOther = nodeOther->next){
    push_back(nodeOther->data);
  }
  _size = other._size;
}

TT void LT::move_from(List<T>& other){
  _head = other._head;
  _tail = other._tail;
  other._head = nullptr;
  other._tail = nullptr;
  _size = other._size;
  other._size = 0;
}
