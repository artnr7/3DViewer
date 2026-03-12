#include <iostream>

#include "object_class.h"

#include "../../utils/logger.h"

namespace s21 {

Object::Object(const std::string &obj_filename)
    : vertices_{}, faces_{}, glvertices_{}, filename_{obj_filename},
      normalization_scale_(), a_(*this), p_(*this) {
  Lg::Log()->Info(std::string(__func__) + " constructor");

  p_.Parse();
  // PrintArray();
  // PrintFaces();
  // PrintVertMinMax();
  ObjectCentering();
  Normalization();

  a_.Multiply();
  // PrintGLVertices();
  MakeEBO();
  // PrintEBO();
}

} // namespace s21
