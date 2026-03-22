#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include <cstdint>
#include <iostream>
#include <string>

namespace s21 {

using Str = std::string;

struct Angles {
  float x, y, z;
};

struct Rates {
  float x, y, z;
};

struct Color {
  uint8_t x, y, z;
  void Print() const {
    std::cout << static_cast<int>(x) << " " << static_cast<int>(y) << " "
              << static_cast<int>(z) << std::endl;
  }
};

}  // namespace s21
#endif
