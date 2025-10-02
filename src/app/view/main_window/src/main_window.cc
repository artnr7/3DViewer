#include "../main_window.hpp"

#include <qglobal.h>

// #include "../../../controller/controller.hpp"
#include "../../../utils/logger.hpp"
#include "../config.hpp"

s21::MainWindow::MainWindow() {
  s21::Logger::Log()->Msg(std::string(__func__) + " Constructor...",
                          Logger::MessageType::Process);

  setWindowTitle("3DViewer");
  setGeometry(INIT_AX_MAIN_WINDOW, INIT_AY_MAIN_WINDOW, INIT_W_MAIN_WINDOW,
              INIT_H_MAIN_WINDOW);
  p_menu_wid_ = new MenuWidget(this);
  Connections();
}

// Color --------------------------------------------------------------------→
void s21::MainWindow::SetObjVBckgColor(const std::array<GLclampf, 4> &color) {
  p_obj_v_wid_->SetBckgColor(color);
}

void s21::MainWindow::SetObjVEdgeColor() { p_obj_v_wid_->SetEdgeColor(); }

void s21::MainWindow::SetObjVVerticeColor() { p_obj_v_wid_->SetVerticeColor(); }

// Edge thickness -----------------------------------------------------------→
void s21::MainWindow::SetObjVEdgeThickness() {
  p_obj_v_wid_->SetEdgeThickness();
}

// Vertices -----------------------------------------------------------------→
// Mapping -------→
void s21::MainWindow::SetObjVVerticeMapping(
    const VerticeMappingType &v_map_type) {
  p_obj_v_wid_->SetVerticeMapping(v_map_type);
}
// Size -----→
void s21::MainWindow::SetObjVVerticeSize() { p_obj_v_wid_->SetEdgeThickness(); }

// Projection type -----------------------------------------------------------→
void s21::MainWindow::SetObjVProjection(const ProjectionType &proj_type) {
  Q_UNUSED(proj_type);
  // вызов s21::Controller::Функция изменения вида проекции на нужную
}