// #include "logger.h"
#include "view.h"

namespace s21 {

void View::OnControllerDataUpdateStarted() {
  Lg::Log()->Info("View:" + std::string(__func__));
  menu_wid_update_timer_->start(15);
}

void View::OnGetGLVertices() {
  Lg::Log()->Info("View:" + std::string(__func__));
  GetNSetGLVertices();
}

} // namespace s21
