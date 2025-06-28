#include <stdexcept>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest/doctest.h"
#include "../include/gravedata.h"
#include "../include/l_list.h"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

using gint = ian::GraveData;
using gilist = List<gint>;

gilist create_list(const int *data, int cap) {
	gilist myList;
	for (int i = 0; i < cap; ++i) {
		myList.push_back(*(data + i));
	}
	return myList;
}

TEST_SUITE("constructors") {
	TEST_CASE("test default constructor") {
		gint::init();

		gilist *list = new gilist;

		CHECK_EQ(0, gint::count());
		CHECK_EQ(0, list->size());

		delete list;
	}

	TEST_CASE("test destructor with empty list") {
		gint::init();

		gilist *list = new gilist;

		delete list;

		CHECK_EQ(0, gint::count());
	}

	TEST_CASE("test destructor with singly item-ed list") {
		gint::init();

		gilist *list = new gilist;

		list->push_back(1);

		delete list;

		CHECK_EQ(0, gint::count());
	}

	TEST_CASE("test destructor with multi item-ed list") {
		gint::init();

		gilist *list = new gilist;

		list->push_back(1);
		list->push_back(2);

		delete list;

		CHECK_EQ(0, gint::count());
	}

	TEST_CASE("test copy constructor with empty list") {
		gint::init();

		gilist list;
		gilist otherList(list);

		CHECK_EQ(list.size(), otherList.size());
		CHECK_EQ(0, gint::count());
	}

	TEST_CASE("test copy constructor with singly item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);
		gilist otherList(list);

		CHECK_EQ(2, gint::count());
		CHECK_EQ(list.size(), otherList.size());
		CHECK_EQ(list, otherList);
	}

	TEST_CASE("test copy constructor with multi item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);
		list.push_back(2);
		gilist otherList(list);

		CHECK_EQ(4, gint::count());
		CHECK_EQ(list.size(), otherList.size());
		CHECK_EQ(list, otherList);
	}

	TEST_CASE("test move constructor with empty list") {
		gint::init();

		gilist list;
		gilist newList(std::move(list));

		CHECK_EQ(0, gint::count());
		CHECK_EQ(0, newList.size());
	}

	TEST_CASE("test move constructor with singly item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);
		gilist newList(std::move(list));

		CHECK_EQ(1, gint::count());
		CHECK_EQ(1, newList.size());
		CHECK_EQ(1, newList.front());
	}

	TEST_CASE("test move constructor with multi item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);
		list.push_back(2);
		gilist newList(std::move(list));

		CHECK_EQ(2, gint::count());
		CHECK_EQ(2, newList.size());
		CHECK_EQ(1, newList.front());
		CHECK_EQ(2, newList.back());
	}

	TEST_CASE("test iterator constructor with empty list") {
		gint::init();

		int data[] = {};

		gilist list(data, data);

		CHECK_EQ(0, list.size());
		CHECK_EQ(0, gint::count());
	}

	TEST_CASE("test iterator constructor with singly item-ed list") {
		gint::init();

		int data[1] = {1};

		gilist list(data, data + 1);

		CHECK_EQ(1, list.size());
		CHECK_EQ(1, gint::count());
		CHECK_EQ(1, list.front());
	}

	TEST_CASE("test iterator constructor with multi item-ed list") {
		gint::init();

		int data[2] = {1, 2};

		gilist list(data, data + 2);

		CHECK_EQ(2, gint::count());
		CHECK_EQ(2, list.size());
		CHECK_EQ(1, list.front());
		CHECK_EQ(2, list.back());
	}
}

