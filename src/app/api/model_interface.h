#ifndef MODEL_INTERFACE_
#define MODEL_INTERFACE_

#include "string"
#include "vector"

namespace s21 {

class IModel {
public:
  // create/build
  virtual void BuildObject(const std::string &filename) = 0;

  // get glvertices
  virtual std::vector<float> &GetGLVertices() = 0;
  virtual std::vector<uint> &GetEBO() = 0;

  // update data
  virtual void TranslateToX(float x) = 0;
  virtual void TranslateToY(float x) = 0;
  virtual void TranslateToZ(float x) = 0;

  virtual void TranslateOnX(float x) = 0;
  virtual void TranslateOnY(float x) = 0;
  virtual void TranslateOnZ(float x) = 0;

  virtual void RotateX(float) = 0;
  virtual void RotateY(float) = 0;
  virtual void RotateZ(float) = 0;

  virtual void ScaleObject(float) = 0;
};

} // namespace s21
#endif
