#ifndef MODEL_H_
#define MODEL_H_

#include "../api/model_interface.h"
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
  std::vector<uint> &GetEBO() override;

  // update data
  void TranslateToX(float x) override;
  void TranslateToY(float x) override;
  void TranslateToZ(float x) override;

  void TranslateOnX(float x) override;
  void TranslateOnY(float x) override;
  void TranslateOnZ(float x) override;

  void ScaleObject() override;
};

} // namespace s21

#endif
