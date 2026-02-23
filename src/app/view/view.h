#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QWidget>
#include <qtimer.h>

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
  void OnControllerDataUpdateStarted();

signals:
  void ControllerDataUpdateStarted();

private:
  void ObjectBuilded();
  void SetupConnections();

  /* Fields */
  MenuWidget *pmenu_wid_;
  ObjectViewerWidget *pobj_v_wid_;
  IController *pcontroller_;

  QTimer *menu_wid_update_timer_;
};

} // namespace s21

#endif
