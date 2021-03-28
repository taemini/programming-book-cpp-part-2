#define CATCH_CONFIG_MAIN

#include <iterator>
#include <vector>

#include "catch.hpp"

TEST_CASE("iter_swap swaps pointed-to elements") {
  std::vector<long> easy_as{3, 2, 1};
  std::iter_swap(easy_as.begin(), std::next(easy_as.begin(), 2));
  REQUIRE(easy_as[0] == 1);
  REQUIRE(easy_as[1] == 2);
  REQUIRE(easy_as[2] == 3);
}