// #include "logger.h"
#include "view.h"

namespace s21 {

// Может имеет смысл кешировать данные из модели ???

void View::OnTranslateOnX(float x) { pcontroller_->TranslateOnX(x); }
void View::OnTranslateOnY(float x) { pcontroller_->TranslateOnY(x); }
void View::OnTranslateOnZ(float x) { pcontroller_->TranslateOnZ(x); }

void View::OnRotateOnX(float x) { pcontroller_->RotateOnX(x); }
void View::OnRotateOnY(float x) { pcontroller_->RotateOnY(x); }
void View::OnRotateOnZ(float x) { pcontroller_->RotateOnZ(x); }

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
  pobj_v_wid_->SetBckgClr(col.r, col.g, col.b);
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
  pobj_v_wid_->SetVertexSz(cmodel_data.vertex_size);
}

void View::OnObjectViewerLineWidthUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  auto cmodel_data = pcontroller_->GetCModelData();
  pobj_v_wid_->SetEdgeW(cmodel_data.edge_thickness);
}

void View::OnObjectViewerContinuityLineUpdate() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  auto cmodel_data = pcontroller_->GetCModelData();
  pobj_v_wid_->SetEdgeStyle(static_cast<EdgesStyle>(cmodel_data.edge_style));
}

void View::OnObjectViewerVerticeStyleUpdate() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  auto cmodel_data = pcontroller_->GetCModelData();
  pobj_v_wid_->SetVertexStyle(
      static_cast<VerticeStyle>(cmodel_data.vertex_style));
}
void View::OnObjectViewerVertexClrUpd() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  auto cmodel_data = pcontroller_->GetCModelData();
  auto col = cmodel_data.vertex_color;
  pobj_v_wid_->SetVertexClr(col.r, col.g, col.b);
}

} // namespace s21
