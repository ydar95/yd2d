#include <iostream>
#include <cstdio>
#include <yd2d/math/vector2d.hpp>

int main() {
  std::cout << u8"Hello, World!" << std::endl;
  yd2d::VecF2d x(1,2);
  yd2d::VecF2d y(1,2);
  auto z = x+y;
  printf("%f,%f\n",z.x(),z.y());
  return 0;
}
