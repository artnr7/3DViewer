// #include "logger.h"
#include "view.h"

namespace s21 {

void View::OnGetGLVertices() {
  Lg::Log()->Trace("View:" + std::string(__func__));

  pobj_v_wid_->SetEBO(pcontroller_->GetEBO());
  pobj_v_wid_->SetVBO(pcontroller_->GetGLVertices());
}

void View::OnMenuWidgetTimerUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  auto cmodel_data = pcontroller_->GetCModelData();
  pmenu_wid_->OnUpdateObjectInfo();
}

void View::OnObjectViewerBackgroundUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  auto cmodel_data = pcontroller_->GetCModelData();
  auto col = cmodel_data.background_color;
  // std::cout << col.r << " " << col.g << " " << col.b << std ::endl;
  pobj_v_wid_->SetBackgroundColor(col.r, col.g, col.b);
}

} // namespace s21
