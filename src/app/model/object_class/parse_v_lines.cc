#include "object_class.hpp"

void s21::Object::ParseVLine(PolyPcInT &vert_i, std::string &obj_file_line) {
  ofl_it_ = obj_file_line.begin();

  if (!IsVLine()) {
    return;
  }
  eofl_it_ = obj_file_line.end();
  ++ofl_it_;
  while (IsSpace()) {
    ++ofl_it_;
  }

  vertices_.vertices.vertice_maps.push_back({0, 0, 0, 0});

  VertIter vert_it = vertices_.vertices.vertice_maps.begin() + vert_i;
  vert_it->i = ++vert_i;

  ParseVLineNums(vert_it);
}

void s21::Object::ParseVLineNums(VertIter &vert_it) {
  ParseNum(vert_it->x);
  ParseNum(vert_it->y);
  ParseNum(vert_it->z);
}

void s21::Object::ParseNum(CoordT &coord) {
  std::string num{};
  while (*ofl_it_ != ' ' && ofl_it_ != eofl_it_) {
    num += *ofl_it_++;
  }
  char **endptr{};
  coord = std::strtold(num.c_str(), endptr);
  while (*ofl_it_ == ' ') {
    ++ofl_it_;
  }
}
