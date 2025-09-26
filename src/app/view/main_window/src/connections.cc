
#include "../main_window.hpp"

void s21::MainWindow::Connections() {
  temp_timer = new QTimer(this);
  temp_timer->start(3000);

  connect(temp_timer, &QTimer::timeout, this,
          &s21::MainWindow::CreateNewObjectImitated);

  connect(this, &s21::MainWindow::NewFilenameEntered, this,
          &s21::MainWindow::CreateNewObjectWidget);
}