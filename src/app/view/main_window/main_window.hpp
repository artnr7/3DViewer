#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include <QWidget>

#include "menu_widget/menu_widget.hpp"
#include "object_viewer_widget/object_viewer_widget.hpp"

namespace s21 {
class MainWindow : public QWidget {
  Q_OBJECT
 private:
  // Variables ---------------------------→
  ObjectViewerWidget* p_obj_v_wid_;
  MenuWidget* p_menu_wid_;

  void Connections();

 public:
  MainWindow();

 private slots:
  void CreateNewObjectWidget(const std::string& obj_filename);
  // friend s21::MenuWidget;
  // Color ------------>
  void SetObjVBckgColor(const std::array<GLclampf, 4>& color);
  void SetObjVEdgeColor();
  void SetObjVVerticeColor();

  // Edge thickness -------------→
  void SetObjVEdgeThickness();

  // Vertices ---------------------------→
  // Mapping ---→
  void SetObjVVerticeMapping(const VerticeMappingType& v_map_type);
  // Size ---→
  void SetObjVVerticeSize();

  // Projections ------------>
  void SetObjVProjection(const ProjectionType& proj_type);
};
}  // namespace s21

#endif
