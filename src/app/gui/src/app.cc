#include "../include/app.hpp"

s21::App::App(int argc, char *argv[]) : QApplication(argc, argv) {
  // QSurfaceFormat format;
  // format.setDepthBufferSize(24);
  // format.setStencilBufferSize(8);

  // format.setVersion(2, 1);
  // format.setProfile(QSurfaceFormat::CoreProfile);
  // format.setProfile(QSurfaceFormat::CompatibilityProfile);
  // QSurfaceFormat::setDefaultFormat(format);

  // MainWidget *m_wid = new MainWidget();
  // m_wid->show();
}

s21::App::~App() {}