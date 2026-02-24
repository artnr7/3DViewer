#include "view.h"

namespace s21 {
void View::OnObjectStartBuild() {
  Lg::Log()->Info("View:" + std::string(__func__));

  menu_wid_update_timer_->start(15);
  pobj_v_wid_->ObjectInit();
}
} // namespace s21
