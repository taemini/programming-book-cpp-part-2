#include <atomic>
#include <future>
#include <iostream>

using namespace std;

struct SpinLock {
  SpinLock() {}
  SpinLock(const SpinLock& other) = delete;

  void lock() {
    while (locked.test_and_set(memory_order_acquire)) {
      /* spin lock */
    }
  }
  bool try_lock() { return locked.test_and_set(memory_order_acquire) != true; }
  void unlock() { locked.clear(); }

 private:
  atomic_flag locked = ATOMIC_FLAG_INIT;
};

void goat_rodeo() {
  const size_t iterations{1'000'000};
  int tin_cans_available{};
  SpinLock spin_lock;
  auto eat_cans = async(launch::async, [&] {
    for (size_t i{}; i < iterations; i++) {
      lock_guard<SpinLock> guard{spin_lock};
      tin_cans_available--;
    }
  });
  auto deposit_cans = async(launch::async, [&] {
    for (size_t i{}; i < iterations; i++) {
      lock_guard<SpinLock> guard{spin_lock};
      tin_cans_available++;
    }
  });
  eat_cans.get();
  deposit_cans.get();
  cout << "Tin cans: " << tin_cans_available << "\n";
}

int main() {
  goat_rodeo();
  goat_rodeo();
  goat_rodeo();
}