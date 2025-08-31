#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QOpenGLWindow>

#include "mainwidget.hpp"

namespace s21 {
class MainWindow : public QOpenGLWindow {
  Q_OBJECT

public:
  MainWindow(QWindow *parent = nullptr) : QOpenGLWindow(parent) {}

protected:
};
} // namespace s21

#endif