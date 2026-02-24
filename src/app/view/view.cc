#include "view.h"

namespace s21 {

void View::GetModelData() {
  // pmenu_wid_->UpdateInfo(int vertices_count, int edges_count)
  pcontroller_->GetBackgroundColor();
}

void View::ObjectBuilded() {
  pobj_v_wid_->SetGLVertices(pcontroller_->GetGLVertices());
  pobj_v_wid_->initGL();
  emit ControllerDataUpdateStarted();
}

void View::GetNSetGLVertices() {
  pobj_v_wid_->SetGLVertices(pcontroller_->GetGLVertices());
}

} // namespace s21
