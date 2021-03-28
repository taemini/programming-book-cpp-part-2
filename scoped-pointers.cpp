#define CATCH_CONFIG_MAIN
#include "boost/smart_ptr/scoped_ptr.hpp"
#include "boost/smart_ptr/scoped_array.hpp"
#include "catch.hpp"

struct DeadMenOfDunharrow {
  DeadMenOfDunharrow(const char* m = "") : message{m} { oaths_to_fulfill++; }
  ~DeadMenOfDunharrow() { oaths_to_fulfill--; }
  const char* message;
  static int oaths_to_fulfill;
};

int DeadMenOfDunharrow::oaths_to_fulfill{};
using ScopedOathBreakers = boost::scoped_ptr<DeadMenOfDunharrow>;

// implicit bool conversion based on ownership
TEST_CASE("ScopedPtr evaluates to") {
  SECTION("true when full") {
    ScopedOathBreakers aragorn{new DeadMenOfDunharrow{}};
    REQUIRE(aragorn);
  }
  SECTION("false when empty") {
    ScopedOathBreakers aragorn;
    REQUIRE_FALSE(aragorn);
  }
}

// smart pointer as a RAII wrapper
TEST_CASE("ScopedPtr is an RAII wrapper.") {
  REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 0);
  ScopedOathBreakers aragorn{new DeadMenOfDunharrow{}};
  REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
  {
    ScopedOathBreakers legolas{new DeadMenOfDunharrow{}};
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 2);
  }
  REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
}

// pointer semantics
TEST_CASE("ScopedPtr supports pointer semantics, like") {
  auto message = "The way is shut";
  ScopedOathBreakers aragorn{ new DeadMenOfDunharrow{message} };
  SECTION("operator*") {
    REQUIRE((*aragorn).message == message);
  }
  SECTION("operator->") {
    REQUIRE(aragorn->message == message);
  }
  SECTION("get(), which returns a raw pointer") {
    REQUIRE(aragorn.get() != nullptr);
  }
}

// comparison with nullptr
TEST_CASE("ScopedPtr supports comparison with nullptr") {
  SECTION("operator==") {
    ScopedOathBreakers legolas{};
    REQUIRE(legolas == nullptr);
  }
  SECTION("operator!=") {
    ScopedOathBreakers aragorn{new DeadMenOfDunharrow};
    REQUIRE(aragorn != nullptr);
  }
}

// swapping
TEST_CASE("ScopedPtr supports swap") {
  auto message1 = "The way is shut.";
  auto message2 = "Until the time comes.";
  ScopedOathBreakers aragorn {
    new DeadMenOfDunharrow{message1}
  };
  ScopedOathBreakers legolas {
    new DeadMenOfDunharrow{message2}
  };
  aragorn.swap(legolas);
  REQUIRE(legolas->message == message1);
  REQUIRE(aragorn->message == message2);
}

// resetting & replacing
TEST_CASE("ScopedPtr reset") {
  ScopedOathBreakers aragorn{new DeadMenOfDunharrow{}};
  SECTION("destructs owned object.") {
    aragorn.reset();
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 0);
  }
  SECTION("can replace an owned object.") {
    auto message = "It was made by those who are dead.";
    auto new_dead_men = new DeadMenOfDunharrow{message};
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 2);
    aragorn.reset(new_dead_men);
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
    REQUIRE(aragorn -> message == new_dead_men -> message);
    REQUIRE(aragorn.get() == new_dead_men);
  }
}

// non-transferability, exclusive-ownership (move X, copy X)
void by_ref(const ScopedOathBreakers&) { }
void by_val(ScopedOathBreakers) { }
TEST_CASE("ScopedPtr can") {
  ScopedOathBreakers aragorn{new DeadMenOfDunharrow};
  SECTION("be passed by reference") {
    by_ref(aragorn);
  }
  SECTION("not be copied") {
    // DOES NOT COMPILE:
    // by_val(aragorn);
    // auto son_of_arathorn = aragorn;
  }
  SECTION("not be moved") {
    // DOES NOT COMPILE:
    // by_val(std::move(aragorn));
    // auto son_of_arathorn = std::move(aragorn);
  }
}

// boost::scoped_array
TEST_CASE("ScopedArray supports operator[]") {
  boost::scoped_array<int> squares{
    new int[5] {0, 4, 9, 16, 25}
  };
  squares[0] = 1;
  REQUIRE(squares[0] == 1);
  REQUIRE(squares[1] == 4);
  REQUIRE(squares[2] == 9);
}