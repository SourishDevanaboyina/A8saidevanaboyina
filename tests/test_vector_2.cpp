#include "catch2/catch.hpp"

#include "array/vector.hpp"
#include "array/matrix.hpp"

TEST_CASE("iterator begin dereference", "[vector][iterator]") {
    dsac::array::Vector<int> v;
    v.push_back(10);
    v.push_back(20);

    auto it = v.begin();
    REQUIRE(*it == 10);
}

TEST_CASE("iterator preincrement walks through vector", "[vector][iterator]") {
    dsac::array::Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    auto it = v.begin();
    ++it;
    REQUIRE(*it == 2);
    ++it;
    REQUIRE(*it == 3);
}

TEST_CASE("iterator postincrement returns old position", "[vector][iterator]") {
    dsac::array::Vector<int> v;
    v.push_back(5);
    v.push_back(6);

    auto it = v.begin();
    auto old = it++;

    REQUIRE(*old == 5);
    REQUIRE(*it == 6);
}

TEST_CASE("insert and erase with iterator return correct iterator", "[vector][iterator]") {
    dsac::array::Vector<int> v;
    v.push_back(1);
    v.push_back(3);

    auto it = v.begin();
    ++it;
    auto inserted = v.insert(it, 2);

    REQUIRE(*inserted == 2);
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);

    auto erased = v.erase(inserted);
    REQUIRE(*erased == 3);
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 3);
}

TEST_CASE("const_iterator begin dereference", "[vector][const_iterator]") {
    dsac::array::Vector<int> v;
    v.push_back(7);
    v.push_back(8);

    const dsac::array::Vector<int>& cv = v;
    auto it = cv.begin();

    REQUIRE(*it == 7);
}

TEST_CASE("const_iterator preincrement works", "[vector][const_iterator]") {
    dsac::array::Vector<int> v;
    v.push_back(11);
    v.push_back(22);
    v.push_back(33);

    const dsac::array::Vector<int>& cv = v;
    auto it = cv.begin();
    ++it;
    REQUIRE(*it == 22);
    ++it;
    REQUIRE(*it == 33);
}

TEST_CASE("const_iterator postincrement returns old value", "[vector][const_iterator]") {
    dsac::array::Vector<int> v;
    v.push_back(100);
    v.push_back(200);

    const dsac::array::Vector<int>& cv = v;
    auto it = cv.begin();
    auto old = it++;

    REQUIRE(*old == 100);
    REQUIRE(*it == 200);
}

TEST_CASE("const_iterator begin and end compare properly", "[vector][const_iterator]") {
    dsac::array::Vector<int> v;
    v.push_back(1);
    v.push_back(2);

    const dsac::array::Vector<int>& cv = v;

    auto it = cv.begin();
    auto last = cv.end();

    REQUIRE(it != last);
    ++it;
    REQUIRE(it != last);
    ++it;
    REQUIRE(it == last);
}