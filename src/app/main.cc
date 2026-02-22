#include <QApplication>
#include <QSurfaceFormat>

#include "controller.h"
#include "logger.h"
#include "model.h"
#include "view.h"

std::unique_ptr<s21::Logger> s21::Logger::instance_ = nullptr;

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  s21::Model model;
  s21::Controller controller(&model);
  s21::View view(&controller);

  view.show();

  return app.exec();
}
