#include <chrono>
#include <cstdio>
#include <map>
#include <random>
#include <unordered_map>
// #include <vector>

long fib_sum(size_t n) {
  std::vector<long> v{};
  v.reserve(3000);
  for (size_t i{}; i < n; i++) {
    if (i == 0 || i == 1) {
      v.push_back(1);
    } else {
      v.push_back(v[i - 2] + v[i - 1]);
    }
  }
  size_t sum{};
  for (auto fib_num : v) {
    sum += fib_num;
  }
  return sum;
}

long random() {
  static std::mt19937_64 mt_engine{102787};
  static std::uniform_int_distribution<long> int_d{1000, 2000};
  return int_d(mt_engine);
}

struct Stopwatch {
  Stopwatch(std::chrono::nanoseconds& result)
      : result{result}, start{std::chrono::system_clock::now()} {}
  ~Stopwatch() { result = std::chrono::system_clock::now() - start; }

 private:
  std::chrono::nanoseconds& result;
  const std::chrono::time_point<std::chrono::system_clock> start;
};

// long cached_fib_sum(size_t n) {
//   static std::map<long, long> cache;
//   if (cache[n]) {
//     return cache[n];
//   } else {
//     cache[n] = fib_sum(n);
//   }
//   return 0;
// }
// long cached_fib_sum(size_t n) {
//   static std::unordered_map<long, long> cache;
//   if (cache[n]) {
//     return cache[n];
//   } else {
//     cache[n] = fib_sum(n);
//   }
//   return 0;
// }
long cached_fib_sum(size_t n) {
  static std::vector<long> cache(3000, 0);
  if (cache[n]) {
    return cache[n];
  } else {
    cache[n] = fib_sum(n);
  }
  return 0;
}

int main() {
  size_t samples{100'000};
  std::chrono::nanoseconds elapsed;
  {
    Stopwatch stopwatch{elapsed};
    volatile double answer;
    while (samples--) {
      // answer = fib_sum(random());
      answer = cached_fib_sum(random());
    }
  }
  printf("Elapsed: %g s.\n", elapsed.count() / 1'000'000'000.);
}