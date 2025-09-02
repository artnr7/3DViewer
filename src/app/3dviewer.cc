#include "gui/include/view.hpp"

int main(int argc, char *argv[]) {
  // s21::View *view = new s21::View(argc, argv);
  // return view->AppExec();

  s21::App app(argc, argv);

  return app.exec();
}