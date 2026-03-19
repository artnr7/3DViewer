#ifndef MODEL_H_
#define MODEL_H_

#include "../api/model_interface.h"
#include "object_class.h"
#include "settings_controller/base.h"
#include <cstdint>
#include <memory>

namespace s21 {

class Model : public IModel {

public:
  Model() { sett_control_ = std::make_unique<SettingsParser>(); };
  ~Model() = default;

private:
  // DATA -------------------------
  std::unique_ptr<Object> obj_;
  std::unique_ptr<SettingsParser> sett_control_;

  std::string obj_filename_;

  // METHODS ------------------------
  void BuildObject(const std::string &filename) override;

  // get glvertices
  std::vector<float> &GetGLVertices() override;
  std::vector<uint> &GetEBO() override;

  // SETTERS -------------------------------
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

  // GETTERS -------------------------------
  const Angles &GetRotAngles() override;
  const Rates &GetTransRates() override;
  const float &GetScaleRate() override;

  const float &GetVertSz() override;
  const uint16_t &GetVertStyle() override;
  const Color &GetVertClr() override;

  const float &GetEdgeSz() override;
  const uint16_t &GetEdgeStyle() override;
  const Color &GetEdgeClr() override;

  const Color &GetBckgClr() override;

  const uint16_t &GetProjType() override;
  const uint16_t &GetRenderType() override;

  const Str &GetFilename() override;
};

} // namespace s21

#endif
