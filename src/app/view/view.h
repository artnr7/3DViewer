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

private slots:
  void OnActionTriggered(SceneAction action, ActionData data);

private:
  void SetupConnections();

  /* Fields */
  MenuWidget *pmenu_wid_;
  ObjectViewerWidget *pobj_v_wid_;
  IController *pcontroller_;
};

} // namespace s21

#endif
