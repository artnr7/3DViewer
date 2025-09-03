#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "TriangleWidget.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QMainWindow mainWindow;

  TriangleWidget centralWidget(&mainWindow);
  mainWindow.setCentralWidget(&centralWidget);

  mainWindow.show();

  return app.exec();
}