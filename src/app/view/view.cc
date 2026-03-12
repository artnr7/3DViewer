#include "view.h"

namespace s21 {
void View::OnObjectStartBuild() {
  // по сути это надо вызывать, когда есть уверенность, что файл в модели
  // загружен
  Lg::Log()->Info("View:" + std::string(__func__));

  // menu
  menu_wid_update_timer_->start(15);
  // obj_widget
  pobj_v_wid_->ObjectInit();
}

void View::OnTranslateOnX(float x) { pcontroller_->TranslateOnX(x); }
void View::OnTranslateOnY(float x) { pcontroller_->TranslateOnY(x); }
void View::OnTranslateOnZ(float x) { pcontroller_->TranslateOnZ(x); }

void View::OnRotateOnX(float x) { pcontroller_->RotateOnX(x); }
void View::OnRotateOnY(float x) { pcontroller_->RotateOnY(x); }
void View::OnRotateOnZ(float x) { pcontroller_->RotateOnZ(x); }
} // namespace s21
