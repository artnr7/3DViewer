#ifndef MODEL_INTERFACE_
#define MODEL_INTERFACE_

#include "string"
#include "vector"

#include "primitives.h"
#include <cstdint>

namespace s21 {
class IModel {
public:
  // create/build
  virtual void BuildObject(const std::string &filename) = 0;

  // get glvertices
  virtual std::vector<float> &GetGLVertices() = 0;
  virtual std::vector<uint> &GetEBO() = 0;

  // Setters
  virtual void TranslateToX(float x) = 0;
  virtual void TranslateToY(float x) = 0;
  virtual void TranslateToZ(float x) = 0;

  virtual void TranslateOnX(float x) = 0;
  virtual void TranslateOnY(float x) = 0;
  virtual void TranslateOnZ(float x) = 0;

  virtual void RotateToX(float) = 0;
  virtual void RotateToY(float) = 0;
  virtual void RotateToZ(float) = 0;

  virtual void RotateOnX(float) = 0;
  virtual void RotateOnY(float) = 0;
  virtual void RotateOnZ(float) = 0;

  virtual void ScaleObject(float) = 0;

  // Getters
  virtual const Angles &GetRotAngles() = 0;
  virtual const Rates &GetTransRates() = 0;
  virtual const float &GetScaleRate() = 0;

  virtual const float &GetVertSz() = 0;
  virtual const uint16_t &GetVertStyle() = 0;

  virtual const Color &GetVertClr() = 0;

  virtual const float &GetEdgeSz() = 0;
  virtual const uint16_t &GetEdgeStyle() = 0;

  virtual const Color &GetEdgeClr() = 0;

  virtual const Color &GetBckgClr() = 0;

  virtual const uint16_t &GetProjType() = 0;
  virtual const uint16_t &GetRenderType() = 0;

  virtual const Str &GetFilename() = 0;
};

} // namespace s21
#endif
