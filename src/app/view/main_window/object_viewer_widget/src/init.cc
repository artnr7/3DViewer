#include "../../../../controller/controller.hpp"
#include "../../../../utils/logger.hpp"
#include "../../config.hpp"
#include "../object_viewer_widget.hpp"

s21::ObjectViewerWidget::ObjectViewerWidget(QWidget *parent,
                                            const std::string &obj_filename,
                                            const int &w, const int &h)
    : QOpenGLWidget(parent),
      update_timer_(),
      glvertices_(),
      obj_filename_(obj_filename) {
  s21::Logger::Log()->Msg(std::string(__func__) + " Constructor...",
                          Logger::MessageType::Process);
  setWindowTitle("3DViewer");
  setGeometry(INIT_AX_OBJECT_WIDGET, INIT_AY_OBJECT_WIDGET,
              INIT_W_OBJECT_WIDGET, INIT_H_OBJECT_WIDGET);
  s21::Controller::CreateNewObject(obj_filename_, w, h);
  Connections();
}
