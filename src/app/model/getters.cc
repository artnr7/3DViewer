#include "model.h"

namespace s21 {

// Affine
const Angles& Model::GetRotAngles() { return sett_control_->GetRotAngles(); }
const Rates& Model::GetTransRates() { return sett_control_->GetTransRates(); }
const float& Model::GetScaleRate() { return sett_control_->GetScaleRate(); }

// Vert
const float& Model::GetVertSz() { return sett_control_->GetVertSz(); }
const uint16_t& Model::GetVertStyle() { return sett_control_->GetVertStyle(); }
const Color& Model::GetVertClr() {
  // sett_control_->GetVertClr().Print();
  return sett_control_->GetVertClr();
}

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
