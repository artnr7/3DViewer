#include "../include/app.hpp"

#include "../object_viewer_widget/object_viewer_widget.hpp"

s21::App::App(int argc, char *argv[]) : QApplication(argc, argv) {
  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);

  format.setVersion(4, 5);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  ObjectViewerWidget *obj_viewer_wid = new ObjectViewerWidget();
  obj_viewer_wid->show();
}

s21::App::~App() {}