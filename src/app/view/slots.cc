// #include "logger.h"
#include "view.h"

namespace s21 {

// Может имеет смысл кешировать данные из модели ???

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

void View::OnObjectViewerBackgroundColorUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  auto cmodel_data = pcontroller_->GetCModelData();
  auto col = cmodel_data.background_color;
  // std::cout << col.r << " " << col.g << " " << col.b << std ::endl;
  pobj_v_wid_->SetBackgroundColor(col.r, col.g, col.b);
}

void View::OnObjectViewerEdgeColorUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  auto cmodel_data = pcontroller_->GetCModelData();
  auto col = cmodel_data.edge_color;
  // std::cout << col.r << " " << col.g << " " << col.b << std ::endl;
  pobj_v_wid_->SetEdgeColor(col.r, col.g, col.b);
}

void View::OnObjectViewerVerticesSizeUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  auto cmodel_data = pcontroller_->GetCModelData();
  pobj_v_wid_->SetVerticesSize(cmodel_data.vertex_size);
}

void View::OnObjectViewerLineWidthUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  auto cmodel_data = pcontroller_->GetCModelData();
  pobj_v_wid_->SetLinesWidth(cmodel_data.edge_thickness);
}

void View::OnObjectViewerContinuityLineUpdate() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  auto cmodel_data = pcontroller_->GetCModelData();
  pobj_v_wid_->SetContinuityLine(
      static_cast<LineStyle>(cmodel_data.edge_style));
}

void View::OnObjectViewerVerticeStyleUpdate() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  auto cmodel_data = pcontroller_->GetCModelData();
  pobj_v_wid_->SetVerticeStyle(
      static_cast<VerticeStyle>(cmodel_data.vertex_style));
}

} // namespace s21
