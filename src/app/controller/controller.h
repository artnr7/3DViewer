#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../api/controller_interface.h"
#include "../utils/logger.h"
#include <../api/model_interface.h>
#include <memory>
#include <qpixelformat.h>
#include <vector>

namespace s21 {

class Controller : public IController {
public:
  Controller(IModel *model) : model_(model) {}

  Controller() = delete;
  ~Controller() = default;

private:
  IModel *model_;

  // METHODS ------------------------
  void BuildObject(const std::string &filename) override {
    Lg::Log()->Info("Controller::" + std::string(__func__));
    model_->BuildObject(filename);
  }

  // SETTERS -------------------------------
  void SetRotAngleX(float) override;
  void SetRotAngleY(float) override;
  void SetRotAngleZ(float) override;

  void AddRotAngle(Angles) override;

  void SetTransRateX(float) override;
  void SetTransRateY(float) override;
  void SetTransRateZ(float) override;

  void AddTransRates(Rates) override;

  void SetScaleRate(float) override;

  void SetVertSz(float) override;
  void SetVertStyle(uint16_t) override;
  void SetVertClr(Color) override;

  void SetEdgeSz(float) override;
  void SetEdgeStyle(uint16_t) override;
  void SetEdgeClr(Color) override;
  void SetBckgClr(Color) override;

  // GETTERS -------------------------------
  // get glvertices
  std::vector<float> &GetGLVertices() override;
  std::vector<uint> &GetEBO() override;

  // Affine
  const Angles &GetRotAngles() override;
  const Rates &GetTransRates() override;
  const float &GetScaleRate() override;

  // Vert
  const float &GetVertSz() override;
  const uint16_t &GetVertStyle() override;
  const Color &GetVertClr() override;

  // Edge
  const float &GetEdgeSz() override;
  const uint16_t &GetEdgeStyle() override;
  const Color &GetEdgeClr() override;

  // Misc
  const Color &GetBckgClr() override;
  const uint16_t &GetProjType() override;
  const uint16_t &GetRenderType() override;
  const Str &GetFilename() override;

  // CModelData &GetCModelData() override;
};

} // namespace s21

#endif // !CONTROLLER_H_
