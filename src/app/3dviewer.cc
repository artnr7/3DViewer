#include "utils/logger.hpp"
#include "view/include/view.hpp"

std::unique_ptr<s21::Logger> s21::Logger::instance_ = nullptr;

int main(int argc, char *argv[]) {
  s21::View *view = new s21::View(argc, argv);
  return view->AppExec();
}