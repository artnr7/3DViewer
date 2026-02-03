#ifndef MODEL_CORE_TYPES_H_
#define MODEL_CORE_TYPES_H_

#include <variant>
#include <string>

struct ObjectInfo {
 int vertices; /* vertices count */
 int edges;    /* edges    count */
};

template <typename T>
using TemplateData = std::variant<T, ObjectInfo>;

using LoadData = TemplateData<std::string>;

#endif // MODEL_CORE_TYPES_H_
