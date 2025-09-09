#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <QtOpenGL>
#include <vector>

namespace s21 {
class Controller {
 private:
  Controller() = default;

 public:
  static std::vector<float> &GetVertices();
};
}  // namespace s21

#endif