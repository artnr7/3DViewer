#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "object_class/object_class.hpp"

namespace s21 {
class Model {
 protected:
  Model() = default;

 private:
  // Variables ----------→
  static std::unique_ptr<Model> instance;
  std::unique_ptr<Object> obj_;
  std::string obj_filename_;

 public:
  // Constructors ----------→

  static Model *GetModel() {
    if (instance == nullptr) {
      instance = std::unique_ptr<Model>(new Model());
    }
    return instance.get();
  }

  std::vector<float> &GetGLVertices();
  void CreateNewObject(const std::string &obj_filename);

  void ScaleObject();
};

}  // namespace s21

#endif