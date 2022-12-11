#include "../src/Edge.h"
#include "../src/Node.h"
#include "../src/dijkstra.h"

#define CATCH_CONFIG_MAIN


//!DEMO START

#include <vector>
#include <iostream>
#include <exception>

long sumVector(std::vector<int> arr) {
    long acc = 0;
    for(int i = 0; i < arr.size(); i++) {
        acc += arr.at(i);
    }
    return acc;
}

TEST_CASE("Catch2 & Tests are wroking", "[Catch2]"){
    std::vector<int> vec = {1, 2, 3};
    REQUIRE(sumVector(vec) == 6);
}

// Quickstart commands
// g++ tests/test.cpp
// ./a.out

//!DEMO END

//TODO Add more test cases
// TEST_CASE("Test case name", "[flag1][flag2]") {
//     std::vector<int> vec = {1, 2, 3};
//     REQUIRE(sumVectorModN(vec, 5) == 1);
//     REQUIRE(sumVectorModN(vec, 4) == 2);
//     REQUIRE_FALSE(sumVectorModN(vec, 1) == 1); //Any number mod 1 is 0, expression is false, so assertion passes
//     REQUIRE_THROWS(sumVectorModN(vec, -1)); //Should throw a logic_error, so test should pass
// }