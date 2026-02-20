#ifndef CONTROLLER_INTERFACE_H_
#define CONTROLLER_INTERFACE_H_

#include <string>
#include <vector>

namespace s21 {
enum class ObjectAction {
  /* Transform */
  kTranslateX,
  kTranslateY,
  kTranslateZ,
  kRotateX,
  kRotateY,
  kRotateZ,
  kScale,

  /* Shading */
  // kVertexSize,
  // kVertexStyle,
  // kVertexColor,
  // kEdgeThickness,
  // kEdgeStyle,
  // kEdgeColor,
  // kBackgroundColor,
};

class IController {

public:
  virtual void BuildObject(const std::string &filename) = 0;

  // get glvertices
  virtual std::vector<float> &GetGLVertices() = 0;

  virtual void TranslateObject() = 0;
  virtual void RotateObject() = 0;
  virtual void ScaleObject() = 0;
};

} // namespace s21

#endif // !CONTROLLER_INTERFACE_H_
