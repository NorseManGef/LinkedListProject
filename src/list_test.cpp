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

TEST_SUITE("constructors"){
  TEST_CASE("test default constructor"){
    gint::init();

    gilist* list = new gilist;

    CHECK_EQ(0, gint::count());
    CHECK_EQ(0, list->size());

    delete list;
  }

  TEST_CASE("test destructor with empty list"){
    gint::init();

    gilist* list = new gilist;

    delete list;

    CHECK_EQ(0, gint::count());
  }

  TEST_CASE("test destructor with singly item-ed list"){
    gint::init();

    gilist* list = new gilist;

    list->push_back(1);

    delete list;

    CHECK_EQ(0, gint::count());
  }

  TEST_CASE("test destructor with multi item-ed list"){
    gint::init();

    gilist* list = new gilist;

    list->push_back(1);
    list->push_back(2);

    delete list;

    CHECK_EQ(0, gint::count());
  }

  TEST_CASE("test copy constructor with empty list"){
    gint::init();

    gilist list;
    gilist otherList(list);

    CHECK_EQ(list.size(), otherList.size());
    CHECK_EQ(0, gint::count());
  }

  TEST_CASE("test copy constructor with singly item-ed list"){
    gint::init();

    gilist list;
    list.push_back(1);
    gilist otherList(list);

    CHECK_EQ(2, gint::count());
    CHECK_EQ(list.size(), otherList.size());
    CHECK_EQ(list, otherList);
  }

  TEST_CASE("test copy constructor with multi item-ed list"){
    gint::init();
    
    gilist list;
    list.push_back(1);
    list.push_back(2);
    gilist otherList(list);

    CHECK_EQ(4,gint::count());
    CHECK_EQ(list.size(), otherList.size());
    CHECK_EQ(list, otherList);
  }
}

TEST_SUITE("Operators!"){
  //TODO
}

TEST_SUITE("methods"){
  //TODO
}


