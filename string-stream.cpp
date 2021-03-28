#define CATCH_CONFIG_MAIN
#include <sstream>

#include "catch.hpp"

TEST_CASE("string stream supports all string stream operations") {
  std::stringstream ss;
  ss << "Zed's DEAD";
  std::string who;
  ss >> who;
  int what;
  ss >> std::hex >> what;

  REQUIRE(who == "Zed's");
  REQUIRE(what == 0xdead);
}