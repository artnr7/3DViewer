// #include "logger.h"
#include "view.h"

namespace s21 {

// Может имеет смысл кешировать данные из модели ???

// Inner
void View::OnMenuWidgetTimerUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pmenu_wid_->OnUpdateObjectInfo();
}

// Inner Setters
void View::updGLVert() {
  Lg::Log()->Trace("View:" + std::string(__func__));

  pobj_v_wid_->SetEBO(pcontroller_->GetEBO());
  pobj_v_wid_->SetVBO(pcontroller_->GetGLVertices());
}

void View::updTransX(float x) { pcontroller_->AddTransRateX(x); }
void View::updTransY(float y) { pcontroller_->AddTransRateY(y); }
void View::updTransZ(float z) { pcontroller_->AddTransRateZ(z); }

void View::updRotX(float x) { pcontroller_->AddRotAngleX(x); }
void View::updRotY(float y) { pcontroller_->AddRotAngleY(y); }
void View::updRotZ(float z) { pcontroller_->AddRotAngleZ(z); }

// Edge
void View::updVertSz() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetVertSz(pcontroller_->GetVertSz());
}

void View::updVertStyle() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetVertStyle(
      static_cast<VertStyle>(pcontroller_->GetVertStyle()));
}

void View::updVertClr() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetVertClr(pcontroller_->GetVertClr());
}

// Edge
void View::updEdgeSz() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetEdgeSz(pcontroller_->GetEdgeSz());
}

void View::updEdgeStyle() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetEdgeStyle(
      static_cast<EdgeStyle>(pcontroller_->GetEdgeStyle()));
}

void View::updEdgeClr() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetEdgeClr(pcontroller_->GetEdgeClr());
}

// Misc
void View::updBckgClr() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetBckgClr(pcontroller_->GetBckgClr());
}

}  // namespace s21
