#include <iostream>

#include "object_class.hpp"

s21::Object::Object(const std::string &obj_filename)
    : vertices_{},
      faces_{},
      glvertices_{},
      file_name_{obj_filename},
      ofl_it_{},
      eofl_it_(),
      scale_() {
  std::cout << "Loading Model " << std::endl;
  ObjectParser();
  ObjectCentering();
  Normalization();
  FillGLvertices();
}