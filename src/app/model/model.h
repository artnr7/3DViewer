#ifndef MODEL_H_
#define MODEL_H_

#include <cstdint>
#include <memory>

#include "../api/model_interface.h"
#include "object/object.h"
#include "settings_controller/settings_controller.h"

namespace s21 {

class Model : public IModel {
 public:
  Model() {
    sett_control_ = std::make_unique<SettingsController>();
    obj_ = std::make_unique<Object>();
  };
  ~Model() = default;

 private:
  // DATA -------------------------
  std::unique_ptr<Object> obj_;
  std::unique_ptr<SettingsController> sett_control_;

  std::string obj_filename_;

  // METHODS ------------------------
  void BuildObject(const std::string& filename) override {
    Lg::Log()->Info("Model::" + std::string(__func__));

    if (obj_ != nullptr) {
      obj_.reset();
    }

    obj_filename_ = filename;

    obj_ = std::make_unique<Object>(obj_filename_);
  }

  // SETTERS -------------------------------
  // Affine
  std::vector<float>& GetGLVertices() override;
  std::vector<uint>& GetEBO() override;

  template <typename F>
  void AddSet(F f, const char* fn);

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
  void AddScaleRate(float) override;

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
