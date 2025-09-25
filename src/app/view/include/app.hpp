#ifndef APP_HPP_
#define APP_HPP_

#include <QApplication>
#include <QtOpenGL>

#include "../main_window/main_window.hpp"

namespace s21 {
class App : public QApplication {
  Q_OBJECT

 public:
  App(int argc, char *argv[]);
  virtual ~App();

 private:
};
}  // namespace s21

#endif