#include "../object_viewer_widget.hpp"

s21::ObjectViewerWidget::ObjectViewerWidget(QWidget *parent)
    : QOpenGLWidget(parent), obj_filename_() {
  setWindowTitle("3DViewer");
  setGeometry(400, 200, 800, 600);
  SetObjFilename();
  [[maybe_unused]] s21::Controller *controller =
      new s21::Controller(obj_filename_);
  // s21::Controller::SetObjFilename(obj_filename_);
  // m_shader_program_ = new QOpenGLShaderProgram(this);
}

void s21::ObjectViewerWidget::SetObjFilename() noexcept {
  obj_filename_ = "../objs/cube.obj";
}