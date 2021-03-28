#define CATCH_CONFIG_MAIN
#include <boost/numeric/conversion/cast.hpp>
#include <boost/numeric/conversion/converter.hpp>

#include "catch.hpp"

using double_to_int =
    boost::numeric::converter<int, double>;  // T: target, S: source

TEST_CASE("boost::numeric::converter offers the static method convert") {
  REQUIRE(double_to_int::convert(3.14159) == 3);
}

TEST_CASE("boost::numeric::converter implements operator()") {
  double_to_int dti;
  REQUIRE(dti(3.14159) == 3);
  REQUIRE(double_to_int{}(3.14159) == 3);
}

TEST_CASE("boost::numeric::converter checks for overflow") {
  auto yuge = std::numeric_limits<double>::max();
  double_to_int dti;
  REQUIRE_THROWS_AS(dti(yuge), boost::numeric::positive_overflow);
}

TEST_CASE("boost::numeric_cast") {
  auto yuge = std::numeric_limits<double>::max();
  REQUIRE_THROWS_AS(boost::numeric_cast<int>(yuge),
                    boost::numeric::positive_overflow);
}