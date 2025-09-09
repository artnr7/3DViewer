#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "iostream"
#include "object_class/object_class.hpp"

namespace s21 {
class Model {
protected:
  Model();
  static Model *instance;

private:
  Object *obj_;

public:
  static Model *GetModel() {
    if (instance == nullptr) {
      instance = new Model();
    }
    return instance;
  }
  std::vector<float> &GetGLVertices() {
    if (!obj_) {
      throw std::runtime_error("obj is not initialized");
    }
    obj_->PrintArray();
    return obj_->GetGLVertices();
  }
};
} // namespace s21

#endif