#include <iostream>

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

  static long int i = 0;
  if (!i++) {
    auto &vert = vertices_.vertices;

    vert.min_x = vert_it->x;
    vert.max_x = vert_it->x;
    vert.min_y = vert_it->y;
    vert.max_y = vert_it->y;
    vert.min_z = vert_it->z;
    vert.max_z = vert_it->z;

  } else {
    FindMinMax(vert_it);
  }
}

void s21::Object::ParseNum(CoordT &coord) {
  std::string num{};
  while (!IsSpace() && !IsEndOfLine()) {
    num += *ofl_it_++;
  }
  char **endptr{};
  coord = std::strtold(num.c_str(), endptr);

  while (*ofl_it_ == ' ') {
    ++ofl_it_;
  }
}

void s21::Object::FindMinMax(VertIter &vert_it) {
  auto &vert = vertices_.vertices;
  if (vert_it->x < vert.min_x) {
    vert.min_x = vert_it->x;
  }
  if (vert_it->x > vert.max_x) {
    vert.max_x = vert_it->x;
  }
  if (vert_it->y < vert.min_y) {
    vert.min_y = vert_it->y;
  }
  if (vert_it->y > vert.max_y) {
    vert.max_y = vert_it->y;
  }
  if (vert_it->z < vert.min_z) {
    vert.min_y = vert_it->y;
  }
  if (vert_it->z > vert.max_z) {
    vert.max_z = vert_it->z;
  }
}