#include <stdexcept>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include<string>
#include<sstream>
#include "../include/doctest/doctest.h"
#include "../include/gravedata.h"
#include "../include/l_list.h"
#include<iostream>

using gint = ian::GraveData;
using gilist = List<gint>;

gilist create_list(int* data, int cap){
  gilist myList;
  for(int i = 0; i<cap; ++i){
    myList.push_back(*(data+i));
  }
  return myList;
}

  ///////////////////////
 /// Constructors //////
///////////////////////
TEST_SUITE("constructors"){
  TEST_CASE("test default constructor"){
    gint::init();

    gilist* list = new gilist;

    CHECK_EQ(0, gint::count());
    CHECK_EQ(0, list->size());

    delete list;
  }

  TEST_CASE("test destructor empty"){
    gilist* list = new gilist;
    delete list;
  }

  TEST_CASE("test destructor 1"){
    gint::init();

    gilist* list = new gilist;

    list->push_back(1);

    delete list;

    CHECK_EQ(0, gint::count());
  }

  TEST_CASE("test destructor 2"){
    gint::init();

    gilist* list = new gilist;

    list->push_back(1);
    list->push_back(2);

    delete list;

    CHECK_EQ(0, gint::count());
  }

  TEST_CASE("test destrcuctor 3"){
    gint::init();

    gilist* list = new gilist;

    list->push_back(1);
    list->push_back(2);
    list->push_back(3);

    delete list;

    CHECK_EQ(0, gint::count());
  }

  TEST_CASE("test copy constructor"){
    gint::init();

    int data[] = { 2, 3, 5, 7, 11 };
    gilist* firstList = new gilist(data, data+5);

    gilist* secondList = new gilist(*firstList);
  
    CHECK_EQ(firstList->size(), secondList->size());
    CHECK_EQ(firstList, secondList);
    CHECK_EQ(10, gint::count());

    delete firstList;

    CHECK_EQ(5, secondList->size());
    CHECK_EQ(5, gint::count());

    delete secondList;
  }

  TEST_CASE("test move constructor"){
    gint::init();

    int data[] = { 2, 3, 5, 7, 11 };
    gilist firstList(create_list(data, 5));

    CHECK_EQ(5, gint::count());

    auto changes = gint::changes();
    CHECK_EQ(5, changes.increments);
    CHECK_EQ(0, changes.decrements);
  }

  TEST_CASE("test iterator constructor"){
    gint::init();

    int data[] = { 2, 3, 5, 7, 11 };
    gilist list(data, data+5);

    CHECK_EQ(5, list.size());

    auto it = list.begin();
    for(int i = 0; i<5; ++i){
      CHECK_EQ(data[i], *it);
      ++it;
    }

    CHECK_EQ(list.end(), it);
  }

    //////////////////////
   /// Methods //////////
  //////////////////////
  TEST_CASE("test front"){
    gilist list;

    CHECK_THROWS(list.front());

    list.push_back(1);

    CHECK_EQ(1, list.front());

    list.push_back(2);

    CHECK_EQ(1, list.front());

    list.push_back(3);

    CHECK_EQ(1, list.front());
  }

  TEST_CASE("test back"){
    gilist list;

    CHECK_THROWS(list.back());

    list.push_back(1);

    CHECK_EQ(1, list.back());

    list.push_back(2);

    CHECK_EQ(2, list.back());

    list.push_back(3);

    CHECK_EQ(3, list.back());
  }

  TEST_CASE("test empty"){
    gilist list;

    CHECK_EQ(true, list.empty());
    
    list.push_back(1);

    CHECK_EQ(false, list.empty());
  }

  TEST_CASE("test size"){
    gilist list;

    CHECK_EQ(0, list.size());

    list.push_back(1);

    CHECK_EQ(1, list.size());

    list.push_back(2);

    CHECK_EQ(2, list.size());
  }

  TEST_CASE("test push_front"){
gilist list;

    list.push_front(1);

    CHECK_EQ(1, list.front());
    CHECK_EQ(1, list.back());
    CHECK_EQ(1, list.size());

    list.push_front(2);
    
    CHECK_EQ(2, list.front());
    CHECK_EQ(1, list.back());
    CHECK_EQ(2, list.size());

    list.push_front(3);

    CHECK_EQ(3, list.front());
    CHECK_EQ(true, list.contains(2));
    CHECK_EQ(1, list.back());
    CHECK_EQ(3, list.size());
  }

  TEST_CASE("test pop_front"){
    int data[] = { 2, 3, 5, 7, 11 };
    gilist list(data, data+5);

    auto popped = list.pop_front();

    CHECK_EQ(3, list.front());
    CHECK_EQ(4, list.size());
    CHECK_EQ(2, popped);
  }

  TEST_CASE("test pop_front with empty list"){
    gilist list;

    CHECK_THROWS(list.pop_front());
  }

  TEST_CASE("test push_back"){
    gilist list;

    list.push_back(1);

    CHECK_EQ(1, list.front());
    CHECK_EQ(1, list.back());
    CHECK_EQ(1, list.size());

    list.push_back(2);
    
    CHECK_EQ(1, list.front());
    CHECK_EQ(2, list.back());
    CHECK_EQ(2, list.size());

    list.push_back(3);

    CHECK_EQ(1, list.front());
    CHECK_EQ(true, list.contains(2));
    CHECK_EQ(3, list.back());
    CHECK_EQ(3, list.size());
  }

  TEST_CASE("test pop_back"){
    int data[] = { 2, 3, 5, 7, 11 };
    gilist list(data, data+5);

    auto popped = list.pop_back();

    CHECK_EQ(7, list.back());
    CHECK_EQ(4, list.size());
    CHECK_EQ(11, popped);
  }

  TEST_CASE("test pop_back with empty list"){
    gilist list;

    CHECK_THROWS(list.pop_back());
  }

  TEST_CASE("test remove"){
    gint::init();

    gilist list;

    CHECK_EQ(false, list.remove(1));

    list.push_back(1);
    list.push_back(2);

    CHECK_EQ(true, list.remove(1));
    CHECK_EQ(2, list.front());
    CHECK_EQ(1, gint::count());

    CHECK_EQ(true, list.remove(2));
    CHECK_EQ(true, list.empty());
    CHECK_EQ(0, gint::count());
  }

  TEST_CASE("test remove query"){
    //TODO
  }

  TEST_CASE("test remove_all"){
    gilist list;

    CHECK_EQ(false, list.remove_all(1));

    list.push_back(1);
    list.push_back(2);
    list.push_back(1);
    list.push_back(2);

    CHECK_EQ(true, list.remove_all(1));
    CHECK_EQ(false, list.contains(1));
    CHECK_EQ(2, list.size());

    CHECK_EQ(true, list.remove_all(2));
    CHECK_EQ(true, list.empty());
  }

  TEST_CASE("test remove_all query"){
    //TODO
  }

  TEST_CASE("test clear"){
    gint::init();

    int data[] = { 2, 3, 5, 7, 11 };
    gilist list(data, data+5);

    CHECK_EQ(5, gint::count());

list.clear();

    CHECK_EQ(0, list.size());
    CHECK_EQ(true, list.empty());
    CHECK_EQ(0, gint::count());
  }

  TEST_CASE("test contains"){
    int data[] = { 2, 3, 5, 7, 11 };
    gilist list(data, data+5);

    CHECK_EQ(false, list.contains(1));
    CHECK_EQ(true, list.contains(2));
    CHECK_EQ(true, list.contains(5));
  }

  TEST_CASE("test contains query"){
    //TODO
  }

  TEST_CASE("test count"){
    int data[] = { 2, 3, 3, 7, 11 };
    gilist list(data, data+5);

    CHECK_EQ(0, list.contains(5));
    CHECK_EQ(1, list.contains(2));
    CHECK_EQ(2, list.contains(3));
  }

  TEST_CASE("test count query"){
    //TODO
  }

  TEST_CASE("test foreach"){
    //TODO
  }

  TEST_CASE("test map"){
    //TODO
  }

  TEST_CASE("aggregate"){
    //TODO
  }

  TEST_CASE("aggregate start"){
    //TODO
  }

  TEST_CASE("aggregate first"){
    //TODO
  }

    //////////////////
   // Operators /////
  //////////////////
  TEST_CASE("copy operator"){
    //TODO
  }

  TEST_CASE("move operator"){
    //TODO
  }

  TEST_CASE("operator+"){
    //TODO
  }

  TEST_CASE("operator+="){
    //TODO
  }

  TEST_CASE("operator=="){
    //TODO
  }

  TEST_CASE("operator!="){
    //TODO
  }

  TEST_CASE("operator<<"){
    //TODO
  }

  TEST_CASE("operator>>"){
    //TODO
  }
}
