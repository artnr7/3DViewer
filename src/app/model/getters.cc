
#include "model.h"
#include "object_class/object_class.h"

#include "../utils/logger.h"
#include <array>
#include <stdexcept>
#include <variant>

namespace s21 {

const Angles &Model::GetRotAngles() { return sett_control_->GetRotAngles(); }

const Rates &Model::GetTransRates() { return sett_control_->GetTransRates(); }
const float &Model::GetScaleRate() { return sett_control_->GetScaleRate(); }

const float &Model::GetVertSz() { return sett_control_->GetVertexSz(); }
const uint16_t &Model::GetVertStyle() {
  return sett_control_->GetVertexStyle();
}

const Color &Model::GetVertClr() { return sett_control_->GetVertexClr(); }

const float &Model::GetEdgeSz() { return sett_control_->GetEdgeSz(); }
const uint16_t &Model::GetEdgeStyle() { return sett_control_->GetEdgeStyle(); }

const Color &Model::GetEdgeClr() { return sett_control_->GetEdgeClr(); }

const Color &Model::GetBckgClr() { return sett_control_->GetBckgClr(); }

const uint16_t &Model::GetProjType() { return sett_control_->GetProjType(); }
const uint16_t &Model::GetRenderType() {
  return sett_control_->GetRenderType();
}

const Str &Model::GetFilename() { return sett_control_->GetFilename(); }
} // namespace s21
