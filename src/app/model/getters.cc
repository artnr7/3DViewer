#include "model.h"

namespace s21 {

// Affine
std::vector<float>& Model::GetGLVertices() {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  if (obj_ == nullptr) {
    throw std::runtime_error("obj is not initialized");
  }

  return obj_->GetGLVertices();
}

std::vector<uint>& Model::GetEBO() {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  if (obj_ == nullptr) {
    throw std::runtime_error("obj is not initialized");
  }

  return obj_->GetEBO();
}

const Angles& Model::GetRotAngles() { return sett_control_->GetRotAngles(); }
const Rates& Model::GetTransRates() { return sett_control_->GetTransRates(); }
const float& Model::GetScaleRate() { return sett_control_->GetScaleRate(); }

// Vert
const float& Model::GetVertSz() { return sett_control_->GetVertSz(); }
const uint16_t& Model::GetVertStyle() { return sett_control_->GetVertStyle(); }
const Color& Model::GetVertClr() { return sett_control_->GetVertClr(); }

// Edge
const float& Model::GetEdgeSz() { return sett_control_->GetEdgeSz(); }
const uint16_t& Model::GetEdgeStyle() { return sett_control_->GetEdgeStyle(); }
const Color& Model::GetEdgeClr() { return sett_control_->GetEdgeClr(); }

// Misc
const Color& Model::GetBckgClr() { return sett_control_->GetBckgClr(); }
const uint16_t& Model::GetProjType() { return sett_control_->GetProjType(); }
const uint16_t& Model::GetRenderType() {
  return sett_control_->GetRenderType();
}
const Str& Model::GetFilename() { return sett_control_->GetFilename(); }
}  // namespace s21
