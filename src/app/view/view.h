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
  View(Controller* controller, QWidget* parent = nullptr)
      : QWidget(parent), pcontroller_(controller) {
    Lg::Log()->Info(std::string(__func__) + " constuctor");
    setWindowTitle("3DViewer");
    setGeometry(INIT_AX_MAIN_WIN, INIT_AY_MAIN_WIN, INIT_W_MAIN_WIN,
                INIT_H_MAIN_WIN);

    ObjViewerWidgetSetupConnections();
    MenuWidgetSetupConnections();
    // TODO:(sundaeka) надо считать настройки до состояния когда можно уже
    // загружать файл
  }

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
  MenuWidget* pmenu_wid_ =
      new MenuWidget(INIT_W_MENU_WID, INIT_H_MENU_WID, this);
  ObjectViewerWidget* pobj_v_wid_ =
      new ObjectViewerWidget(INIT_AX_OBJECT_WIDGET, INIT_AY_OBJECT_WID,
                             INIT_W_OBJECT_WID, INIT_H_OBJ_WID, this);
  IController* pcontroller_;

  QTimer* menu_wid_update_timer_ = new QTimer(this);
};

}  // namespace s21

#endif
