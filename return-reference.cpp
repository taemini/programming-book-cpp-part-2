#include <cstdio>

int& get_int_value(int& num) {
  num++;
  return num;
}

int main() {
  int num = 3;
  int num1 = get_int_value(num);
  num1++;
  printf("%d %d\n", num, num1);
}