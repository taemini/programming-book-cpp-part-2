#define CATCH_CONFIG_MAIN

#include <optional>
#include <stdexcept>

#include "catch.hpp"

// template <typename To, typename From>
// To narrow_cast(From value) {
//   const auto converted = static_cast<To>(value);
//   const auto backwards = static_cast<From>(converted);
//   if (value != backwards) throw std::runtime_error{"Narrowed!"};
//   return converted;
// }

template <typename To, typename From>
std::optional<To> narrow_cast(From value) {
  const auto converted = static_cast<To>(value);
  const auto backwards = static_cast<From>(converted);
  if (value != backwards) return std::nullopt;
  return converted;
}

TEST_CASE("narrow_cast can convert if no overflow") {
  int perfect{496};
  const auto perfect_short = narrow_cast<short>(perfect);
  REQUIRE(perfect_short.value() == 496);
}

TEST_CASE("narrow_cast returns empty optional when narrowing occurs") {
  int cyclic{142857};
  const auto cyclic_short = narrow_cast<short>(cyclic);
  if (cyclic_short) {
    FAIL("cylcic short has a value");
  }
}
