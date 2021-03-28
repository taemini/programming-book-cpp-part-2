#define CATCH_CONFIG_MAIN
#include <algorithm>
#include <string>
#include <vector>

#include "catch.hpp"

using namespace std;

TEST_CASE("stable_partition") {
  auto is_odd = [](auto x) { return x % 2 == 1; };
  vector<int> numbers{1, 2, 3, 4, 5};
  stable_partition(numbers.begin(), numbers.end(), is_odd);
  REQUIRE(numbers == vector<int>{1, 3, 5, 2, 4});
}

TEST_CASE("partition_copy") {
  auto is_odd = [](auto x) { return x % 2 == 1; };
  vector<int> numbers{1, 2, 3, 4, 5}, odds, evens;
  partition_copy(numbers.begin(), numbers.end(), back_inserter(odds),
                 back_inserter(evens), is_odd);
  REQUIRE(all_of(odds.begin(), odds.end(), is_odd));
  REQUIRE_FALSE(all_of(evens.begin(), evens.end(), is_odd));
}

TEST_CASE("partition") {
  auto is_odd = [](auto x) { return x % 2 == 1; };
  vector<int> numbers{1, 2, 3, 4, 5};
  const auto partition_point =
      partition(numbers.begin(), numbers.end(), is_odd);
  REQUIRE(is_partitioned(numbers.begin(), numbers.end(), is_odd));
  REQUIRE(partition_point == numbers.begin() + 3);
}

TEST_CASE("is_partitioned") {
  auto is_odd = [](auto x) { return x % 2 == 1; };
  vector<int> numbers1{9, 5, 9, 6, 4, 2};
  REQUIRE(is_partitioned(numbers1.begin(), numbers1.end(), is_odd));

  vector<int> numbers2{9, 4, 9, 6, 4, 2};
  REQUIRE_FALSE(is_partitioned(numbers2.begin(), numbers2.end(), is_odd));
}