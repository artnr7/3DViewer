
#include "../main_window.hpp"

void s21::MainWindow::Connections() {
  QTimer temp_timer{};
  temp_timer.start(5000);

  connect(&temp_timer, &QTimer::timeout, this,
          &s21::MainWindow::CreateNewObjectImitated);

  connect(this, &s21::MainWindow::NewFilenameEntered, this,
          &s21::MainWindow::CreateNewObjectWidget);
}