#ifndef MODEL_H_
#define MODEL_H_

#include <cstdint>
#include <memory>

#include "../api/model_interface.h"
#include "object_class/object_class.h"
#include "settings_controller/base.h"

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
  void BuildObject(const std::string& filename) override;

  // get glvertices
  std::vector<float>& GetGLVertices() override;
  std::vector<uint>& GetEBO() override;

  // SETTERS -------------------------------
  // Affine
  void SetTransRateX(float) override;
  void SetTransRateY(float) override;
  void SetTransRateZ(float) override;

  void AddTransRateX(float) override;
  void AddTransRateY(float) override;
  void AddTransRateZ(float) override;

  void SetRotAngleX(float) override;
  void SetRotAngleY(float) override;
  void SetRotAngleZ(float) override;

  void AddRotAngleX(float) override;
  void AddRotAngleY(float) override;
  void AddRotAngleZ(float) override;

  void SetScaleRate(float) override;

  // Vert
  void SetVertSz(float) override;
  void SetVertStyle(uint16_t) override;
  void SetVertClr(Color) override;

  // Edge
  void SetEdgeSz(float) override;
  void SetEdgeStyle(uint16_t) override;
  void SetEdgeClr(Color) override;

  // Misc
  void SetBckgClr(Color) override;

  // GETTERS -------------------------------
  const Angles& GetRotAngles() override;
  const Rates& GetTransRates() override;
  const float& GetScaleRate() override;

  const float& GetVertSz() override;
  const uint16_t& GetVertStyle() override;
  const Color& GetVertClr() override;

  const float& GetEdgeSz() override;
  const uint16_t& GetEdgeStyle() override;
  const Color& GetEdgeClr() override;

  const Color& GetBckgClr() override;

  const uint16_t& GetProjType() override;
  const uint16_t& GetRenderType() override;

  const Str& GetFilename() override;
};

}  // namespace s21

#endif
