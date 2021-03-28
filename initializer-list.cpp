#define CATCH_CONFIG_MAIN
#include <cmath>
#include <initializer_list>
#include <stdexcept>
#include <vector>

#include "catch.hpp"

size_t square_root(size_t x) {
  const auto result = sqrt(x);
  if (result * result != x) throw std::logic_error{"Not a perfect square"};
  return result;
}

template <typename T>
struct SquareMatrix {
  SquareMatrix(std::initializer_list<T> val)
      : dim{square_root(val.size())}, data(dim, std::vector<T>{}) {
    auto itr = val.begin();
    for (size_t row{}; row < dim; row++) {
      data[row].assign(itr, itr + dim);
      itr += dim;
    }
  }
  T& at(size_t row, size_t col) {
    if (row >= dim || col >= dim) {
      throw std::out_of_range{"Index invalid."};
    }
    return data[row][col];
  }
  const size_t dim;

 private:
  std::vector<std::vector<T>> data;
};

TEST_CASE("SquareMatrix and std::initializer_list") {
  SquareMatrix<int> mat{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  REQUIRE(mat.dim == 4);
  mat.at(1, 1) = 6;
  REQUIRE(mat.at(1, 1) == 6);
  REQUIRE(mat.at(0, 2) == 3);
}