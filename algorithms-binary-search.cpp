#define CATCH_CONFIG_MAIN
#include <string>
#include <vector>

#include "catch.hpp"

using namespace std;

TEST_CASE("binary_search") {
  vector<int> numbers{2, 4, 5, 6, 6, 9};
  REQUIRE(binary_search(numbers.begin(), numbers.end(), 6));
  REQUIRE_FALSE(binary_search(numbers.begin(), numbers.end(), 7));
}

// TEST_CASE("equal_range") {
//   vector<int> numbers{2, 4, 5, 6, 6, 9};
//   const auto [rbeg, rend] = equal_range(numbers.begin(), numbers.end(), 6);
//   REQUIRE(rbeg == numbers.begin() + 3);
//   REQUIRE(rend == numbers.begin() + 5);
// }

// TEST_CASE("upper_bound") {
//   vector<int> numbers{2, 4, 5, 6, 6, 9};
//   const auto result = upper_bound(numbers.begin(), numbers.end(), 5);
//   REQUIRE(result == numbers.begin() + 3);
// }

// TEST_CASE("lower_bound") {
//   vector<int> numbers{2, 4, 5, 6, 6, 9};
//   const auto result = lower_bound(numbers.begin(), numbers.end(), 5);
//   REQUIRE(result == numbers.begin() + 2);
// }