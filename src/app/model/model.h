#ifndef MODEL_H_
#define MODEL_H_

#include "../model_interface/interface.h"
#include "object_class.h"
#include <memory>

namespace s21 {

class Model : public IModel {

public:
  Model() = default;
  ~Model() = default;

private:
  // DATA -------------------------
  std::unique_ptr<Object> obj_;
  std::string obj_filename_;
  // affine_trans at_;

  // METHODS ------------------------
  // create/build
  void BuildObject(const std::string &filename) override;

  // get glvertices
  std::vector<float> &GetGLVertices() override;

  // update data
  void TranslateObject() override;
  void ScaleObject() override;
};

} // namespace s21

#endif
