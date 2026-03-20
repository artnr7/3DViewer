#include "controller.h"

#include <string>

#include "../utils/logger.h"
#include "iostream"

namespace s21 {

// SETTERS -------------------------------
// Affine
void Controller::SetTransRateX(float x) {}
void Controller::SetTransRateY(float y) {}
void Controller::SetTransRateZ(float z) {}

void Controller::AddTransRateX(float x) { model_->AddTransRateX(x); }
void Controller::AddTransRateY(float y) { model_->AddTransRateY(y); }
void Controller::AddTransRateZ(float z) { model_->AddTransRateZ(z); }

void Controller::SetRotAngleX(float x) {}
void Controller::SetRotAngleY(float y) {}
void Controller::SetRotAngleZ(float z) {}

void Controller::AddRotAngleX(float x) { model_->AddRotAngleX(x); }
void Controller::AddRotAngleY(float y) { model_->AddRotAngleY(y); }
void Controller::AddRotAngleZ(float z) { model_->AddRotAngleZ(z); }

void Controller::SetScaleRate(float) {}

// Vert
void Controller::SetVertSz(float vert_sz) { model_->SetVertSz(vert_sz); }
void Controller::SetVertStyle(uint16_t vert_style) {
  model_->SetVertStyle(vert_style);
}
void Controller::SetVertClr(Color vert_clr) { model_->SetVertClr(vert_clr); }

// Edge
void Controller::SetEdgeSz(float edge_sz) { model_->SetEdgeSz(edge_sz); }
void Controller::SetEdgeStyle(uint16_t edge_style) {
  model_->SetEdgeStyle(edge_style);
}
void Controller::SetEdgeClr(Color edge_clr) { model_->SetEdgeClr(edge_clr); }

// Misc
void Controller::SetBckgClr(Color bckg_clr) { model_->SetBckgClr(bckg_clr); }

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
