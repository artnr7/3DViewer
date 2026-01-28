#include "model.h"
#include "controller.h"
#include "logger.h"

#include "view.h"
#include <QApplication>
#include <QSurfaceFormat>

std::unique_ptr<s21::Logger> s21::Logger::instance_ = nullptr;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  s21::Model model;
  s21::Controller controller(&model);
  s21::View view(&controller);
  // //s21::Controller controller(&model, &view);
  view.show();

  return app.exec();
}
