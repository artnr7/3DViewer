#include "../utils/logger.h"
#include "controller.h"

namespace s21 {

// Affine
void Controller::SetTransRateX(float x) { model_->SetTransRateX(x); }
void Controller::SetTransRateY(float y) { model_->SetTransRateY(y); }
void Controller::SetTransRateZ(float z) { model_->SetTransRateZ(z); }

void Controller::AddTransRateX(float x) { model_->AddTransRateX(x); }
void Controller::AddTransRateY(float y) { model_->AddTransRateY(y); }
void Controller::AddTransRateZ(float z) { model_->AddTransRateZ(z); }

void Controller::SetRotAngleX(float x) { model_->SetRotAngleX(x); }
void Controller::SetRotAngleY(float y) { model_->SetRotAngleY(y); }
void Controller::SetRotAngleZ(float z) { model_->SetRotAngleZ(z); }

void Controller::AddRotAngleX(float x) { model_->AddRotAngleX(x); }
void Controller::AddRotAngleY(float y) { model_->AddRotAngleY(y); }
void Controller::AddRotAngleZ(float z) { model_->AddRotAngleZ(z); }

void Controller::SetScaleRate(float scl_rt) { model_->SetScaleRate(scl_rt); }
void Controller::AddScaleRate(float scl_rt) { model_->AddScaleRate(scl_rt); }

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

}  // namespace s21
