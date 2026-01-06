#ifndef VIEW_HPP_
#define VIEW_HPP_

#include "app.h"

namespace s21 {

class View {
 public:
  View(int argc, char *argv[]);
  int AppExec();

 private:
  App *app_;
};
}  // namespace s21

#endif