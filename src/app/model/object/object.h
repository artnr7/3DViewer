#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <cstdint>

#include "../../utils/logger.h"
#include "affine/affine.h"
#include "parser/parser.h"
#include "types.h"

namespace s21 {

class Object {
 private:
  // Variables
  Vertices vertices_{};
  Faces faces_{};
  bool init_f_ = true;

  // GL
  std::vector<float> glvertices_{};
  std::vector<uint> ebo_{};

  // file
  std::string filename_;

  float normalization_scale_ = 0;
  uint8_t dim_qty_ = THREE_DIMENSIONAL;

  // Methods
  void ObjectCentering();
  void Normalization();

  Parser p_;

 public:
  friend class Parser;
  friend class Affine;
  Affine a_;

  // Constructors --------------------→
  Object() : p_(*this), a_(*this) {};
  explicit Object(const std::string& obj_filename)
      : filename_{obj_filename}, p_(*this), a_(*this) {
    Lg::Log()->Info(std::string(__func__) + " constructor");

    p_.Parse();
    // PrintArray();
    // PrintFaces();
    // PrintVertMinMax();
    ObjectCentering();
    Normalization();

    a_.UpdGLVertices();
    // PrintGLVertices();
    MakeEBO();
    // PrintEBO();
  }

  std::vector<float>& GetGLVertices() { return glvertices_; }
  std::vector<uint>& GetEBO() { return ebo_; }

  // utils
  void PrintVertMinMax();
  void PrintArray();
  void PrintFaces();
  void PrintEBO();
  void PrintGLVertices();

  void MakeEBO();
};
}  // namespace s21

#endif
