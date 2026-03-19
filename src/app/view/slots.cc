// #include "logger.h"
#include "view.h"

namespace s21 {

// Может имеет смысл кешировать данные из модели ???

void View::OnTranslateOnX(float x) {}
void View::OnTranslateOnY(float x) {}
void View::OnTranslateOnZ(float x) {}

void View::OnRotateOnX(float x) {}
void View::OnRotateOnY(float x) {}
void View::OnRotateOnZ(float x) {}

void View::OnGetGLVertices() {
  Lg::Log()->Trace("View:" + std::string(__func__));

  pobj_v_wid_->SetEBO(pcontroller_->GetEBO());
  pobj_v_wid_->SetVBO(pcontroller_->GetGLVertices());
}

// Inner
void View::OnMenuWidgetTimerUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pmenu_wid_->OnUpdateObjectInfo();
}

void View::OnObjectViewerBackgroundColorUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetBckgClr(pcontroller_->GetBckgClr());
}

void View::OnObjectViewerEdgeColorUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetEdgeColor(pcontroller_->GetEdgeClr());
}

void View::OnObjectViewerVerticesSizeUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetVertexSz(pcontroller_->GetVertSz());
}

void View::OnObjectViewerLineWidthUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetEdgeW(pcontroller_->GetEdgeSz());
}

void View::OnObjectViewerContinuityLineUpdate() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetEdgeStyle(
      static_cast<EdgesStyle>(pcontroller_->GetEdgeStyle()));
}

void View::OnObjectViewerVerticeStyleUpdate() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetVertexStyle(
      static_cast<VerticeStyle>(pcontroller_->GetVertStyle()));
}
void View::OnObjectViewerVertexClrUpd() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetVertexClr(pcontroller_->GetVertClr());
}

} // namespace s21
