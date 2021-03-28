#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <new>
#include <memory>

struct DeadMenOfDunharrow {
  DeadMenOfDunharrow(const char* m = "") : message{m} { oaths_to_fulfill++; }
  ~DeadMenOfDunharrow() { oaths_to_fulfill--; }
  const char* message;
  static int oaths_to_fulfill;
};
int DeadMenOfDunharrow::oaths_to_fulfill{};

// for testing
static size_t n_allocated, n_deallocated;

template <typename T>
struct MyAllocator {
  using value_type = T;
  MyAllocator() noexcept { }
  template <typename U>
  MyAllocator(const MyAllocator<U>&) noexcept { }
  T* allocate(size_t n) {
    auto p = operator new(sizeof(T) * n);
    ++n_allocated;
    return static_cast<T*>(p);
  }
  void deallocate(T* p, size_t n) {
    operator delete(p);
    ++n_deallocated;
  }
};

template <typename T1, typename T2>
bool operator==(const MyAllocator<T1>&, const MyAllocator<T2>&) {
  return true;
}
template <typename T1, typename T2>
bool operator!=(const MyAllocator<T1>&, const MyAllocator<T2>&) {
  return false;
}

TEST_CASE("Allocator") {
  auto message = "The way is shut.";
  MyAllocator<DeadMenOfDunharrow> alloc;
  {
    auto aragorn = std::allocate_shared<DeadMenOfDunharrow>(alloc, message);
    REQUIRE(aragorn->message == message);
    REQUIRE(n_allocated == 1);
    REQUIRE(n_deallocated == 0);
  }
  REQUIRE(n_allocated == 1);
  REQUIRE(n_deallocated == 1);
}