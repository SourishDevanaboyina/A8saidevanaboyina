// test_vector_iterator.cpp
//#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "array/vector.hpp"
#include "array/matrix.hpp"


TEST_CASE("Matrix addition: same dimensions", "[tag]") {
    REQUIRE(true);
}

TEST_CASE("Matrix constructor initializes zeros", "[tag]") {
    dsac::array::Matrix m(2, 3);

    REQUIRE(m(0, 0) == 0);
    REQUIRE(m(0, 1) == 0);
    REQUIRE(m(0, 2) == 0);
    REQUIRE(m(1, 0) == 0);
    REQUIRE(m(1, 1) == 0);
    REQUIRE(m(1, 2) == 0);
}

TEST_CASE("Matrix constructor throws on negative dimensions", "[tag]") {
    REQUIRE_THROWS_AS(dsac::array::Matrix(-1, 2), std::out_of_range);
    REQUIRE_THROWS_AS(dsac::array::Matrix(2, -1), std::out_of_range);
}

TEST_CASE("Matrix operator() accesses elements", "[tag]") {
    dsac::array::Matrix m(2, 2);

    m(0, 0) = 4;
    m(0, 1) = 5;
    m(1, 0) = 6;
    m(1, 1) = 7;

    REQUIRE(m(0, 0) == 4);
    REQUIRE(m(0, 1) == 5);
    REQUIRE(m(1, 0) == 6);
    REQUIRE(m(1, 1) == 7);
}

TEST_CASE("Matrix addition works", "[tag]") {
    dsac::array::Matrix a(2, 2);
    dsac::array::Matrix b(2, 2);

    a(0, 0) = 1; a(0, 1) = 2;
    a(1, 0) = 3; a(1, 1) = 4;

    b(0, 0) = 10; b(0, 1) = 20;
    b(1, 0) = 30; b(1, 1) = 40;

    dsac::array::Matrix c = a + b;

    REQUIRE(c(0, 0) == 11);
    REQUIRE(c(0, 1) == 22);
    REQUIRE(c(1, 0) == 33);
    REQUIRE(c(1, 1) == 44);
}

TEST_CASE("Matrix addition throws on mismatched dimensions", "[tag]") {
    dsac::array::Matrix a(2, 2);
    dsac::array::Matrix b(2, 3);

    REQUIRE_THROWS_AS(a + b, std::out_of_range);
}