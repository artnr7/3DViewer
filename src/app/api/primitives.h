#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include <cstdint>
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
};

}  // namespace s21
#endif
