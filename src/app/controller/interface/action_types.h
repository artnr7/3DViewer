#ifndef ACTION_TYPES_H_
#define ACTION_TYPES_H_

#include <QString>
#include <QColor>

namespace s21 {

enum class SceneAction {
  /* Transform */
  kTranslateX, kTranslateY, kTranslateZ,
  kRotateX,    kRotateY,    kRotateZ,
  kScale,

  /* Shading */
  kVertexSize,    kVertexStyle, kVertexColor,
  kEdgeThickness, kEdgeStyle,   kEdgeColor,
  kBackgroundColor,

  /* Projection */
  kProjection,

  /* Render */
  kRender,

  /* Files */
  kOpenFile
};

enum class ComboBoxData {
  kCircle, kSquare,
  kLine, kDashLine
};

// using ActionData = std::variant<double, int, QColor, QString, bool>;
using ActionData = std::variant<int>;

} // namespace s21

#endif // ACTION_TYPES_H_
