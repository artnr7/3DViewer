#include "object_class.hpp"

s21::Object::Object(std::string &file_name) : file_name_(file_name) {}

void s21::Object::ObjectParser() {
  std::ifstream obj_file_stream(file_name_);

  std::string obj_file_line = "";

  poly_pc_i_t vert_i = 0;
  while (std::getline(obj_file_stream, obj_file_line)) {
    ParseVLine(obj_file_line, vert_i);
  }
}

void s21::Object::ParseVLine(std::string &obj_file_line, poly_pc_i_t &vert_i) {
  str_it_t ofl_it = obj_file_line.begin();

  if (*ofl_it != 'v') {
    return;
  }
  vert_it_t vert_it = vertices_.begin();
  vert_it++->i = vert_i++;

  ParseVLineNums(vert_it, ofl_it);
}

void s21::Object::ParseVLineNums(vert_it_t &vert_it, str_it_t &ofl_it) {
  ParseNum(vert_it->x, ofl_it);
  ParseNum(vert_it->y, ofl_it);
  ParseNum(vert_it->z, ofl_it);
}

void s21::Object::ParseNum(coord_t &coord, str_it_t &ofl_it) {
  std::string num{};
  while (*ofl_it != ' ' && *ofl_it != '\n') {
    num += *ofl_it++;
  }
  char **endptr{};
  coord = std::strtold(num.c_str(), endptr);
}