#define CATCH_CONFIG_MAIN

#include <list>

#include "catch.hpp"

TEST_CASE("std::list begin and end provide bidirectional iterators") {
  const std::list<int> easy_as{1, 2, 3};
  auto itr = easy_as.begin();
  REQUIRE(*itr == 1);
  itr++;
  REQUIRE(*itr == 2);
  itr--;
  REQUIRE(*itr == 1);
  REQUIRE(itr == easy_as.cbegin());
}