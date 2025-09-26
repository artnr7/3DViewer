#include "../main_window.hpp"

s21::MainWindow::MainWindow() {
  setWindowTitle("3DViewer");
  setGeometry(400, 200, 1000, 800);
  p_menu_wid_ = new MenuWidget(this);
  Connections();
}