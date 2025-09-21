#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "iostream"
#include "object_class/object_class.hpp"

namespace s21 {
class Model {
protected:
  Model() = default;
  static Model *instance;

private:
  Object *obj_;
  std::string obj_filename_;

public:
  explicit Model(std::string &obj_filename);
  static Model *GetModel() {
    if (instance == nullptr) {
      instance = new Model();
    }
    return instance;
  }
  std::vector<float> &GetGLVertices();
  // void SetObjFilename(std::string &obj_filename) noexcept;
};
} // namespace s21

#endif