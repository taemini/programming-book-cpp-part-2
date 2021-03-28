#define CATCH_CONFIG_MAIN
#include <filesystem>
#include <string>

#include "catch.hpp"

TEST_CASE("std::filesystem::path supports == and .empty()") {
  std::filesystem::path empty_path;
  std::filesystem::path shadow_path{"/etc/shadow"};
  REQUIRE(empty_path.empty());
  REQUIRE(shadow_path == std::string{"/etc/shadow"});
}
