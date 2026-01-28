#ifndef ACTION_TYPES_H_
#define ACTION_TYPES_H_

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

// using ActionData = std::variant<double, int, QColor, QString, bool>;
 using ActionData = std::variant<int>;

} // namespace s21

#endif // ACTION_TYPES_H_
