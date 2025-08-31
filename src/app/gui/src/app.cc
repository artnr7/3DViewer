#include "../include/app.hpp"

s21::App::App(int argc, char *argv[]) : QApplication(argc, argv) {

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);

  format.setVersion(3, 2);
  format.setProfile(QSurfaceFormat::CoreProfile);

  MainWidget *m_wid = new MainWidget();
}