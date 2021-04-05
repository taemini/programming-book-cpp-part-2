#include <iostream>
#include <string>

struct Tracer {
  Tracer(std::string name_in) : name{name_in} {
    std::cout << name << " constructed.\n";
  }
  ~Tracer() { std::cout << name << " destructed.\n"; }

 private:
  const std::string name;
};

// static storage duration
Tracer static_tracer{"static Tracer"};

void run() {
  std::cout << "Registering a callback\n";
  std::atexit([] { std::cout << "***std::atexit callback executing***\n"; });
  std::cout << "Callback registered\n";
  std::abort();
}

int main() {
  std::cout << "Entering main()\n";
  Tracer local_tracer{"local Tracer"};
  thread_local Tracer thread_local_tracer{"thread_local Tracer"};
  const auto* dynamic_tracer = new Tracer{"dynamic Tracer"};
  run();
  delete dynamic_tracer;
  std::cout << "Exiting main()\n";
}