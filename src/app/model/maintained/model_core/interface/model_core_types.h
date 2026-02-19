#ifndef MODEL_CORE_TYPES_H_
#define MODEL_CORE_TYPES_H_

#include <string>
#include <variant>

namespace s21 {

enum class ColorEntity {
  kVertex,
  kEdge,
  kBackground
};

struct ColorRGB {
  float r; /* red */
  float g; /* green */
  float b; /* blue */
};

struct ObjectInfo {
  int vertices; /* vertices count */
  int edges;    /* edges    count */
};

template <typename T>
using TemplateData = std::variant<T, ObjectInfo>;

using LoadData = TemplateData<std::string>;

} // namespace s21

#endif  // MODEL_CORE_TYPES_H_
