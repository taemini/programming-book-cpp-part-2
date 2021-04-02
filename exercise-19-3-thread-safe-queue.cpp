#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <stdexcept>

using namespace std;

template <typename T>
struct ThreadSafeQueue {
  void push(T val) {
    lock_guard<mutex> guard{mtx};
    q.push(val);
    cv.notify_all();
  }
  void pop() {
    lock_guard<mutex> guard{mtx};
    return q.pop();
  }
  T wait_and_pop() {
    auto lock = unique_lock{mtx};
    cv.wait(lock, [&] { return q.size() > 0; });
    T front = q.front();
    q.pop();
    return front;
  }
  size_t size() { return q.size(); }

 private:
  queue<T> q{};
  mutex mtx{};
  condition_variable cv{};
};

void goat_rodeo() {
  cout << "goat_rodeo" << endl;
  ThreadSafeQueue<size_t> tsq{};
  const size_t iterations{1'000'000};

  auto pushNumbers = async(launch::async, [&] {
    for (size_t i{}; i < iterations; i++) {
      tsq.push(i);
    }
  });
  auto popNumbers = async(launch::async, [&] {
    for (size_t i{}; i < iterations; i++) {
      tsq.wait_and_pop();
    }
  });
  pushNumbers.get();
  popNumbers.get();
  cout << "------------------------------------------------------" << endl;
  cout << tsq.size() << endl;
}

int main() {
  cout << "thread-safe-queue" << endl;
  goat_rodeo();
  goat_rodeo();
  goat_rodeo();
}