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
  copy_list(other);
}

TT LT::List(List&& other){
  move_list(other);
}

TT template<class ForwardIterator> LT::List(ForwardIterator begin, ForwardIterator end){
  //TODO
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
  Node temp = _head;
  _head = _head->next;
  delete _head->previous;
  --_size;
  return temp->data;
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
  Node temp = _tail;
  _tail = _tail->previous;
  delete _tail->next;
  --_size;
  return temp->data;
}

TT bool LT::remove(const T& item){
  if(_head==nullptr){ return false; }
  Node<T>* node = _head;
  for(size_t i = 0; i<_size; ++i){
    if(node->data==item){
      delete node;
      return true; 
    }
    node = node->next;
  }
  return false;
}

TT bool LT::remove(std::function<bool(T&)> query){
  if(_head==nullptr){ return false; }
  Node<T>* node = _head;
  for(size_t i = 0; i<_size; ++i){
    if(query(node->data)){
      delete node;
      return true;
    }
    node = node->next;
  }
  return false;
}

TT bool LT::remove_all(const T& item){
  if(_head==nullptr){ return false; }
  Node<T>* node = _head;
  bool track = false;
  for(size_t i = 0; i<_size; ++i){
    if(node->data==item){
      node = node->next;
      delete node->previous;
      track = true;
      continue;
    }
    node = node->next;
  }
  return track;
}

TT bool LT::remove_all(std::function<bool(T&)> query){
  if(_head==nullptr){ return false; }
  Node<T>* node = _head;
  bool track = false;
  for(size_t i = 0; i<_size; ++i){
    if(query(node->data)){
      node = node->next;
      delete node->previous;
      track = true;
      continue;
    }
    node = node->next;
  }
}

TT void LT::clear(){
  Node<T>* node = _head;
  for(size_t i = 0; i<_size-1; ++i){
    node = node->next;
    delete node->previous;
  }
  delete node;
  _size = 0;
}

TT bool LT::contains(const T& item){
  if(_head==nullptr){ return false; }
  Node<T>* node = _head;
  for(size_t i = 0; i<_size; ++i){
    if(node->data==item){
      return true;
    }
    node = node->next;
  }
  return false;
}

TT bool LT::contains(std::function<bool(T&)> query){
  if(_head==nullptr){ return false; }
  Node<T>* node = _head;
  for(size_t i = 0; i<_size; ++i){
    if(query(node->data)){
      return true;
    }
    node = node->next;
  }
  return false;
}

TT int LT::count(const T& item){
  if(_head==nullptr){ return false; }
  int count = 0;
  Node<T>* node = _head;
  for(size_t i = 0; i<_size; ++i){
    if(node->data==item){
      ++count;
    }
    node = node->next;
  }
  return count;
}

TT int LT::count(std::function<bool(T&)> query){
  if(_head==nullptr){ return false; }
  int count = 0;
  Node<T>* node = _head;
  for(size_t i = 0; i<_size; ++i){
    if(query(node->data)){
      ++count;
    }
    node = node->next;
  }
  return count;
}

TT void LT::foreach(std::function<void(T&)> action){
  Node<T>* node = _head;
  for(size_t i = 0; i<_size; ++i){
    action(node->data);
    node = node->next;
  }
}

TTU LU LT::map(std::function<U(T&)> mapper){
  LU newList;
  Node<T>* node = _head;
  for(size_t i = 0; i<_size; ++i){
    newList.push_back(mapper(node->data));
    node = node->next;
  }
  return newList;
}

TT T LT::aggregate(std::function<T(T&, T&)> accumulator){
  CHECK_NOT_EMPTY();
  Node<T>* node = _head;
  T result = node->data;
  node = node->next;
  for(size_t i = 0; i<_size; ++i){
    result = accumulator(result, node->data);
    node = node->next;
  }
  return result;
}

TTU U LT::aggregate(U start, std::function<U(U&, T&)> accumulator){
  CHECK_NOT_EMPTY();
  Node<T>* node = _head;
  U result = start;
  for(size_t i; i<_size; ++i){
    result = accumulator(result, node->data);
    node = node->next;
  }
  return result;
}

TTU U LT::aggregate(std::function<U(T&)> first, std::function<U(U&, T&)> accumulator){
  CHECK_NOT_EMPTY();
  Node<T>* node = _head;
  U result = first(node->data);
  node = node->next;
  for(size_t i; i<_size; ++i){
    result = accumulator(result, node->data);
    node = node->next;
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
  if(this!=other){
    if(_head!=nullptr){
      clear();
    }
    move_from(other);
  }
  return *this;
}

TT LT LT::operator+(const LT& other) const{
  LT newList = new List();
  Node<T>* node = _head;
  for(size_t i = 0; i<_size; ++i){
    newList.push_back(node->data);
    node = node->next;
  }
  node = other->_head;
  for(size_t i = 0; i<other->_size; ++i){
    newList.push_back(node->data);
    node = node->next;
  }
  return newList;
}

TT LT& LT::operator+=(const LT& other){
  Node<T>* node = other->_head;
  for(size_t i = 0; i<other._size; ++i){
    push_back(node->data);
    node = node->next;
  }
  return *this;
}

TT bool LT::operator==(const LT& other) const{
  if(_size==other->_size && other->_head !=nullptr && _head!=nullptr){
    Node<T>* nodeOther = other->_head;
    Node<T>* nodeSelf = _head;
    for(size_t i = 0; i<_size; ++i){
      if(nodeSelf->data != nodeOther->data){
        return false;
      }
      nodeSelf = nodeSelf->next;
      nodeOther = nodeOther->next;
    }
    return true;
  }
  if(other->head==nullptr && _head==nullptr){
    true;
  }
  return false;
}

TT bool LT::operator!=(const LT& other) const{
  if(_size==other->_size && other->_head !=nullptr && _head!=nullptr){
    Node<T>* nodeOther = other->_head;
    Node<T>* nodeSelf = _head;
    for(size_t i = 0; i<_size; ++i){
      if(nodeSelf->data != nodeOther->data){
        return true;
      }
      nodeSelf = nodeSelf->next;
      nodeOther = nodeOther->next;
    }
    return false;
  }
  if(other->_head==nullptr && _head==nullptr){
    return false;
  }
  return true;
}

TT std::ostream& operator<<(std::ostream& out, const LT& theList){
  Node<T>* node = theList->_head;
  for(size_t i = 0; i<theList->_size-1; ++i){
    out << node->data;
    out << " ";
    node = node->next;
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
 * Private Functions!
 * */

TT void LT::remove_node(Node<T>& node){
  //TODO
}

TT void LT::copy_from(const List<T>& other){
  Node<T>* nodeOther = other->_head;
  _size = other->_size;
  for(size_t i = 0; i<_size; ++i){
    push_back(nodeOther->data);
    nodeOther = nodeOther->next;
  }
}

TT void LT::move_from(List<T>&& other){
  _head = other->_head;
  other->_head = nullptr;
  _size = other->_size;
}
