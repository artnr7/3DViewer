#include "object_class.hpp"
#include <iostream>

s21::Object::Object(const std::string &file_name)
    : vertices_{}, faces_{}, glvertices_{}, file_name_{file_name}, ofl_it_{} {
  std::cout << "Loading Model " << std::endl;
  ObjectParser();
  ObjectCentering();
  FillGLvertices();
}