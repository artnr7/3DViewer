#include "../include/view.hpp"

s21::View::View(int argc, char *argv[]) { app_ = new App(argc, argv); }

int s21::View::AppExec() { return app_->exec(); }