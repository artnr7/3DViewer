#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "TriangleWidget.h"
#include <iostream>

int main(int argc, char *argv[]) {
  // QApplication app(argc, argv);

  // QMainWindow mainWindow;

  // TriangleWidget centralWidget(&mainWindow);
  // mainWindow.setCentralWidget(&centralWidget);

  // mainWindow.show();

  // return app.exec();

  GLfloat v1[] = {5.0f, 5.0f, 5.0f, 5.0f, 5.0f};

  std::cout << sizeof(v1) << std::endl;

  GLfloat *v2 = new GLfloat[5]{5.0f};

  std::cout << sizeof(v2) << std::endl;

  delete[] v2;
}