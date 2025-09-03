#include "gui/include/view.hpp"
// #include <QApplication>
// #include <QtWidgets/QMainWindow>

int main(int argc, char *argv[]) {
  // s21::View *view = new s21::View(argc, argv);
  // return view->AppExec();

  // QApplication app(argc, argv);
  // QMainWindow mainWindow;
  s21::App app(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);

  format.setVersion(2, 1);
  // format.setProfile(QSurfaceFormat::CoreProfile);
  format.setProfile(QSurfaceFormat::CompatibilityProfile);
  QSurfaceFormat::setDefaultFormat(format);

  s21::MainWidget *m_wid = new s21::MainWidget();
  // m_wid->resize(800, 600);
  m_wid->show();

  // s21::MainWidget m_wid(&mainWindow);
  // mainWindow.setCentralWidget(&m_wid);

  // mainWindow.show();

  return app.exec();
}