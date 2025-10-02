#include "../../../utils/logger.hpp"
#include "../main_window.hpp"

void s21::MainWindow::CreateNewObjectWidget(const std::string &obj_filename) {
  s21::Logger::Log()->Msg(
      std::string(__func__) + " Creating new object viewer widget...",
      Logger::MessageType::Process);
  if (p_obj_v_wid_ != nullptr) {
    delete p_obj_v_wid_;
  }

  p_obj_v_wid_ = new ObjectViewerWidget(this, obj_filename);
  p_obj_v_wid_->show();
}
