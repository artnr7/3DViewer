
#include <string>

#include "../utils/logger.h"
#include "controller.h"

namespace s21 {

std::vector<float>& Controller::GetGLVertices() {
  return model_->GetGLVertices();
}
std::vector<uint>& Controller::GetEBO() { return model_->GetEBO(); }

// Affine
const Angles& Controller::GetRotAngles() { return model_->GetRotAngles(); }
const Rates& Controller::GetTransRates() { return model_->GetTransRates(); }
const float& Controller::GetScaleRate() { return model_->GetScaleRate(); }

// Vert
const float& Controller::GetVertSz() { return model_->GetVertSz(); }
const uint16_t& Controller::GetVertStyle() { return model_->GetVertStyle(); }
const Color& Controller::GetVertClr() { return model_->GetVertClr(); }

// Edge
const float& Controller::GetEdgeSz() { return model_->GetEdgeSz(); }
const uint16_t& Controller::GetEdgeStyle() { return model_->GetEdgeStyle(); }
const Color& Controller::GetEdgeClr() { return model_->GetEdgeClr(); }

// Misc
const Color& Controller::GetBckgClr() { return model_->GetBckgClr(); }
const uint16_t& Controller::GetProjType() { return model_->GetProjType(); }
const uint16_t& Controller::GetRenderType() { return model_->GetRenderType(); }
const Str& Controller::GetFilename() { return model_->GetFilename(); }

}  // namespace s21
