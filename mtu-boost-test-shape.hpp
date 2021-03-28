#ifndef SHAPE_H
#define SHAPE_H

struct Shape {
  virtual double area() = 0;
  double x;
  double y;
};

#endif SHAPE_H