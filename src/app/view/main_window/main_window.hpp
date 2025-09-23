#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP

#include "menu_widget/menu_widget.hpp"
#include "object_viewer_widget/object_viewer_widget.hpp"
#include <QWidget>

namespace s21 {
class MainWindow : public QWidget {
  Q_OBJECT
private:
  std::unique_ptr<ObjectViewerWidget> p_obj_v_wid_;
  std::unique_ptr<MenuWidget> p_menu_wid_;

public:
  MainWindow();
};
} // namespace s21

#endif
