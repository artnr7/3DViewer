#ifndef MODEL_HPP_
#define MODEL_HPP_

// #include "spdlog/spdlog.h"
// #include "object_class/object_class.h"

#include "model_core_types.h"

namespace s21 {

class ModelCore {
  ModelCore() = default;

 protected:
  // explicit Model(const std::string &obj_filename);

 private:
  // Variables ----------→
  // static std::unique_ptr<ModelCore> instance;
  // std::unique_ptr<Object> obj_;
  // std::string obj_filename_;

 public:
  // Constructors ----------→

  // static Model *GetModel() {
  //   if (instance == nullptr) {
  //     instance = std::unique_ptr<Model>(new Model());
  //   }
  //   return instance.get();
  //}

  // std::vector<float> &GetGLVertices();
  // void CreateNewObject(const std::string &obj_filename);
  // void SetObjFilename(std::string &obj_filename) noexcept;

  LoadData OpenModelFile(const std::string& file_path);
};

}  // namespace s21

#endif
