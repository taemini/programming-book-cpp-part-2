#define CATCH_CONFIG_MAIN
#include <chrono>
#include <thread>

#include "catch.hpp"

// durations
TEST_CASE("std::chrono supports several clocks") {
  auto sys_now = std::chrono::system_clock::now();
  auto hires_now = std::chrono::high_resolution_clock::now();
  auto steady_now = std::chrono::steady_clock::now();

  REQUIRE(sys_now.time_since_epoch().count() > 0);
  REQUIRE(hires_now.time_since_epoch().count() > 0);
  REQUIRE(steady_now.time_since_epoch().count() > 0);
}
// construct durations
TEST_CASE("std::chrono supports several units of measurement") {
  using namespace std::literals::chrono_literals;
  auto one_s = std::chrono::seconds(1);
  auto thousand_ms = 1000ms;
  REQUIRE(one_s == thousand_ms);
}

// convert to another unit (duration_case)
TEST_CASE("std::chrono supports duration_case") {
  using namespace std::chrono;
  auto billion_ns_as_s = duration_cast<seconds>(1'000'000'000ns);
  REQUIRE(billion_ns_as_s.count() == 1);
}

// waiting
TEST_CASE("std::chrono used to sleep") {
  using namespace std::literals::chrono_literals;
  auto start = std::chrono::system_clock::now();
  std::this_thread::sleep_for(100ms);
  auto end = std::chrono::system_clock::now();
  REQUIRE(end - start >= 100ms);
}