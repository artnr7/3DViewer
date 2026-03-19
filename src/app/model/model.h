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

private:
  // struct RGB {
  //   uint8_t r, g, b;
  // };
  //
  // struct Settings {
  //   float vertex_sz_ = 1.0f;
  //   uint16_t vertex_style_ = 0;
  //
  //   RGB vertex_clr = {};
  //
  //   float edge_sz_ = 1.0f;
  //   uint16_t edge_style_ = 0;
  //
  //   RGB edge_clr = {};
  //
  //   RGB bckg_clr = {};
  //
  //   uint16_t proj_type = 0;
  //   uint16_t render_type = 0;
  // };
  //
  // Settings settings_;
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

  // Settings Getters
  float GetRotAngleX();
  float GetRotAngleY();
  float GetRotAngleZ();

  float GetTransRateX();
  float GetTransRateY();
  float GetTransRateZ();

  float GetScaleRate();

  float GetVertexSz();
  uint16_t GetVertexStyle();
};

} // namespace s21

#endif
