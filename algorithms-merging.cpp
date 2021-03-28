#define CATCH_CONFIG_MAIN
#include <algorithm>
#include <string>
#include <vector>

#include "catch.hpp"

using namespace std;

TEST_CASE("merge") {
  vector<int> numbers1{1, 4, 5}, numbers2{2, 3, 3, 6}, result;
  merge(numbers1.begin(), numbers1.end(), numbers2.begin(), numbers2.end(),
        back_inserter(result));
  REQUIRE(result == vector<int>{1, 2, 3, 3, 4, 5, 6});
}