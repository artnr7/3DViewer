#include "../main_window.hpp"

void s21::MainWindow::Connections() {
  static int i = 0;
  if (i++ == 1000) {
    emit NewFilenameEntered();
  }

  connect(this, &s21::MainWindow::NewFilenameEntered, this,
          &s21::MainWindow::CreateNewObjectWidget);
}