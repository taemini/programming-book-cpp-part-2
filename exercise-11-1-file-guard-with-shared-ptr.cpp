#include <cstdio>
#include <memory>
#include <errno.h>

using FileGuard = std::shared_ptr<FILE>;

struct Hal {
  Hal(std::shared_ptr<FILE> file): file{file} { }
  ~Hal() {
    fprintf(file.get(), "Stop, Dave.\n");
  }
  void write_status() {
    fprintf(file.get(), "I'm completely operational.\n");
  };
  std::shared_ptr<FILE> file;
};

void say_hello(FileGuard file) {
  fprintf(file.get(), "HELLO DAVE\n");
}

int main() {
  auto file = fopen("exercise-11-1", "w");
  FileGuard file_guard{file, fclose};
  if (!file) return errno;
  Hal hal1{file_guard};
  hal1.write_status();
  Hal hal2{file_guard};
  hal2.write_status();
  Hal hal3{file_guard};
  hal3.write_status();
}d