#define CATCH_CONFIG_MAIN
#include <sstream>
#include <string>

#include "catch.hpp"

TEST_CASE("istringstream supports construction from a string") {
  // whitespace is the appropriate delimiter for string data
  std::string numbers("1 2.23606 2");
  std::istringstream ss{numbers};
  int a;
  float b, c, d;
  ss >> a;
  ss >> b;
  ss >> c;
  REQUIRE(a == 1);
  REQUIRE(b == Approx(2.23606));
  REQUIRE(c == Approx(2));
  REQUIRE_FALSE(ss >> d);
}