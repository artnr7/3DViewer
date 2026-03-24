#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QTimer>
#include <QWidget>

#include "controller.h"
#include "menu_widget/menu_widget.h"
#include "object_viewer_widget/obj_v_wid.h"

namespace s21 {

class View : public QWidget {
  Q_OBJECT

 public:
  View(Controller* controller, QWidget* parent = nullptr);

 private slots:
  // MenuWidget
  void OnActionTriggered(SceneAction action, ActionData data);
  void OnMenuWidgetTimerUpdated();

  // ObjectViewerWidget
  // Affine
  void updTransX(float x);
  void updTransY(float y);
  void updTransZ(float z);

  void updRotX(float x);
  void updRotY(float y);
  void updRotZ(float z);

  void updScaleRate(float);

  // Vert
  void updVertSz();
  void updVertStyle();
  void updVertClr();

  // Edge
  void updEdgeSz();
  void updEdgeStyle();
  void updEdgeClr();

  // Misc
  void updBckgClr();

  // Buffers
  void updGLVert();

 private:
  void RunViewUpdAgents();
  void MenuWidgetSetupConnections();
  void ObjViewerWidgetSetupConnections();

  /* Fields */
  MenuWidget* pmenu_wid_;
  ObjectViewerWidget* pobj_v_wid_;
  IController* pcontroller_;

  QTimer* menu_wid_update_timer_;
};

}  // namespace s21

#endif
