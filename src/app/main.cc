#include <QApplication>
#include <QSurfaceFormat>
#include <source_location>

#include "controller.h"
#include "logger.h"
#include "model.h"
#include "view.h"

std::unique_ptr<s21::Lg> s21::Lg::inst_ = nullptr;

int main(int argc, char *argv[]) {

  s21::Lg::Log()->Info(std::string(__func__));
  s21::Lg::Log()->Info(std::source_location::current().function_name());
  s21::Lg::Log()->Info(std::source_location::current().file_name());

  QApplication app(argc, argv);

  s21::Model model;
  s21::Controller controller(&model);
  s21::View view(&controller);

  s21::Lg::Log()->Info("View SHOW");
  view.show();

  return app.exec();
}
