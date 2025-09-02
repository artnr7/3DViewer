#ifndef APP_HPP_
#define APP_HPP_

#include <QApplication>

#include "mainwidget.hpp"

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