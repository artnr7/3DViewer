#include <iostream>

#include "object_class.h"

#include "../../utils/logger.h"

namespace s21 {

Object::Object(const std::string &obj_filename)
    : points_{}, faces_{}, glvertices_{}, filename_{obj_filename}, ofl_it_{},
      eofl_it_(), scale_(), a_(*this) {
  Lg::Log()->Info(std::string(__func__) + " constructor");

  ObjectParser();
  // PrintArray();
  // PrintFaces();
  ObjectCentering();
  Normalization();
  FillGLvertices();
  MakeEBO();
  // PrintEBO();
}

} // namespace s21
