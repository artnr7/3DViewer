#include "model.h"

namespace s21 {

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
