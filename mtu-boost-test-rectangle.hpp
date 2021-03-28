#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "mtu-boost-test-shape.hpp"

struct Rectangle : Shape {
  double area();

  double width;
  double height;
};

#endif