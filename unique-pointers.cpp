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
using UniqueOathBreakers = std::unique_ptr<DeadMenOfDunharrow>;

// implicit bool conversion based on ownership
TEST_CASE("UniquePtr evaluates to") {
  SECTION("true when full") {
    UniqueOathBreakers aragorn{new DeadMenOfDunharrow{}};
    REQUIRE(aragorn);
  }
  SECTION("false when empty") {
    UniqueOathBreakers aragorn;
    REQUIRE_FALSE(aragorn);
  }
}

// smart pointer as a RAII wrapper
TEST_CASE("UniquePtr is an RAII wrapper.") {
  REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 0);
  UniqueOathBreakers aragorn{new DeadMenOfDunharrow{}};
  REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
  {
    UniqueOathBreakers legolas{new DeadMenOfDunharrow{}};
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 2);
  }
  REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
}

// pointer semantics
TEST_CASE("UniquePtr supports pointer semantics, like") {
  auto message = "The way is shut";
  UniqueOathBreakers aragorn{ new DeadMenOfDunharrow{message} };
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
TEST_CASE("UniquePtr supports comparison with nullptr") {
  SECTION("operator==") {
    UniqueOathBreakers legolas{};
    REQUIRE(legolas == nullptr);
  }
  SECTION("operator!=") {
    UniqueOathBreakers aragorn{new DeadMenOfDunharrow};
    REQUIRE(aragorn != nullptr);
  }
}

// swapping
TEST_CASE("UniquePtr supports swap") {
  auto message1 = "The way is shut.";
  auto message2 = "Until the time comes.";
  UniqueOathBreakers aragorn {
    new DeadMenOfDunharrow{message1}
  };
  UniqueOathBreakers legolas {
    new DeadMenOfDunharrow{message2}
  };
  aragorn.swap(legolas);
  REQUIRE(legolas->message == message1);
  REQUIRE(aragorn->message == message2);
}

// resetting & replacing
TEST_CASE("UniquePtr reset") {
  UniqueOathBreakers aragorn{new DeadMenOfDunharrow{}};
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

// transferable, exclusive ownership move O, copy X
TEST_CASE("UniquePtr can be used in move") {
  auto aragorn = std::make_unique<DeadMenOfDunharrow>();
  SECTION("construction") {
    auto son_of_arathorn{std::move(aragorn)};
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
  }
  SECTION("assignment") {
    auto son_of_arathorn = std::make_unique<DeadMenOfDunharrow>();
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 2);
    son_of_arathorn = std::move(aragorn);
    REQUIRE(DeadMenOfDunharrow::oaths_to_fulfill == 1);
  }
}

// unique arrays
TEST_CASE("UniquePtr to array supports operator[]") {
  std::unique_ptr<int[]> squares {
    new int[5]{1,4,9,16,25}
  };
  squares[0] = 1;
  REQUIRE(squares[0] == 1);
  REQUIRE(squares[1] == 4);
  REQUIRE(squares[2] == 9);
}