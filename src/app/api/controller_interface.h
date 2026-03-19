#ifndef CONTROLLER_INTERFACE_H_
#define CONTROLLER_INTERFACE_H_

#include "primitives.h"
#include <cstdint>
#include <qtypes.h>
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
  // struct RGBColor {
  //   int r, g, b;
  // };
  //
  // struct CModelData {
  //   float vertex_size;
  //   int vertex_style;
  //   RGBColor vertex_color;
  //
  //   float edge_thickness;
  //   int edge_style;
  //   RGBColor edge_color;
  //   RGBColor background_color;
  // };

  virtual void BuildObject(const std::string &filename) = 0;

  // SETTERS -------------------------------
  virtual void SetRotAngleX(float) = 0;
  virtual void SetRotAngleY(float) = 0;
  virtual void SetRotAngleZ(float) = 0;

  virtual void AddRotAngle(Angles) = 0;

  virtual void SetTransRateX(float) = 0;
  virtual void SetTransRateY(float) = 0;
  virtual void SetTransRateZ(float) = 0;

  virtual void AddTransRates(Rates) = 0;

  virtual void SetScaleRate(float) = 0;

  virtual void SetVertSz(float) = 0;
  virtual void SetVertStyle(uint16_t) = 0;
  virtual void SetVertClr(Color) = 0;

  virtual void SetEdgeSz(float) = 0;
  virtual void SetEdgeStyle(uint16_t) = 0;
  virtual void SetEdgeClr(Color) = 0;
  virtual void SetBckgClr(Color) = 0;

  // GETTERS -------------------------------
  // get glvertices
  virtual std::vector<float> &GetGLVertices() = 0;
  virtual std::vector<uint> &GetEBO() = 0;

  // Affine
  virtual const Angles &GetRotAngles() = 0;
  virtual const Rates &GetTransRates() = 0;
  virtual const float &GetScaleRate() = 0;

  // Vert
  virtual const float &GetVertSz() = 0;
  virtual const uint16_t &GetVertStyle() = 0;
  virtual const Color &GetVertClr() = 0;

  // Edge
  virtual const float &GetEdgeSz() = 0;
  virtual const uint16_t &GetEdgeStyle() = 0;
  virtual const Color &GetEdgeClr() = 0;

  // Misc
  virtual const Color &GetBckgClr() = 0;
  virtual const uint16_t &GetProjType() = 0;
  virtual const uint16_t &GetRenderType() = 0;
  virtual const Str &GetFilename() = 0;

  // virtual CModelData &GetCModelData() = 0;
};

} // namespace s21

#endif // !CONTROLLER_INTERFACE_H_
