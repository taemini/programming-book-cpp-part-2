#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <optional>

struct TheMatrix {
  TheMatrix(int x): iteration { x } {}
  const int iteration;
};

enum class Pill { Red, Blue };

std::optional<TheMatrix> take(Pill pill) {
  if(pill == Pill::Blue) return TheMatrix{6};
  return std::nullopt; // std::nullopt = empty std::optional
}

TEST_CASE("std::optional contains types") {
  if (auto matrix_opt = take(Pill::Blue)) {
    REQUIRE(matrix_opt -> iteration == 6); // use of operator->
    auto& matrix = matrix_opt.value(); // use of .value()
    REQUIRE(matrix.iteration == 6);
  } else {
    FAIL("The optional evaluated to false.");
  }
}

TEST_CASE("std::optional can be empty") {
  auto matrix_opt = take(Pill::Red);
  if (matrix_opt) FAIL("The Matrix is not empty.");
  REQUIRE_FALSE(matrix_opt.has_value());
}