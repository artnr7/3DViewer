
#include <string>

#include "../utils/logger.h"
#include "controller.h"

namespace s21 {

std::vector<float>& Controller::GetGLVertices() {
  return model_->GetGLVertices();
}
std::vector<uint>& Controller::GetEBO() { return model_->GetEBO(); }

// Affine
// const Rates& Controller::GetTransRates() { return model_->GetTransRates(); }
const Rate& Controller::GetTransRateX() { return model_->GetTransRateX(); }
const Rate& Controller::GetTransRateY() { return model_->GetTransRateY(); }
const Rate& Controller::GetTransRateZ() { return model_->GetTransRateZ(); }

const Rate& Controller::GetRotAngleX() { return model_->GetRotAngleX(); }
const Rate& Controller::GetRotAngleY() { return model_->GetRotAngleY(); }
const Rate& Controller::GetRotAngleZ() { return model_->GetRotAngleZ(); }

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
