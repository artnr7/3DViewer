#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QWidget>

#include "controller.h"
#include "menu_widget/menu_widget.h"
#include "object_viewer_widget/object_viewer_widget.h"

namespace s21 {

class View : public QWidget {
  Q_OBJECT

public:
  View(Controller *controller, QWidget *parent = nullptr);

private:
  void SetupConnections();

  /* Fields */
  MenuWidget *p_menu_wid_;
  ObjectViewerWidget *p_obj_v_wid_;
  Controller *controller_;
};

} // namespace s21

#endif
