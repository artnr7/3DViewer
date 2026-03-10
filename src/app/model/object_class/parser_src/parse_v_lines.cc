#include <iostream>

#include "object_class.h"

namespace s21 {

void Object::Parser::ParseVLine(IndT &v_ind, std::string &obj_file_line) {
  ofl_it_ = obj_file_line.begin();

  if (!IsVLine()) {
    return;
  }
  eofl_it_ = obj_file_line.end();
  ++ofl_it_;
  while (IsSpace()) {
    ++ofl_it_;
  }

  obj_.vertices_.maps.push_back(vec4{});

  VertIter v_it = obj_.vertices_.maps.begin() + v_ind;
  // vert_it->first = ++vert_i;

  ParseVLineNums(v_it);
}

void Object::Parser::ParseVLineNums(VertIter &v_it) {
  ParseNum(v_it->x);
  ParseNum(v_it->y);
  ParseNum(v_it->z);

  FindMinMax(v_it);
}

void Object::Parser::ParseNum(CoordT &coord) {
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

void Object::Parser::FindMinMax(VertIter &v_it) {
  auto &mnx = obj_.vertices_.mnx;

  if (parser_once_f) {
    mnx.min_x, mnx.max_x = v_it->x, v_it->x;
    mnx.min_y, mnx.max_y = v_it->y, v_it->y;
    mnx.min_z, mnx.max_z = v_it->z, v_it->z;

    parser_once_f = false;
    return;
  }

  Min(v_it->x, mnx.min_x);
  Max(v_it->x, mnx.max_x);

  Min(v_it->y, mnx.min_y);
  Max(v_it->y, mnx.max_y);

  Min(v_it->z, mnx.min_z);
  Max(v_it->z, mnx.max_z);
}

void Object::Parser::Min(CoordT coord, CoordT &min) {
  if (coord < min)
    min = coord;
}

void Object::Parser::Max(CoordT coord, CoordT &max) {
  if (coord > max)
    max = coord;
}

} // namespace s21
