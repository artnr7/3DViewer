#include "main_window.h"
#include "config.h"

s21::MainWindow::MainWindow() {
  setWindowTitle("3DViewer");
  setGeometry(INIT_AX_MAIN_WINDOW, INIT_AY_MAIN_WINDOW, INIT_W_MAIN_WINDOW,
              INIT_H_MAIN_WINDOW);
  p_menu_wid_ = new MenuWidget(INIT_W_MENU_WIDGET, INIT_H_MENU_WIDGET,this);
  Connections();
}
