#include "../include/app.hpp"

s21::App::App(int argc, char *argv[]) : QApplication(argc, argv) {
  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);

  format.setVersion(4, 5);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  std::unique_ptr<MainWindow> p_main_win(new MainWindow());

  p_main_win->show();
}

s21::App::~App() = default;