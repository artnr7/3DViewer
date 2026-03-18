#ifndef MODEL_H_
#define MODEL_H_

#include "../api/model_interface.h"
#include "object_class.h"
#include "settings_controller/base.h"
#include <memory>

namespace s21 {

class Model : public IModel {

public:
  Model() { settings_controller_ = std::make_unique<SettingsParser>(); };
  ~Model() = default;

private:
  // DATA -------------------------
  std::unique_ptr<Object> obj_;
  std::unique_ptr<SettingsParser> settings_controller_;

  std::string obj_filename_;

  // METHODS ------------------------
  // create/build
  void BuildObject(const std::string &filename) override;

  // get glvertices
  std::vector<float> &GetGLVertices() override;
  std::vector<uint> &GetEBO() override;

  // update data
  void TranslateToX(float) override;
  void TranslateToY(float) override;
  void TranslateToZ(float) override;

  void TranslateOnX(float) override;
  void TranslateOnY(float) override;
  void TranslateOnZ(float) override;

  void RotateToX(float) override;
  void RotateToY(float) override;
  void RotateToZ(float) override;

  void RotateOnX(float) override;
  void RotateOnY(float) override;
  void RotateOnZ(float) override;

  void ScaleObject(float) override;
};

} // namespace s21

#endif
