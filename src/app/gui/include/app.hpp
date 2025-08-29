#ifndef APP_HPP_
#define APP_HPP_

#include <QApplication>

namespace s21 {
class App : public QApplication {
  Q_OBJECT

public:
  App(int argc, char *argv[]);

private:
};
} // namespace s21

#endif