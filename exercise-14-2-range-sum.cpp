#include <cstdio>
#include <iterator>
#include <vector>

template <typename InputIterator>
using IteratorRtn = typename std::iterator_traits<InputIterator>::value_type;

template <typename InputIterator>
IteratorRtn<InputIterator> range_sum(InputIterator itr1, InputIterator itr2) {
  IteratorRtn<InputIterator> sum{};
  while (itr1 != itr2) {
    sum += *(itr1++);
  }
  return sum;
}

int main() {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int result = range_sum(v.begin(), v.end());
  printf("%d\n", result);
}