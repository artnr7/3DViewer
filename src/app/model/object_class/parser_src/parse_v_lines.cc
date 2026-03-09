#include <iostream>

#include "object_class.h"
namespace s21 {

void Object::Parser::ParseVLine(IndT &vert_i, std::string &obj_file_line) {
  ofl_it_ = obj_file_line.begin();

  if (!IsVLine()) {
    return;
  }
  eofl_it_ = obj_file_line.end();
  ++ofl_it_;
  while (IsSpace()) {
    ++ofl_it_;
  }

  obj_.vertices_.maps.push_back({});

  auto vert_it = obj_.vertices_.maps.begin() + vert_i;
  vert_it->first = ++vert_i;

  ParseVLineNums(vert_it);
}

void Object::Parser::ParseVLineNums(VertIter &vert_it) {
  auto [_, val] = *vert_it;
  ParseNum(val.x);
  ParseNum(val.y);
  ParseNum(val.z);

  FindMinMax(vert_it);
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

void Object::Parser::FindMinMax(VertIter &vert_it) {
  auto [_, val] = *vert_it;
  auto &mnx = obj_.vertices_.mnx;

  if (parser_once_f) {
    mnx.min_x, mnx.max_x = val.x, val.x;
    mnx.min_y, mnx.max_y = val.y, val.y;
    mnx.min_z, mnx.max_z = val.z, val.z;

    parser_once_f = false;
    return;
  }

  Min(val.x, mnx.min_x);
  Max(val.x, mnx.max_x);

  Min(val.y, mnx.min_y);
  Max(val.y, mnx.max_y);

  Min(val.z, mnx.min_z);
  Max(val.z, mnx.max_z);
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
