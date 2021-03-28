#define CATCH_CONFIG_MAIN
#include <memory>
#include "catch.hpp"

struct DeadMenOfDunharrow {
  DeadMenOfDunharrow(const char* m = "") : message{m} { oaths_to_fulfill++; }
  ~DeadMenOfDunharrow() { oaths_to_fulfill--; }
  const char* message;
  static int oaths_to_fulfill;
};

int DeadMenOfDunharrow::oaths_to_fulfill{};
using SharedOathBreakers = std::shared_ptr<DeadMenOfDunharrow>;

// implicit bool conversion based on ownership
TEST_CASE("SharedPtr evaluates to") {
  SECTION("true when full") {
    SharedOathBreakers aragorn{new DeadMenOfDunharrow{}};
    REQUIRE(aragorn);
  }
  SECTION("false when empty") {
    SharedOathBreakers aragorn;
    REQUIRE_FALSE(aragorn);
  }
}

// smart pointer as a RAII wrapper
TEST_CASE("SharedPtr is an RAII wrapper.") {
  REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 0);
  SharedOathBreakers aragorn{new DeadMenOfDunharrow{}};
  REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
  {
    SharedOathBreakers legolas{new DeadMenOfDunharrow{}};
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 2);
  }
  REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
}

// pointer semantics
TEST_CASE("SharedPtr supports pointer semantics, like") {
  auto message = "The way is shut";
  SharedOathBreakers aragorn{ new DeadMenOfDunharrow{message} };
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
TEST_CASE("SharedPtr supports comparison with nullptr") {
  SECTION("operator==") {
    SharedOathBreakers legolas{};
    REQUIRE(legolas == nullptr);
  }
  SECTION("operator!=") {
    SharedOathBreakers aragorn{new DeadMenOfDunharrow};
    REQUIRE(aragorn != nullptr);
  }
}

// swapping
TEST_CASE("SharedPtr supports swap") {
  auto message1 = "The way is shut.";
  auto message2 = "Until the time comes.";
  SharedOathBreakers aragorn {
    new DeadMenOfDunharrow{message1}
  };
  SharedOathBreakers legolas {
    new DeadMenOfDunharrow{message2}
  };
  aragorn.swap(legolas);
  REQUIRE(legolas->message == message1);
  REQUIRE(aragorn->message == message2);
}

// resetting & replacing
TEST_CASE("SharedPtr reset") {
  SharedOathBreakers aragorn{new DeadMenOfDunharrow{}};
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

// transferable & non-exclusive ownership
TEST_CASE("SharedPtr can be used in copy") {
  auto aragorn = std::make_shared<DeadMenOfDunharrow>();
  SECTION("construction") {
    auto son_of_arathorn{aragorn};
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
  }
  SECTION("assignment") {
    SharedOathBreakers son_of_arathorn;
    son_of_arathorn = aragorn;
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
  }
  SECTION("assignment, and original gets discarded") {
    auto son_of_arathorn = std::make_shared<DeadMenOfDunharrow>();
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 2);
    son_of_arathorn = aragorn;
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
  }
}