#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "array/vector.hpp"

TEST_CASE("Default constructor creates empty vector", "[vector]") {
    dsac::array::Vector<int> v;
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.empty());
}

TEST_CASE("push_back grows vector and preserves values", "[vector]") {
    dsac::array::Vector<int> v;
    for (int i = 0; i < 5; ++i) {
        v.push_back(i);
    }

    REQUIRE(v.size() == 5);
    REQUIRE(v[0] == 0);
    REQUIRE(v[1] == 1);
    REQUIRE(v[2] == 2);
    REQUIRE(v[3] == 3);
    REQUIRE(v[4] == 4);
}

TEST_CASE("at throws for invalid index", "[vector]") {
    dsac::array::Vector<int> v;
    v.push_back(10);

    REQUIRE_THROWS_AS(v.at(-1), std::out_of_range);
    REQUIRE_THROWS_AS(v.at(1), std::out_of_range);
}

TEST_CASE("insert and erase by index work", "[vector]") {
    dsac::array::Vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.insert(1, 2);

    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);

    v.erase(1);
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 3);
}