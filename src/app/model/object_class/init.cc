#include <iostream>

#include "object_class.h"

#include "../../utils/logger.h"

s21::Object::Object(const std::string &obj_filename)
    : vertices_{}, faces_{}, glvertices_{}, filename_{obj_filename}, ofl_it_{},
      eofl_it_(), scale_() {
  Lg::Log()->Info(std::string(__func__) + " constructor");

  ObjectParser();
  PrintArray();
  ObjectCentering();
  Normalization();
  FillGLvertices();
}
