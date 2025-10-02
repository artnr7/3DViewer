
#include "../main_window.hpp"

void s21::MainWindow::Connections() {
  connect(p_menu_wid_, &s21::MenuWidget::NewFilenameEntered, this,
          &s21::MainWindow::CreateNewObjectWidget);
}