// #include "logger.h"
#include "view.h"

namespace s21 {

void View::OnControllerDataUpdateStarted() {
  menu_wid_update_timer_->start(15);
}

} // namespace s21
