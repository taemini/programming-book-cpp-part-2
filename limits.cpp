#define CATCH_CONFIG_MAIN
#include <limits>

#include "catch.hpp"

TEST_CASE("std::numeric_limits::min provides the smallest finite value.") {
  auto my_cup = std::numeric_limits<int>::min();
  auto underfloweth = my_cup - 1;
  REQUIRE(my_cup < underfloweth);
}
