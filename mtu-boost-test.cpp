// multiple translation unit에서 정말 boost test의 header-only mode는 작동하지
// 않을까?

#define BOOST_TEST_MODULE test_module_name
#include <cstdio>

#include "boost/test/included/unit_test.hpp"
#include "mtu-boost-test-rectangle.hpp"

void goodbye() { printf("good bye"); }

BOOST_AUTO_TEST_CASE(TestA) {
  // Unit Test A here
  Rectangle r;
  r.width = 10;
  r.height = 15;
  r.x = 3;
  r.y = 2;
  printf("rectangle area: %g\n", r.area());
}

// int main() {
//   Rectangle r;
//   r.width = 10;
//   r.height = 15;
//   r.x = 3;
//   r.y = 2;
//   printf("rectangle area: %g\n", r.area());
// }