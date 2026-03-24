#include "model.h"

namespace s21 {

// Affine
// Translate
void Model::SetTransRateX(float x) {  // X
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.SetTransX(x);
  obj_->a_.UpdGLVertices();
}
void Model::SetTransRateY(float y) {  // Y
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.SetTransX(y);
  obj_->a_.UpdGLVertices();
}
void Model::SetTransRateZ(float z) {  // Z
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.SetTransZ(z);
  obj_->a_.UpdGLVertices();
}

void Model::AddTransRateX(float x) {  // X
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.AddTransX(x);
  obj_->a_.UpdGLVertices();
}

void Model::AddTransRateY(float y) {  // Y
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.AddTransY(y);
  obj_->a_.UpdGLVertices();
}

void Model::AddTransRateZ(float z) {  // Z
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.AddTransZ(z);
  obj_->a_.UpdGLVertices();
}

// Rotate
void Model::SetRotAngleX(float x) {  // X
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.SetRotX(x);
  obj_->a_.UpdGLVertices();
}

void Model::SetRotAngleY(float y) {  // Y
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.SetRotY(y);
  obj_->a_.UpdGLVertices();
}

void Model::SetRotAngleZ(float z) {  // Z
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.SetRotZ(z);
  obj_->a_.UpdGLVertices();
}
void Model::AddRotAngleX(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.AddRotX(x);
  obj_->a_.UpdGLVertices();
}
void Model::AddRotAngleY(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.AddRotY(x);
  obj_->a_.UpdGLVertices();
}
void Model::AddRotAngleZ(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.AddRotZ(x);
  obj_->a_.UpdGLVertices();
}

// Scale
void Model::SetScaleRate(float scl_rt) {
  Lg::Log()->Info("Model::" + std::string(__func__));
  obj_->a_.SetScale(scl_rt);
  obj_->a_.UpdGLVertices();
}

void Model::AddScaleRate(float scl_rt) {
  Lg::Log()->Info("Model::" + std::string(__func__));
  obj_->a_.AddScale(scl_rt);
  obj_->a_.UpdGLVertices();
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
