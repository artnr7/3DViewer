
#include <QString>
#include <QColor>

namespace s21 {

enum class SceneAction {
  kTranslateX, kTranslateY, kTranslateZ,
  kRotateX, kRotateY, kRotateZ,
  kScaleAll,
  kVertexColor,
  kOpenFile,
  kSwitchProjection
};

using ActionData = std::variant<double, int, QColor, QString, bool>;

} // namespace s21
