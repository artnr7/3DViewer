#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "iostream"
// #include "spdlog/spdlog.h"
#include "object_class/object_class.hpp"

namespace s21 {
class Model {
protected:
private:
  Model() = default;
  static std::unique_ptr<Model> instance;
  std::unique_ptr<Object> obj_;
  std::string obj_filename_;

public:
  // explicit Model(std::string &obj_filename);

  static Model *GetModel() {
    if (instance == nullptr) {
      instance = std::unique_ptr<Model>(new Model());
    }
    return instance.get();
  }

  std::vector<float> &GetGLVertices();
  void CreateNewObject(const std::string &obj_filename);
  // void SetObjFilename(std::string &obj_filename) noexcept;
};

} // namespace s21

#endif