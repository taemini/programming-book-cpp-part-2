#define CATCH_CONFIG_MAIN
#include <sstream>
#include <string>

#include "catch.hpp"

TEST_CASE("ostringstream produces strings with str") {
  std::ostringstream ss;
  ss << "By grabthar's hammer, ";
  ss << "by the suns of Worvan. ";

  ss << "You shall be avenged.";
  const auto lazarus = ss.str();

  ss.str("I am Groot.");
  const auto groot = ss.str();

  REQUIRE(lazarus ==
          "By grabthar's hammer, by the suns"
          " of Worvan. You shall be avenged.");
  REQUIRE(groot == "I am Groot.");
}