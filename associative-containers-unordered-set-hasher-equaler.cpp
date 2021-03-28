#define CATCH_CONFIG_MAIN
#include <functional>

#include "catch.hpp"

// hash function
TEST_CASE("std::hash<long> returns") {
  std::hash<long> hasher;
  auto hash_code_42 = hasher(42);
  SECTION("equal hash codes for equal keys") {
    REQUIRE(hash_code_42 == hasher(42));
  }
  SECTION("unequal hash codes for unequal keys") {
    REQUIRE(hash_code_42 != hasher(43));
  }
}

// equality check (identical to ==)
TEST_CASE("std::equal_to<long> returns") {
  std::equal_to<long> long_equal_to;
  SECTION("true when arguments equal") { REQUIRE(long_equal_to(42, 42)); }
  SECTION("false when arguments unequal") { REQUIRE(!long_equal_to(42, 43)); }
}
