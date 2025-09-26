#include "../../../../controller/controller.hpp"
#include "../../config.hpp"
#include "../object_viewer_widget.hpp"

// s21::ObjectViewerWidget::ObjectViewerWidget() {
//
// }

s21::ObjectViewerWidget::ObjectViewerWidget(QWidget *parent,
                                            const std::string &obj_filename)
    : QOpenGLWidget(parent), obj_filename_(obj_filename) {
  setWindowTitle("3DViewer");
  setGeometry(INIT_AX_OBJECT_WIDGET, INIT_AY_OBJECT_WIDGET,
              INIT_W_OBJECT_WIDGET, INIT_H_OBJECT_WIDGET);
  s21::Controller::CreateNewObject(obj_filename_);
}
