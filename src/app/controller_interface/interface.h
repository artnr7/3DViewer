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

// struct CModelData {
//   VertexSize
//
// }

class IController {
public:
  virtual void BuildObject(const std::string &filename) = 0;

  // SETTERS -------------------------------
  virtual void TranslateObject() = 0;
  virtual void RotateObject() = 0;
  virtual void ScaleObject() = 0;

  virtual void SetVertexSize() = 0;
  virtual void SetVertexStyle() = 0;
  virtual void SetVertexColor() = 0;
  virtual void SetVertexThickness() = 0;
  virtual void SetEdgeStyle() = 0;
  virtual void SetEdgeColor() = 0;
  virtual void SetBackgroundColor() = 0;

  // GETTERS -------------------------------
  // get glvertices
  virtual std::vector<float> &GetGLVertices() = 0;

  //
  virtual void GetVertexSize() = 0;
  virtual void GetVertexStyle() = 0;
  virtual void GetVertexColor() = 0;
  virtual void GetVertexThickness() = 0;
  virtual void GetEdgeStyle() = 0;
  virtual void GetEdgeColor() = 0;
  virtual void GetBackgroundColor() = 0;
};

} // namespace s21

#endif // !CONTROLLER_INTERFACE_H_
