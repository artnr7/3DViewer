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
  virtual void TranslateObject() = 0;
  virtual void ScaleObject() = 0;
};

} // namespace s21
#endif
