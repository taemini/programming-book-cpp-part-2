#define CATCH_CONFIG_MAIN

#include <boost/asio.hpp>
#include <string>

#include "catch.hpp"

TEST_CASE("construct with dynamic_buffer()") {
  std::string proposition{"Charity for an ex-leper?"};
  auto db = boost::asio::dynamic_buffer(proposition);
}

// TEST_CASE("construct with buffer()") {
//   std::string proposition{"Charity for an ex-leper?"};
//   auto mb = boost::asio::buffer(
//       proposition);  // 그냥 std::string을 넣으면 std::mutable_buffer

//   const std::string const_proposition{"Charity for an ex-leper"};
//   auto cb = boost::asio::buffer(
//       const_proposition);  // const std::string을 넣으면 std::const_buffer
// }

// TEST_CASE("streambuf input/output") {
//   boost::asio::streambuf sb;
//   std::ostream os{&sb};
//   os << "Welease Wodger!";

//   std::istream is{&sb};
//   std::string command;
//   is >> command;

//   REQUIRE(command == "Welease");
// }

// TEST_CASE("streambuf constructor") {
//   boost::asio::streambuf sb;
//   REQUIRE(sb.size() == 0);
// }

// TEST_CASE("const_buffer constructor") {
//   boost::asio::const_buffer cb{"Blessed are the cheesemakers.", 7};

//   REQUIRE(cb.size() == 7);
//   REQUIRE(*static_cast<const char*>(cb.data()) == 'B');
// }

// TEST_CASE("mutable_buffer constructor") {
//   std::string proposition{"Charity for an ex-leper?"};
//   boost::asio::mutable_buffer mb{proposition.data(), proposition.size()};
//   REQUIRE(mb.data() == proposition.data());
//   REQUIRE(mb.size() == proposition.size());
// }
