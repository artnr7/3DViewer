// #include "logger.h"
#include <cstdio>

#include "action_types.h"
#include "view.h"

namespace s21 {

// Может имеет смысл кешировать данные из модели ???

// Inner
void View::OnMenuWidgetTimerUpdated() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  // Translate
  pmenu_wid_->OnActionTriggered(SceneAction::kTranslateX,
                                pcontroller_->GetTransRateX());
  pmenu_wid_->OnActionTriggered(SceneAction::kTranslateY,
                                pcontroller_->GetTransRateY());
  pmenu_wid_->OnActionTriggered(SceneAction::kTranslateZ,
                                pcontroller_->GetTransRateZ());
  // Rotate
  pmenu_wid_->OnActionTriggered(SceneAction::kRotateX,
                                pcontroller_->GetRotAngleX());
  pmenu_wid_->OnActionTriggered(SceneAction::kRotateY,
                                pcontroller_->GetRotAngleY());
  pmenu_wid_->OnActionTriggered(SceneAction::kRotateZ,
                                pcontroller_->GetRotAngleZ());
  // Scale
  pmenu_wid_->OnActionTriggered(SceneAction::kScale,
                                pcontroller_->GetScaleRate());

  // Vert
  pmenu_wid_->OnActionTriggered(SceneAction::kVertexSize,
                                pcontroller_->GetVertSz());
  pmenu_wid_->OnActionTriggered(SceneAction::kVertexStyle,
                                pcontroller_->GetVertStyle());
  auto vert_clr = pcontroller_->GetVertClr();
  auto qvert_clr = QColor{vert_clr.x, vert_clr.y, vert_clr.z};
  pmenu_wid_->OnActionTriggered(SceneAction::kVertexColor, qvert_clr);

  // Edge
  pmenu_wid_->OnActionTriggered(SceneAction::kEdgeThickness,
                                pcontroller_->GetEdgeSz());
  pmenu_wid_->OnActionTriggered(SceneAction::kEdgeStyle,
                                pcontroller_->GetEdgeStyle());
  auto edge_clr = pcontroller_->GetEdgeClr();
  auto qedge_clr = QColor{edge_clr.x, edge_clr.y, edge_clr.z};
  pmenu_wid_->OnActionTriggered(SceneAction::kEdgeColor, qedge_clr);

  // Misc
  auto bckg_clr = pcontroller_->GetBckgClr();
  auto qbckg_clr = QColor(bckg_clr.x, bckg_clr.y, bckg_clr.z);
  pmenu_wid_->OnActionTriggered(SceneAction::kBackgroundColor, qbckg_clr);
}

// Inner Setters
void View::updGLVert() {
  Lg::Log()->Trace("View:" + std::string(__func__));

  pobj_v_wid_->SetEBO(pcontroller_->GetEBO());
  pobj_v_wid_->SetVBO(pcontroller_->GetGLVertices());
}

// Outer
void View::updTransX(float x) { pcontroller_->AddTransRateX(x); }
void View::updTransY(float y) { pcontroller_->AddTransRateY(y); }
void View::updTransZ(float z) { pcontroller_->AddTransRateZ(z); }

void View::updRotX(float x) { pcontroller_->AddRotAngleX(x); }
void View::updRotY(float y) { pcontroller_->AddRotAngleY(y); }
void View::updRotZ(float z) { pcontroller_->AddRotAngleZ(z); }

void View::updScaleRate(float scl_rt) { pcontroller_->AddScaleRate(scl_rt); }

// Vert
void View::updVertSz() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetVertSz(pcontroller_->GetVertSz());
}

void View::updVertStyle() {
  Lg::Log()->Trace("View::" + std::string(__func__));

  pobj_v_wid_->SetVertStyle(
      static_cast<VertsStyle>(pcontroller_->GetVertStyle()));
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
      static_cast<EdgesStyle>(pcontroller_->GetEdgeStyle()));
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
