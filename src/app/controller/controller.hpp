#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <QtOpenGL>
#include <vector>

namespace s21 {
class Controller {
private:
  Controller() = default;

public:
  [[nodiscard]] static std::vector<float> &GetVertices();
  explicit Controller(std::string &obj_filename);
  // static void SetObjFilename(std::string &obj_filename) noexcept;
};
} // namespace s21

#endif