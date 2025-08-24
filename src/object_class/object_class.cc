#include "object_class.hpp"

s21::Object::Object(std::string &file_name) : file_name_(file_name) {}

void s21::Object::ObjectParser() {
  std::ifstream obj_file_stream(file_name_);

  std::string obj_file_line = "";

  std::getline(obj_file_stream, obj_file_line);

  
}