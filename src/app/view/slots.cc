// #include "logger.h"
#include "view.h"

namespace s21 {

void View::OnGetGLVertices() {
  // Lg::Log()->Info("View:" + std::string(__func__));
  static int i = 0;
    pobj_v_wid_->SetEBO(pcontroller_->GetEBO());
  pobj_v_wid_->SetVBO(pcontroller_->GetGLVertices());
}

void View::OnMenuWidgetTimerUpdated() {
  // Lg::Log()->Info("View::" + std::string(__func__));
  //
  auto cmodel_data = pcontroller_->GetCModelData();
  pmenu_wid_->OnUpdateObjectInfo();
}

void View::OnObjectViewerBackgroundUpdated() {
  // Lg::Log()->Info("View::" + std::string(__func__));

  auto cmodel_data = pcontroller_->GetCModelData();
  auto col = cmodel_data.background_color;
  // std::cout << col.r << " " << col.g << " " << col.b << std ::endl;
  pobj_v_wid_->SetBackgroundColor(col.r, col.g, col.b);
}

} // namespace s21
