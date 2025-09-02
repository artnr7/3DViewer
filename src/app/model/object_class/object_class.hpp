#ifndef OBJECT_HPP_
#define OBJECT_HPP_
#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../model.hpp"
#include "../utils/exception.hpp"

namespace s21 {
#define TOKEN_QTY 3
using coord_t = long double;
using poly_pc_i_t = long int;

typedef struct {
  poly_pc_i_t i;
  coord_t x;
  coord_t y;
  coord_t z;
} Vertice;

// typedef struct {
//   poly_pc_i_t i;
//   coord_t x;
//   coord_t y;
//   coord_t z;
// } Texture;

// typedef struct {
//   poly_pc_i_t i;
//   coord_t x;
//   coord_t y;
//   coord_t z;
// } Normals;

enum ParseStatus {
  Good,
  Invalid,

  NoVertices,
  InvalidVertice,

  NoFaces,
  InvalidFace,

  NotEnoughVertices,
};

enum TokenID { VerticeID, TextureID, NormalID };

typedef struct {
  typedef struct {
    poly_pc_i_t vert_i;
    poly_pc_i_t txr_i;
    poly_pc_i_t norl_i;
  } MapEl;

  poly_pc_i_t i;
  std::vector<MapEl> map;
} Face;

using str_it_t = std::string::iterator;
using vert_it_t = std::vector<s21::Vertice>::iterator;
using face_it_t = std::vector<s21::Face>::iterator;

class Object {
 private:
  std::vector<s21::Vertice> vertices_;
  std::vector<s21::Face> faces_;

  std::string file_name_;
  std::string obj_file_line_;
  str_it_t ofl_it_;

  ParseStatus parse_status_;

  void ObjectParser();

  // VLine
  void ParseVLine(poly_pc_i_t &peaks_i, str_it_t &old_ofl_it);
  void ParseVLineNums(vert_it_t &vert_it);
  void ParseNum(coord_t &coord);
  // FLine
  void ParseFLine(poly_pc_i_t &face_i, str_it_t &old_ofl_it);
  void ParseFMap(poly_pc_i_t &face_i);
  void ParseFMapEls(Face &face);
  void ParseFMapEl(Face::MapEl &map_el);
  void ParseFMapElTok(Face::MapEl &map_el, int &token_i);

 public:
  Object() = default;
  Object(std::string &file_name);
};
}  // namespace s21

#endif