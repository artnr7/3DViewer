#ifndef ACTION_TYPES_H_
#define ACTION_TYPES_H_

#include <qmainwindow.h>
#include <qobject.h>

#include <QColor>
#include <QString>

namespace s21 {

enum class SceneAction {
  /* Transform */
  kTranslateX,
  kTranslateY,
  kTranslateZ,
  kRotateX,
  kRotateY,
  kRotateZ,
  kScale,

  /* Shading */
  kVertexSize,
  kVertexStyle,
  kVertexColor,
  kEdgeThickness,
  kEdgeStyle,
  kEdgeColor,
  kBackgroundColor,

  /* Projection */
  kProjection,

  /* Render */
  kRender,

  /* Files */
  kOpenFile
};

enum class VertexStyle { kEmpty, kSquare, kCircle };
enum class EdgeStyle { kLine, kDashLine };
enum class ProjectionType { kPerspective, kOrthographic };
enum class RenderType { kGif, kImage };

using ActionData = std::variant<int, QString, QColor, VertexStyle, EdgeStyle, ProjectionType, RenderType>;

}  // namespace s21

#endif  // ACTION_TYPES_H_
