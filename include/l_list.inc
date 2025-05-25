#include <functional>
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

/*
 * Member Functions!
 * */

TT T& LT::front(){
  //TODO
}

TT const T& LT::front() const{
  //TODO
}

TT T& LT::back(){
  //TODO
}

TT const T& LT::back() const{
  //TODO
}

TT bool LT::empty() const{
  //TODO
}

TT size_t LT::size() const{
  //TODO
}

TT void LT::push_front(const T& item){
  //TODO
}

TT T LT::pop_front(){
  //TODO
}

TT void LT::push_back(const T& item){
  //TODO
}

TT T LT::pop_back(){
  //TODO
}

TT bool LT::remove(const T& item){
  //TODO
}

TT bool LT::remove(std::function<bool(T&)> query){
  //TODO
}

TT bool LT::remove_all(const T& item){
  //TODO
}

TT bool LT::remove_all(std::function<bool(T&)> query){
  //TODO
}

TT void LT::clear(){
  //TODO
}

TT bool LT::contains(const T& item){
  //TODO
}

TT bool LT::contains(std::function<bool(T&)> query){
  //TODO
}

TT int LT::count(const T& item){
  //TODO
}

TT int LT::count(std::function<bool(T&)> query){
  //TODO
}

TT void LT::foreach(std::function<void(T&)> action){
  //TODO
}

TTU LU LT::map(std::function<U(T&)> mapper){
  //TODO
}

TT T LT::aggregate(std::function<T(T&, T&)> accumulator){
  //TODO
}

TTU U LT::aggregate(U start, std::function<U(U&, T&)> accumulator){
  //TODO
}

TTU U LT::aggregate(std::function<U(T&)> first, std::function<U(U&, T&)> accumulator){
  //TODO
}

/*
 * Operators!
 * */

TT LT& LT::operator=(const LT& other){
  //TODO
}

TT LT& LT::operator=(LT&& other){
  //TODO
}

TT LT LT::operator+(const LT& other) const{
  //TODO
}

TT LT& LT::operator+=(const LT& other){
  //TODO
}

TT bool LT::operator==(const LT& other) const{
  //TODO
}

TT bool LT::operator!=(const LT& other) const{
  //TODO
}

TT std::ostream& operator<<(std::ostream& out, const LT& theList){
  //TODO
}

TT std::istream& operator>>(std::istream& in, LT& theList){
  //TODO
}

/*
 * Private Functions!
 * */

TT void LT::remove_node(Node<T>& node){
  //TODO
}

TT void LT::copy_list(const LT& other){
  //TODO
}

TT void LT::move_list(LT&& other){
  //TODO
}
