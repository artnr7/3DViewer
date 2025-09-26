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
  QTimer *temp_timer;


  void Connections();

 public:
  MainWindow();

 signals:
  void NewFilenameEntered(const std::string& obj_filename);

 private slots:
  void CreateNewObjectWidget(const std::string& obj_filename);
  void CreateNewObjectImitated();
};
}  // namespace s21

#endif
