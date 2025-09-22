#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <QtOpenGL>
#include <vector>
// #include "spdlog/spdlog.h"

namespace s21 {
class Controller {
private:
  Controller() = default;

public:
  [[nodiscard]] static std::vector<float> &GetVertices();
  // explicit Controller(std::string &obj_filename);
  static void CreateNewObject(const std::string &obj_filename) noexcept;
};
} // namespace s21

#endif