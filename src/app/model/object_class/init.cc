#include "object_class.hpp"

s21::Object::Object(std::string &file_name)
    : vertices_{}, faces_{}, glvertices_{}, file_name_{file_name}, ofl_it_{} {

  ObjectParser();
  FillGLvertices();
}