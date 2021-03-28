#define CATCH_CONFIG_MAIN

#include <forward_list>

#include "catch.hpp"

TEST_CASE("std::forward_list begin and end provide input iterators") {
  const std::forward_list<int> easy_as{1, 2, 3};
  auto itr = easy_as.begin();
  REQUIRE(*itr == 1);
  itr++;
  REQUIRE(*itr == 2);
  itr++;
  REQUIRE(*itr == 3);
  itr++;
  REQUIRE(itr == easy_as.end());
}