#include "../include/mainwindow.hpp"

s21::MainWindow::MainWindow(QWindow *parent = nullptr) {
  MainWidget *w = new MainWidget();

  w->setFormat(format); 
}