TEST_SUITE("Operators!") {
	TEST_CASE("test copy operator with empty list") {
		gint::init();

		gilist list;

		gilist newList = list;

		CHECK_EQ(0, newList.size());
		CHECK_EQ(0, gint::count());
	}

	TEST_CASE("test copy operator with singly item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);
		gilist newList = list;

		CHECK_EQ(1, newList.size());
		CHECK_EQ(2, gint::count());
		CHECK_EQ(1, newList.front());
	}

	TEST_CASE("test copy operator with multi item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);
		list.push_back(2);
		gilist newList = list;

		CHECK_EQ(2, newList.size());
		CHECK_EQ(4, gint::count());
		CHECK_EQ(1, newList.front());
		CHECK_EQ(2, newList.back());
	}

	TEST_CASE("test move operator with empty list") {
		gint::init();

		gilist list;
		gilist newList = std::move(list);

		CHECK_EQ(0, gint::count());
		CHECK_EQ(0, newList.size());
	}

	TEST_CASE("test move operator with singly item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);
		gilist newList = std::move(list);

		CHECK_EQ(1, gint::count());
		CHECK_EQ(1, newList.size());
		CHECK_EQ(1, newList.front());
	}

	TEST_CASE("test move operator with multi item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);
		list.push_back(2);
		gilist newList = std::move(list);

		CHECK_EQ(2, gint::count());
		CHECK_EQ(2, newList.size());
		CHECK_EQ(1, newList.front());
		CHECK_EQ(2, newList.back());
	}

	TEST_CASE("test append operator with empty list") {
		gint::init();

		gilist list;
		gilist newList;
		gilist finalList = list + newList;

		CHECK_EQ(0, gint::count());
		CHECK_EQ(0, finalList.size());
	}

	TEST_CASE("test append operator with singly item-ed list") {
		gint::init();

		gilist list;
		gilist newList;
		list.push_back(1);
		newList.push_back(2);
		gilist finalList = list + newList;

		CHECK_EQ(4, gint::count());
		CHECK_EQ(2, finalList.size());
		CHECK_EQ(1, finalList.front());
		CHECK_EQ(2, finalList.back());
	}

	TEST_CASE("test append operator with multi item-ed list") {
		gint::init();

		gilist list;
		gilist newList;
		list.push_back(1);
		list.push_back(2);
		newList.push_back(3);
		newList.push_back(4);

		gilist finalList = list + newList;

		CHECK_EQ(8, gint::count());
		CHECK_EQ(4, finalList.size());

		auto it = finalList.begin();
		CHECK_EQ(1, *it);
		++it;
		CHECK_EQ(2, *it);
		++it;
		CHECK_EQ(3, *it);
		++it;
		CHECK_EQ(4, *it);
	}

	TEST_CASE("test append equals operator with empty list") {
		gint::init();

		gilist list;
		gilist newList;
		newList += list;

		CHECK_EQ(0, gint::count());
		CHECK_EQ(0, newList.size());
	}

	TEST_CASE("test append equals operator with singly item-ed list") {
		gint::init();

		gilist list;
		list.push_back(2);
		gilist newList;
		newList.push_back(1);
		newList += list;

		CHECK_EQ(3, gint::count());
		CHECK_EQ(2, newList.size());
		CHECK_EQ(1, newList.front());
		CHECK_EQ(2, newList.back());
	}

	TEST_CASE("test append equals operator with multi item-ed list") {
		gint::init();

		gilist list;
		list.push_back(3);
		list.push_back(4);
		gilist newList;
		newList.push_back(1);
		newList.push_back(2);
		newList += list;

		CHECK_EQ(6, gint::count());
		CHECK_EQ(4, newList.size());

		auto it = newList.begin();
		CHECK_EQ(1, *it);
		++it;
		CHECK_EQ(2, *it);
		++it;
		CHECK_EQ(3, *it);
		++it;
		CHECK_EQ(4, *it);
	}

	TEST_CASE("test equality operator with empty list") {
		gilist list;
		gilist newList;

		CHECK(list == newList);
	}

	TEST_CASE("test false equality operator with singly item-ed list") {
		gilist list;
		list.push_back(1);
		gilist newList;
		newList.push_back(2);

		CHECK_FALSE(list == newList);
	}

	TEST_CASE("test true equality operator with singly item-ed list") {
		gilist list;
		list.push_back(1);
		gilist newList;
		newList.push_back(1);

		CHECK(list == newList);
	}

	TEST_CASE("test false equality operator with multi item-ed list") {

		gilist list;
		list.push_back(1);
		list.push_back(2);
		gilist newList;
		newList.push_back(1);
		newList.push_back(3);

		CHECK_FALSE(list == newList);
	}

	TEST_CASE("test true equality operator with multi item-ed list") {
		gilist list;
		list.push_back(1);
		list.push_back(2);
		gilist newList;
		newList.push_back(1);
		newList.push_back(2);

		CHECK(list == newList);
	}

	TEST_CASE("test inequality operator with empty list") {
		gilist list;
		gilist newList;

		CHECK_FALSE(list != newList);
	}

	TEST_CASE("test false inequality operator with singly item-ed list") {
		gilist list;
		list.push_back(1);
		gilist newList;
		newList.push_back(1);

		CHECK_FALSE(list != newList);
	}

	TEST_CASE("test true inequality operator with singly item-ed list") {
		gilist list;
		list.push_back(1);
		gilist newList;
		newList.push_back(2);

		CHECK(list != newList);
	}

	TEST_CASE("test false inequality operator with multi item-ed list") {
		gilist list;
		list.push_back(1);
		list.push_back(2);

		gilist newList;
		newList.push_back(1);
		newList.push_back(2);

		CHECK_FALSE(list != newList);
	}

	TEST_CASE("test true inequality operator with multi item-ed list") {
		gilist list;
		list.push_back(1);
		list.push_back(2);

		gilist newList;
		newList.push_back(1);
		newList.push_back(3);

		CHECK(list != newList);
	}

	TEST_CASE("test stream insertion operator") {
		gint::init();

		int data[] = {1, 2, 3, 4, 5};
		const std::string datstr = "1 2 3 4 5";
		std::stringstream stream;

		gilist list(data, data + 5);

		stream << list;

		std::string lstring = stream.str();

		CHECK_EQ(datstr, lstring);
	}

	TEST_CASE("test stream extraction operator") {}
}

