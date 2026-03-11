#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QTimer>
#include <QWidget>

#include "controller.h"
#include "menu_widget/menu_widget.h"
#include "object_viewer_widget/object_viewer_widget.h"

#include "../../utils/logger.h"

namespace s21 {

class View : public QWidget {
  Q_OBJECT

public:
  View(Controller *controller, QWidget *parent = nullptr);

private slots:
  void OnActionTriggered(SceneAction action, ActionData data);
  void OnGetGLVertices();
  void OnMenuWidgetTimerUpdated();
  void OnObjectViewerBackgroundUpdated();

private:
  void OnObjectStartBuild();
  void SetupConnections();

  void OnTranslateOnX(float x);
  void OnTranslateOnY(float y);
  void OnTranslateOnZ(float z);

  /* Fields */
  MenuWidget *pmenu_wid_;
  ObjectViewerWidget *pobj_v_wid_;
  IController *pcontroller_;

  QTimer *menu_wid_update_timer_;
};

} // namespace s21

#endif
