#include "model.h"

namespace s21 {

// Affine
// Translate
//
template <typename F>
void Model::AddSet(F f, const char* fn) {
  Lg::Log()->Trace("Model::" + std::string(fn));
  f();
  obj_->a_.UpdGLVertices();
}

void Model::SetTransRateX(float x) {  // X
  AddSet([&] { obj_->a_.SetTransX(x); }, __func__);
}

void Model::SetTransRateY(float y) {  // Y
  AddSet([&] { obj_->a_.SetTransY(y); }, __func__);
}
void Model::SetTransRateZ(float z) {  // Z
  AddSet([&] { obj_->a_.SetTransZ(z); }, __func__);
}

void Model::AddTransRateX(float x) {  // X
  AddSet([&] { obj_->a_.AddTransX(x); }, __func__);
}

void Model::AddTransRateY(float y) {  // Y
  AddSet([&] { obj_->a_.AddTransY(y); }, __func__);
}

void Model::AddTransRateZ(float z) {  // Z
  AddSet([&] { obj_->a_.AddTransZ(z); }, __func__);
}

// Rotate
void Model::SetRotAngleX(float x) {  // X
  AddSet([&] { obj_->a_.SetRotX(x); }, __func__);
}

void Model::SetRotAngleY(float y) {  // Y
  AddSet([&] { obj_->a_.SetRotY(y); }, __func__);
}

void Model::SetRotAngleZ(float z) {  // Z
  AddSet([&] { obj_->a_.SetRotZ(z); }, __func__);
}
void Model::AddRotAngleX(float x) {  // X
  AddSet([&] { obj_->a_.AddRotX(x); }, __func__);
}
void Model::AddRotAngleY(float y) {  // Y
  AddSet([&] { obj_->a_.AddRotY(y); }, __func__);
}
void Model::AddRotAngleZ(float z) {  // Z
  AddSet([&] { obj_->a_.AddRotZ(z); }, __func__);
}

// Scale
void Model::SetScaleRate(float scl_rt) {
  AddSet([&] { obj_->a_.SetScale(scl_rt); }, __func__);
}

void Model::AddScaleRate(float scl_rt) {
  AddSet([&] { obj_->a_.AddScale(scl_rt); }, __func__);
}

// Vert
void Model::SetVertSz(float vert_sz) { sett_control_->SetVertSz(vert_sz); }
void Model::SetVertStyle(uint16_t vert_style) {
  sett_control_->SetVertStyle(vert_style);
}
void Model::SetVertClr(Color vert_clr) { sett_control_->SetVertClr(vert_clr); }

// Edge
void Model::SetEdgeSz(float edge_sz) { sett_control_->SetEdgeSz(edge_sz); }
void Model::SetEdgeStyle(uint16_t edge_style) {
  sett_control_->SetEdgeStyle(edge_style);
}
void Model::SetEdgeClr(Color edge_clr) { sett_control_->SetEdgeClr(edge_clr); }

// Misc
void Model::SetBckgClr(Color bckg_clr) { sett_control_->SetBckgClr(bckg_clr); }

}  // namespace s21
