#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <../api/model_interface.h>
#include <qpixelformat.h>

#include <memory>
#include <vector>

#include "../api/controller_interface.h"
#include "../utils/logger.h"

namespace s21 {

class Controller : public IController {
 public:
  explicit Controller(IModel* model) : model_(model) {}

  Controller() = delete;
  ~Controller() = default;

 private:
  IModel* model_;

  // METHODS ------------------------
  void BuildObject(const std::string& filename) override {
    Lg::Log()->Info("Controller::" + std::string(__func__));
    model_->BuildObject(filename);
  }

  // SETTERS -------------------------------
  void SetRotAngleX(float) override;
  void SetRotAngleY(float) override;
  void SetRotAngleZ(float) override;

  void AddRotAngleX(float) override;
  void AddRotAngleY(float) override;
  void AddRotAngleZ(float) override;

  void SetTransRateX(float) override;
  void SetTransRateY(float) override;
  void SetTransRateZ(float) override;

  void AddTransRateX(float) override;
  void AddTransRateY(float) override;
  void AddTransRateZ(float) override;

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
  // OpenGL
  std::vector<float>& GetGLVertices() override;
  std::vector<uint>& GetEBO() override;

  // Affine
  // const Rates& GetTransRates() override;
  const Rate& GetTransRateX() override;
  const Rate& GetTransRateY() override;
  const Rate& GetTransRateZ() override;

  const Rate& GetRotAngleX() override;
  const Rate& GetRotAngleY() override;
  const Rate& GetRotAngleZ() override;

  const Rate& GetScaleRate() override;

  // Vert
  const Rate& GetVertSz() override;
  const uint16_t& GetVertStyle() override;
  const Color& GetVertClr() override;

  // Edge
  const Rate& GetEdgeSz() override;
  const uint16_t& GetEdgeStyle() override;
  const Color& GetEdgeClr() override;

  // Misc
  const Color& GetBckgClr() override;
  const uint16_t& GetProjType() override;
  const uint16_t& GetRenderType() override;
  const Str& GetFilename() override;
};

}  // namespace s21

#endif  // !CONTROLLER_H_
