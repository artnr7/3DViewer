#ifndef OBJECT_HPP_
#define OBJECT_HPP_
#include "../model.hpp"
#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {
using coord_t = long double;
using poly_pc_i_t = long int;

typedef struct {
  poly_pc_i_t i;
  coord_t x;
  coord_t y;
  coord_t z;
} Vertice;

typedef

using str_it_t = std::string::iterator;
using vert_it_t = std::vector<s21::Vertice>::iterator;

class Object {
private:
  std::vector<s21::Vertice> vertices_;
  std::vector<long double> surface_;
  std::string file_name_;

  void ObjectParser();


  // VLine
  void ParseVLine(std::string &obj_file_line, poly_pc_i_t &peaks_i);
  void ParseVLineNums(vert_it_t &vert_it, str_it_t &ofl_it);
  void ParseNum(coord_t &coord, str_it_t &ofl_it);
  // FLine
  void ParseFLine()

public:
  Object() = default;
  Object(std::string &file_name);
};
} // namespace s21

#endif