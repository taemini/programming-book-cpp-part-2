#include <chrono>
#include <cstdio>
#include <forward_list>
#include <vector>

struct Stopwatch {
  Stopwatch(std::chrono::nanoseconds& result)
      : result{result}, start{std::chrono::system_clock::now()} {}
  ~Stopwatch() { result = std::chrono::system_clock::now() - start; }

 private:
  std::chrono::nanoseconds& result;
  const std::chrono::time_point<std::chrono::system_clock> start;
};

int main() {
  size_t samples{100'000'000};
  // std::forward_list<size_t> v{}; // 654 ms
  std::vector<size_t> v{};  // 1087 ms

  for (size_t i{}; i < samples; i++) {
    v.push_back(i);
  }
  // for (size_t i{}; i < samples; i++) {
  //   v.push_front(i);
  // }
  printf("pushed all elements\n");

  std::chrono::nanoseconds elapsed;
  {
    Stopwatch stopwatch{elapsed};
    volatile size_t curr{};
    auto itr = v.begin();
    for (size_t i{}; i < samples; i++) {
      curr = *itr;
      std::advance(itr, 1);
    }
  }

  printf("elapsed : %g ms\n", elapsed.count() / 1'000'000.);
  // printf("Elapsed: %g s.\n", elapsed.count() / 1'000'000'000.);
}