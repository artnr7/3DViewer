#include "view.h"
#include "config.h"
#include "controller.h"
#include "menu_widget.h"
#include "object_viewer_widget.h"

namespace s21 {

View::View(Controller* controller, QWidget* parent)
  : QWidget(parent)
  , controller_(controller) {
  setWindowTitle("3DViewer");
  setGeometry(INIT_AX_MAIN_WINDOW, INIT_AY_MAIN_WINDOW, INIT_W_MAIN_WINDOW,
              INIT_H_MAIN_WINDOW);

  p_menu_wid_ = new MenuWidget(INIT_W_MENU_WIDGET, INIT_H_MENU_WIDGET, this);
  p_obj_v_wid_ = new ObjectViewerWidget(INIT_AX_OBJECT_WIDGET, INIT_AY_OBJECT_WIDGET, INIT_W_OBJECT_WIDGET, INIT_H_OBJECT_WIDGET, this);

  SetupConnections();
}

void View::SetupConnections() {
  connect(p_menu_wid_, &MenuWidget::ActionTriggered, controller_, &Controller::OnActionTriggered);
}

} // namespace s21
