#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H
#include<functional>
#include <iterator>

#define ITB typename ListIteratorBase<T, sizeT, T&, T*>
#define CITB typename ListIteratorBase<T, sizeT, const T&, const T*>

template<typename T>
class Node;

template<typename T>
class List;

template<typename T, typename sizeT, typename refT, typename ptrT>
class ListIteratorBase{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = size_t;
  using size_type = sizeT;
  using value_type = T;
  using pointer = ptrT;
  using reference = refT;

  using self = ListIteratorBase<T, sizeT, refT, ptrT>;

  self& operator ++(); //prefix
  self operator ++(int); //postfix

  self& operator --();
  self operator --(int);

  reference operator * ();

  pointer operator -> ();

  self& operator = (const self& other);

  bool operator == (const self& other);
  bool operator != (const self& other); 

protected:
  ListIteratorBase(Node<T>* node, bool isReverse);
  ListIteratorBase(const self& other);

private:
  Node<T>* node;
  bool isReverse;
};

template<typename T, typename sizeT>
class ListIterator: public ListIteratorBase<T, sizeT, T&, T*>{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = ITB::difference_type;
  using size_type = ITB::size_type;
  using value_type = ITB::value_type;
  using pointer = ITB::pointer;
  using reference = ITB::reference;

  friend class List<T>;

private:
  ListIterator(Node<T>* node, bool isReverse);
  ListIterator(const ListIterator<T, sizeT>& other);
};

template<typename T, typename sizeT>
class ConstListIterator: public ListIteratorBase<T, sizeT, const T&, const T*>{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = CITB::difference_type;
  using size_type = CITB::size_type;
  using value_type = CITB::value_type;
  using pointer = CITB::pointer;
  using reference = CITB::reference;

  friend class List<T>;

private:
  ConstListIterator(Node<T>* node, bool isReverse);
  ConstListIterator(const ConstListIterator<T, sizeT>& other);
};

#undef ITB
#undef CITB

#include "list_iterator.inc"

#endif
