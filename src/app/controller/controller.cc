#include "controller.h"
#include "../utils/logger.h"
#include "iostream"
#include <string>

namespace s21 {

// SETTERS -------------------------------
void Controller::SetRotAngleX(float) {}
void Controller::SetRotAngleY(float) {}
void Controller::SetRotAngleZ(float) {}

void Controller::AddRotAngle(Angles) {}

void Controller::SetTransRateX(float) {}
void Controller::SetTransRateY(float) {}
void Controller::SetTransRateZ(float) {}

void Controller::AddTransRates(Rates) {}

void Controller::SetScaleRate(float) {}

void Controller::SetVertSz(float) {}
void Controller::SetVertStyle(uint16_t) {}
void Controller::SetVertClr(Color) {}

void Controller::SetEdgeSz(float) {}
void Controller::SetEdgeStyle(uint16_t) {}
void Controller::SetEdgeClr(Color) {}
void Controller::SetBckgClr(Color) {}

// GETTERS -------------------------------
std::vector<float> &Controller::GetGLVertices() {
  return model_->GetGLVertices();
}
std::vector<uint> &Controller::GetEBO() { return model_->GetEBO(); }
//

// Controller::CModelData &Controller::GetCModelData() {
//   // Lg::Log()->Info("Controller::" + std::string(__func__));
//   return testdata_;
// }
} // namespace s21
