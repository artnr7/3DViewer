#include "controller.h"

#include <string>

#include "../utils/logger.h"
#include "iostream"

namespace s21 {

// SETTERS -------------------------------
// Affine
void Controller::SetRotAngleX(float) {}
void Controller::SetRotAngleY(float) {}
void Controller::SetRotAngleZ(float) {}

void Controller::AddRotAngleX(float) {}
void Controller::AddRotAngleY(float) {}
void Controller::AddRotAngleZ(float) {}

void Controller::SetTransRateX(float) {}
void Controller::SetTransRateY(float) {}
void Controller::SetTransRateZ(float) {}

void Controller::AddTransRateX(float) {}
void Controller::AddTransRateY(float) {}
void Controller::AddTransRateZ(float) {}

void Controller::SetScaleRate(float) {}

// Vert
void Controller::SetVertSz(float) {}
void Controller::SetVertStyle(uint16_t) {}
void Controller::SetVertClr(Color) {}

// Edge
void Controller::SetEdgeSz(float) {}
void Controller::SetEdgeStyle(uint16_t) {}
void Controller::SetEdgeClr(Color) {}
void Controller::SetBckgClr(Color) {}

// GETTERS -------------------------------
std::vector<float>& Controller::GetGLVertices() {
  return model_->GetGLVertices();
}
std::vector<uint>& Controller::GetEBO() { return model_->GetEBO(); }
//

// Controller::CModelData &Controller::GetCModelData() {
//   // Lg::Log()->Info("Controller::" + std::string(__func__));
//   return testdata_;
// }
}  // namespace s21