TEST_SUITE("methods") {
	TEST_CASE("test front with empty list") {
		gilist list;
		CHECK_THROWS(list.front());
	}

	TEST_CASE("test front with singly item-ed list") {
		gilist list;
		list.push_back(1);

		CHECK_EQ(1, list.front());
	}

	TEST_CASE("test front with multi item-ed list") {
		gilist list;
		list.push_back(1);
		list.push_back(2);

		CHECK_EQ(1, list.front());
	}

	TEST_CASE("test back with empty list") {
		gilist list;
		CHECK_THROWS(list.back());
	}

	TEST_CASE("test back with singly item-ed list") {
		gilist list;
		list.push_back(1);

		CHECK_EQ(1, list.back());
	}

	TEST_CASE("test back with multi item-ed list") {
		gilist list;
		list.push_back(1);
		list.push_back(2);

		CHECK_EQ(2, list.back());
	}

	TEST_CASE("test empty with empty list") {
		gilist list;
		CHECK(list.empty());
	}

	TEST_CASE("test empty with non empty list") {
		gilist list;
		list.push_back(1);

		CHECK_FALSE(list.empty());
	}

	TEST_CASE("test size with empty list") {
		gilist list;

		CHECK_EQ(0, list.size());
	}

	TEST_CASE("test size with singly item-ed list") {
		gilist list;
		list.push_back(1);

		CHECK_EQ(1, list.size());
	}

	TEST_CASE("test size with multi item-ed list") {
		gilist list;
		list.push_back(1);
		list.push_back(2);

		CHECK_EQ(2, list.size());
	}

	TEST_CASE("test push_front") {
		gint::init();

		gilist list;
		list.push_front(1);

		CHECK_EQ(1, list.size());
		CHECK_EQ(1, list.front());
		CHECK_EQ(1, gint::count());

		list.push_front(2);
		CHECK_EQ(2, list.size());
		CHECK_EQ(2, list.front());
		CHECK_EQ(2, gint::count());

		list.push_front(3);
		CHECK_EQ(3, list.size());
		CHECK_EQ(3, list.front());
		CHECK_EQ(3, gint::count());
	}

	TEST_CASE("test push_back") {
		gint::init();

		gilist list;
		list.push_back(1);

		CHECK_EQ(1, list.size());
		CHECK_EQ(1, list.back());
		CHECK_EQ(1, gint::count());

		list.push_back(2);
		CHECK_EQ(2, list.size());
		CHECK_EQ(2, list.back());
		CHECK_EQ(2, gint::count());

		list.push_back(3);
		CHECK_EQ(3, list.size());
		CHECK_EQ(3, list.back());
		CHECK_EQ(3, gint::count());
	}

	TEST_CASE("test pop_front with empty list") {
		gilist list;

		CHECK_THROWS(list.pop_front());
	}

	TEST_CASE("test pop_front with singly item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);

		auto testItem = list.pop_front();

		CHECK_EQ(1, testItem);
		CHECK_EQ(0, list.size());
		CHECK_EQ(1, gint::count());
	}

	TEST_CASE("test pop_front with multi item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);
		list.push_back(2);

		{
			auto testItem = list.pop_front();

			CHECK_EQ(1, testItem);
		}

		CHECK_EQ(1, list.size());
		CHECK_EQ(1, gint::count());
	}

	TEST_CASE("test pop_back with empty list") {
		gilist list;

		CHECK_THROWS(list.pop_back());
	}

	TEST_CASE("test pop_back with singly item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);

		{
			auto testItem = list.pop_back();

			CHECK_EQ(1, testItem);
		}

		CHECK_EQ(0, list.size());
		CHECK_EQ(0, gint::count());
	}

	TEST_CASE("test pop_back with multi item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);
		list.push_back(2);

		{
			auto testItem = list.pop_back();

			CHECK_EQ(2, testItem);
		}

		CHECK_EQ(1, list.size());
		CHECK_EQ(1, gint::count());
	}

	TEST_CASE("test remove with empty list") {
		gint::count();

		gilist list;

		CHECK_FALSE(list.remove(1));
		CHECK_EQ(0, gint::count());
		CHECK_EQ(0, list.size());
	}

	TEST_CASE("test remove with singly item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);

		CHECK(list.remove(1));
		CHECK_EQ(0, gint::count());
		CHECK_EQ(0, list.size());
	}

	TEST_CASE("test remove with multi item-ed list") {
		gint::init();

		gilist list;
		list.push_back(2);
		list.push_back(1);

		CHECK(list.remove(1));
		CHECK_EQ(2, list.front());
		CHECK_EQ(2, list.back());
		CHECK_EQ(1, gint::count());
		CHECK_EQ(1, list.size());
	}

	TEST_CASE("test remove query with empty list") {
		gint::init();

		gilist list;

		auto testFunction = [&](gint value) -> bool { return value == 1; };

		bool temp = list.remove(testFunction(1));
		CHECK_FALSE(temp);
		CHECK_EQ(0, gint::count());
		CHECK_EQ(0, list.size());
	}

	TEST_CASE("test remove query with singly item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);

		auto testFunction = [&](gint value) -> bool { return value == 1; };

		bool temp = list.remove(testFunction(1));
		CHECK(temp);
		CHECK_EQ(0, gint::count());
		CHECK_EQ(0, list.size());
	}

	TEST_CASE("test remove query with multi item-ed list") {
		gilist list;
		list.push_back(2);
		list.push_back(1);

		auto testFunction = [&](gint value) -> bool { return value == 1; };

		bool temp = list.remove(testFunction(1));
		CHECK(temp);
		CHECK_EQ(1, gint::count());
		CHECK_EQ(1, list.size());
		CHECK_EQ(2, list.front());
		CHECK_EQ(2, list.back());
	}

	TEST_CASE("test remove_all with empty list") {
		gint::init();

		gilist list;

		CHECK_FALSE(list.remove_all(1));
		CHECK_EQ(0, gint::count());
		CHECK_EQ(0, list.size());
	}

	TEST_CASE("test remove_all with singly item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);

		CHECK(list.remove_all(1));
		CHECK_EQ(0, gint::count());
		CHECK_EQ(0, list.size());
	}

	TEST_CASE("test remove_all with multi item-ed list") {
		gint::init();

		gilist list;
		list.push_back(2);
		list.push_back(2);
		list.push_back(1);
		list.push_back(1);

		CHECK(list.remove_all(1));
		CHECK_EQ(2, gint::count());
		CHECK_EQ(2, list.size());
		CHECK_EQ(2, list.front());
		CHECK_EQ(2, list.back());
	}

	TEST_CASE("test remove_all query with empty list") {
		gint::init();

		gilist list;

		auto testFunction = [&](gint value) -> bool { return value == 1; };

		CHECK_FALSE(list.remove_all(testFunction(1)));
		CHECK_EQ(0, gint::count());
		CHECK_EQ(0, list.size());
	}

	TEST_CASE("test remove_all query with singly item-ed list") {
		gint::init();

		gilist list;
		list.push_back(1);

		auto testFunction = [&](gint value) -> bool { return value == 1; };

		CHECK(list.remove_all(testFunction(1)));
		CHECK_EQ(0, gint::count());
		CHECK_EQ(0, list.size());
	}

	TEST_CASE("test remove_all query with multi item-ed list") {
		gint::init();

		gilist list;
		list.push_back(2);
		list.push_back(2);
		list.push_back(1);
		list.push_back(1);

		auto testFunction = [&](gint value) -> bool { return value == 1; };

		CHECK(list.remove_all(testFunction(1)));
		CHECK_EQ(2, gint::count());
		CHECK_EQ(2, list.size());
		CHECK_EQ(2, list.front());
		CHECK_EQ(2, list.back());
	}
}
