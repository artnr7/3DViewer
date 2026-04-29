#ifndef CONTROLLER_INTERFACE_H_
#define CONTROLLER_INTERFACE_H_

#include <qtypes.h>

#include <cstdint>
#include <string>
#include <vector>

#include "primitives.h"

namespace s21 {

class IController {
 public:
  // build
  virtual void BuildObject(const std::string& filename) = 0;

  // SETTERS -------------------------------
  // Affine
  virtual void SetTransRateX(float) = 0;
  virtual void SetTransRateY(float) = 0;
  virtual void SetTransRateZ(float) = 0;

  virtual void AddTransRateX(float) = 0;
  virtual void AddTransRateY(float) = 0;
  virtual void AddTransRateZ(float) = 0;

  virtual void SetRotAngleX(float) = 0;
  virtual void SetRotAngleY(float) = 0;
  virtual void SetRotAngleZ(float) = 0;

  virtual void AddRotAngleX(float) = 0;
  virtual void AddRotAngleY(float) = 0;
  virtual void AddRotAngleZ(float) = 0;

  virtual void SetScaleRate(float) = 0;
  virtual void AddScaleRate(float) = 0;

  // Vert
  virtual void SetVertSz(float) = 0;
  virtual void SetVertStyle(uint16_t) = 0;
  virtual void SetVertClr(Color) = 0;

  // Edge
  virtual void SetEdgeSz(float) = 0;
  virtual void SetEdgeStyle(uint16_t) = 0;
  virtual void SetEdgeClr(Color) = 0;

  // Misc
  virtual void SetBckgClr(Color) = 0;

  // GETTERS -------------------------------
  // OpenGL
  virtual std::vector<float>& GetGLVertices() = 0;
  virtual std::vector<uint>& GetEBO() = 0;

  // Affine
  // virtual const Rates& GetTransRates() = 0;
  virtual const Rate& GetTransRateX() = 0;
  virtual const Rate& GetTransRateY() = 0;
  virtual const Rate& GetTransRateZ() = 0;

  virtual const Angles& GetRotAngles() = 0;
  virtual const float& GetScaleRate() = 0;

  // Vert
  virtual const float& GetVertSz() = 0;
  virtual const uint16_t& GetVertStyle() = 0;
  virtual const Color& GetVertClr() = 0;

  // Edge
  virtual const float& GetEdgeSz() = 0;
  virtual const uint16_t& GetEdgeStyle() = 0;
  virtual const Color& GetEdgeClr() = 0;

  // Misc
  virtual const Color& GetBckgClr() = 0;
  virtual const uint16_t& GetProjType() = 0;
  virtual const uint16_t& GetRenderType() = 0;
  virtual const Str& GetFilename() = 0;

  // virtual CModelData &GetCModelData() = 0;
};

}  // namespace s21

#endif  // !CONTROLLER_INTERFACE_H_
