#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include <QWidget>

#include "menu_widget/menu_widget.hpp"
#include "object_viewer_widget/object_viewer_widget.hpp"

namespace s21 {
class MainWindow : public QWidget {
  Q_OBJECT
 private:
  // Variables ---------------------------→
  ObjectViewerWidget* p_obj_v_wid_;
  MenuWidget* p_menu_wid_;

  void Connections();

 public:
  MainWindow();

 signals:
  void NewFilenameEntered();

 private slots:
  void CreateNewObjectWidget();
};
}  // namespace s21

#endif
