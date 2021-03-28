#define CATCH_CONFIG_MAIN
#include <vector>

#include "catch.hpp"

TEST_CASE("std::vector begin and end provide random-access iterators") {
  const std::vector<int> easy_as{1, 2, 3};
  auto itr = easy_as.begin();
  REQUIRE(itr[0] == 1);
  itr++;
  REQUIRE(*(easy_as.cbegin() + 2) == 3);
  REQUIRE(easy_as.cend() - itr == 2);
}