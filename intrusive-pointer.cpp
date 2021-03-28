#define CATCH_CONFIG_MAIN
#include "boost/smart_ptr/intrusive_ptr.hpp"
#include "catch.hpp"

struct DeadMenOfDunharrow {
  DeadMenOfDunharrow(const char* m = "") : message{m} { oaths_to_fulfill++; }
  ~DeadMenOfDunharrow() { oaths_to_fulfill--; }
  const char* message;
  static int oaths_to_fulfill;
};

int DeadMenOfDunharrow::oaths_to_fulfill{};
using IntrusivePtr = boost::intrusive_ptr<DeadMenOfDunharrow>;
size_t ref_count{};

void intrusive_ptr_add_ref(DeadMenOfDunharrow* d) {
  ref_count++;
}

// dynamic object가 여러개라면 invalid delete will occur
void intrusive_ptr_release(DeadMenOfDunharrow* d) {
  ref_count--;
  if (ref_count == 0) delete d;
}

TEST_CASE("IntrusivePtr uses an embedded reference counter.") {
  REQUIRE(ref_count == 0);
  IntrusivePtr aragorn{ new DeadMenOfDunharrow{} };
  REQUIRE(ref_count == 1);
  {
    IntrusivePtr legolas{aragorn};
    REQUIRE(ref_count == 2);
  }
  REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
}