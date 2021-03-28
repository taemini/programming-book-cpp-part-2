#define CATCH_CONFIG_MAIN
#include <boost/date_time/gregorian/gregorian.hpp>

#include "catch.hpp"

TEST_CASE("Invalid boost::Gregorian::dates throw exceptions") {
  using boost::gregorian::bad_day_of_month;
  using boost::gregorian::date;

  // Due to a limitation in Catch, you cannot use braced initialization for date
  // in the REQUIRE_THROWS_AS macro
  REQUIRE_THROWS_AS(date(1986, 9, 32), bad_day_of_month);
  // other exceptions : bad_year, bad_month, ...
}

// construct a date & use the accessors
TEST_CASE("boost::gregorian::date supports basic calendar functions") {
  boost::gregorian::date d{1986, 9, 15};
  REQUIRE(d.year() == 1986);
  REQUIRE(d.month() == 9);
  REQUIRE(d.day() == 15);
  REQUIRE(d.day_of_year() == 258);
  REQUIRE(d.day_of_week() == boost::date_time::Monday);
}

// calendar math
TEST_CASE("boost::gregorian::date supports calendar arithmetic") {
  boost::gregorian::date d1{1986, 9, 15};
  boost::gregorian::date d2{2019, 8, 1};
  auto duration = d2 - d1;
  REQUIRE(duration.days() == 12008);
}
TEST_CASE("date and date_duration support addition") {
  boost::gregorian::date d1{1986, 9, 15};
  boost::gregorian::date_duration dur{12008};
  auto d2 = d1 + dur;
  REQUIRE(d2 == boost::gregorian::from_string("2019/8/1"));
}

// date periods
TEST_CASE("boost::gregorian::date supports periods") {
  boost::gregorian::date d1{1986, 9, 15};
  boost::gregorian::date d2{2019, 8, 1};
  boost::gregorian::date_period p{d1, d2};
  REQUIRE(p.contains(boost::gregorian::date{1987, 10, 27}));
}
