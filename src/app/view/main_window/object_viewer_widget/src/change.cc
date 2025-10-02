#include <qglobal.h>

#include <array>

#include "../object_viewer_widget.hpp"

void s21::ObjectViewerWidget::SetBckgColor(
    const std::array<GLclampf, 4>& color) {
  bckg_color_ = {color[0], color[1], color[2], color[3]};
}

void s21::ObjectViewerWidget::SetEdgeColor() {}

void s21::ObjectViewerWidget::SetVerticeColor() {}

// Edge thickness -------------→
void s21::ObjectViewerWidget::SetEdgeThickness() {}

// Vertices ---------------------------→
// Mapping ---→
void s21::ObjectViewerWidget::SetVerticeMapping(
    const VerticeMappingType& v_map_type) {
  Q_UNUSED(v_map_type);
}
// Size ---→
void s21::ObjectViewerWidget::SetVerticeSize() {}