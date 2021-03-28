#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "unordered_set"

TEST_CASE("std::unordered_set") {
  std::unordered_set<unsigned long> sheep(100);
  SECTION("allows bucket count specification on construction") {
    REQUIRE(sheep.bucket_count() >= 100);
    REQUIRE(sheep.bucket_count() <= sheep.max_bucket_count());
    REQUIRE(sheep.max_load_factor() == Approx(1.0));
  }
  SECTION("allows us to reserve space for elements") {
    sheep.reserve(100'000);
    sheep.insert(0);
    REQUIRE(sheep.load_factor() <= 0.00001);
    while (sheep.size() < 100'000) sheep.insert(sheep.size());
    REQUIRE(sheep.load_factor() <= 1.0);
  }
}