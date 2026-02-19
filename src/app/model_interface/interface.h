#include "string"
#include "vector"

namespace s21 {

class IModel {
public:
  // create/build
  virtual void BuildObject(const std::string &filename);

  // get glvertices
  virtual std::vector<float> &GetGLVertices();

  // update data
  virtual void MoveObject();
  virtual void ZoomObject();
};

} // namespace s21
