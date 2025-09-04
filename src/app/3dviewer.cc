#include "gui/include/view.hpp"
// #include <QApplication>
// #include <QtWidgets/QMainWindow>

int main(int argc, char *argv[]) {
  // s21::View *view = new s21::View(argc, argv);
  // return view->AppExec();
  s21::App app(argc, argv);

  // s21::MainWidget m_wid(&mainWindow);
  // mainWindow.setCentralWidget(&m_wid);

  // mainWindow.show();

  return app.exec();
}