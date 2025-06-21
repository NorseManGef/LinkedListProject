#pragma once

#include "list_iterator.h"

#define TTSRP template<typename T, typename sizeT, typename refT, typename ptrT>
#define ITB ListIteratorBase<T, sizeT, refT, ptrT>
#define ITBT TTSRP ITB
#define TURP template<typename U, typename sizeU, typename refU, typename ptrU>
#define ITBU ListIteratorBase<U, sizeU, refU, ptrU>

#define TTS template<typename T, typename sizeT>
#define ITP ListIteratorBase<T, sizeT, T&, T*>
#define ITV ListIterator<T, sizeT>
#define ITVT TTS ITV
#define ITC ConstListIterator<T, sizeT>
#define ITCT TTS ITC

TTSRP typename ITB::self& ITB::operator ++(){ //prefix
  if(isReverse){
    node = node->previous;
  } else {
    node = node->next;
  }
  return *this;
}

TTSRP typename ITB::self ITB::operator ++(int){ //postfix
  self tempIt(*this);
  if(isReverse){
    node = node->previous;
  } else {
    node = node->next;
  }
  return tempIt;
}

TTSRP typename ITB::self& ITB::operator --(){
  if(isReverse){
    node = node->next;
  } else {
    node = node->previous;
  }
  return *this;
}

TTSRP typename ITB::self ITB::operator --(int){
  self tempIt(*this);
  if(isReverse){
    node = node->next;
  } else {
    node = node->previous;
  }
  return tempIt;
}

TTSRP typename ITB::reference ITB::operator * (){
  return node->data; //This might be wrong.
}

TTSRP typename ITB::pointer ITB::operator -> (){
  return node->data; //This might be wrong.
}

TTSRP typename ITB::self& ITB::operator = (const self& other){
  if(&other != this){
    node = other.node;
    isReverse = other.isReverse;
  }
  return *this;
}

TTSRP bool ITB::operator == (const self& other) const{
  return node == other.node && isReverse == other.isReverse;
}

TTSRP bool ITB::operator != (const self& other) const{
  return node != other.node || isReverse != other.isReverse;
}

ITBT::ListIteratorBase(Node<T>* node, bool isReverse):
  node(node),
  isReverse(isReverse)
{}

ITBT::ListIteratorBase(const self& other):
  node(other.node),
  isReverse(other.isReverse)
{}

ITVT::ListIterator(Node<T>* node, bool isReverse):
  ITP(node, isReverse)
{}

ITVT::ListIterator(const ITV& other):
  ITP(other.node, other.isReverse)
{}

ITCT::ConstListIterator(Node<T>* node, bool isReverse):
  ITP(node, isReverse)
{}

ITCT::ConstListIterator(const ITC& other):
  ITP(other.node, other.isReverse)
{}

#undef ITCT
#undef ITC
#undef ITVT
#undef ITV
#undef ITP
#undef TTS

#undef ITBU
#undef TURP
#undef ITBT
#undef ITB
#undef TTSRP
