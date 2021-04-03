#define CATCH_CONFIG_MAIN

#include <boost/asio.hpp>

#include "catch.hpp"

TEST_CASE("const_buffer default constructor") {
  boost::asio::const_buffer cb;
  REQUIRE(cb.size() == 0);
}

TEST_CASE("mutable_buffer default constructor") {
  boost::asio::mutable_buffer mb;
  REQUIRE(mb.size() == 0);
}