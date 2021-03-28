#define CATCH_CONFIG_MAIN
#include <algorithm>
#include <string>
#include <vector>

#include "catch.hpp"

using namespace std;

TEST_CASE("clamp") {
  REQUIRE(clamp(9000, 0, 100) == 100);
  REQUIRE(clamp(-123, 0, 100) == 0);
  REQUIRE(clamp(3.14, 0., 100.) == Approx(3.14));
}

TEST_CASE("min and max element") {
  auto length_compare = [](const auto& x1, const auto& x2) {
    return x1.length() < x2.length();
  };
  vector<string> words{"civic", "deed", "kayak", "malayalam"};
  REQUIRE(*min_element(words.begin(), words.end(), length_compare) == "deed");
  REQUIRE(*max_element(words.begin(), words.end(), length_compare) ==
          "malayalam");
  const auto result =
      minmax_element(words.begin(), words.end(), length_compare);
  REQUIRE(*result.first == "deed");
  REQUIRE(*result.second == "malayalam");
}

TEST_CASE("max and min") {
  using namespace std::literals;
  auto length_compare = [](const auto& x1, const auto& x2) {
    return x1.length() < x2.length();
  };
  REQUIRE(min("undiscriminativeness"s, "vermin"s, length_compare) == "vermin");
  REQUIRE(max("maxim"s, "ultramaximal"s, length_compare) == "ultramaximal");
  const auto result = minmax("minimaxes"s, "maximin"s, length_compare);
  REQUIRE(result.first == "maximin");
  REQUIRE(result.second == "minimaxes");
}