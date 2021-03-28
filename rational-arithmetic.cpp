#define CATCH_CONFIG_MAIN
#include <ratio>

#include "catch.hpp"

TEST_CASE("std::ratio") {
  using ten = std::ratio<10, 1>;
  using two_thirds = std::ratio<2, 12>;
  using result = std::ratio_multiply<ten, two_thirds>;
  REQUIRE(result::num == 5);  // numerator : 분자
  REQUIRE(result::den == 3);  // denominator : 분모
}