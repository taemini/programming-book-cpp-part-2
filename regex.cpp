#define CATCH_CONFIG_MAIN
#include <regex>

#include "catch.hpp"

TEST_CASE("std::basic_regex constructs from a string literal") {
  std::regex zip_regex{R"((\w{2})?(\d{5})(-\d{4})?)"};
  REQUIRE(zip_regex.mark_count() == 3);
}