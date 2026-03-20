#include <QApplication>
#include <QSurfaceFormat>

#include "controller.h"
#include "logger.h"
#include "model.h"
#include "view.h"

#define CFF (//clang-format off)

std::unique_ptr<s21::Lg> s21::Lg::inst_ = nullptr;

int main(int argc, char* argv[]) {
  s21::Lg::Log()->Info(std::string(__func__));
  // s21::Lg::Log()->SetLogLevel(s21::Lg::LogLevel::TRACE);

  QApplication app(argc, argv);

  s21::Model model;
  s21::Controller controller(&model);
  s21::View view(&controller);

  s21::Lg::Log()->Info("View show");
  view.show();

  return app.exec();
}
