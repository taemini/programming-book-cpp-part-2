#define CATCH_CONFIG_MAIN
#include <set>

#include "catch.hpp"

TEST_CASE("std::multiset handles non-unique elements") {
  std::multiset<int> fib{1, 1, 2, 3, 5};
  SECTION("as reflected by size") { REQUIRE(fib.size() == 5); }
  SECTION("and count returns values greater than 1") {
    REQUIRE(fib.count(1) == 2);
  }
  SECTION("and equal_range returns non-trivial ranges") {
    auto [begin, end] = fib.equal_range(1);  // structured binding syntax
    REQUIRE(*begin == 1);
    ++begin;
    REQUIRE(*begin == 1);
    ++begin;
    REQUIRE(begin == end);
  }
}