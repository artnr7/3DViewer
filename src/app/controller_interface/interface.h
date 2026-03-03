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
  struct RGBColor {
    int r, g, b;
  };

  struct CModelData {
    int vertex_size;
    int vertex_style;
    RGBColor vertex_color;
    int edge_thickness;
    int edge_style;
    RGBColor edge_color;
    RGBColor background_color;
  };

  virtual void BuildObject(const std::string &filename) = 0;

  // SETTERS -------------------------------
  virtual void TranslateToX(float x) = 0;
  virtual void TranslateToY(float x) = 0;
  virtual void TranslateToZ(float x) = 0;

  virtual void TranslateOnX(float x) = 0;
  virtual void TranslateOnY(float x) = 0;
  virtual void TranslateOnZ(float x) = 0;

  virtual void RotateObject() = 0;
  virtual void ScaleObject() = 0;

  virtual void SetVertexSize() = 0;
  virtual void SetVertexStyle() = 0;
  virtual void SetVertexColor() = 0;
  virtual void SetVertexThickness() = 0;
  virtual void SetEdgeStyle() = 0;
  virtual void SetEdgeColor() = 0;
  virtual void SetBackgroundColor(int r, int g, int b) = 0;

  // GETTERS -------------------------------
  // get glvertices
  virtual std::vector<float> &GetGLVertices() = 0;
  virtual std::vector<uint> &GetEBO() = 0;

  //
  virtual void GetVertexSize() = 0;
  virtual void GetVertexStyle() = 0;
  virtual void GetVertexColor() = 0;
  virtual void GetVertexThickness() = 0;
  virtual void GetEdgeStyle() = 0;
  virtual void GetEdgeColor() = 0;
  virtual void GetBackgroundColor() = 0;

  virtual CModelData &GetCModelData() = 0;
};

} // namespace s21

#endif // !CONTROLLER_INTERFACE_H_
