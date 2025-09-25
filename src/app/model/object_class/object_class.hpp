#ifndef OBJECT_HPP_
#define OBJECT_HPP_
#include <QtOpenGL>
#include <cctype>
#include <fstream>
#include <iostream>

// #include "../model.hpp"
// #include "../utils/exception.hpp"

#include "types.hpp"

namespace s21 {

class Object {
  using StrIter = std::string::iterator;
  using VertIter = std::vector<Vertices::Vertices::VerticeMap>::iterator;
  using FaceIter = std::vector<Faces::FaceMap>::iterator;

 private:
  Vertices vertices_;
  Faces faces_;

  // std::vector<s21::VerticeMap> vertices_;
  // std::vector<s21::FaceMap> faces_;

  std::vector<float> glvertices_;

  std::string file_name_;
  StrIter ofl_it_;
  StrIter eofl_it_;

  ParseStatus parse_status_;

  void ObjectParser();

  size_t GetVerticesSize();

  void SetFileName();
  // VLine
  void ParseVLine(PolyPcInT &vert_i, std::string &obj_file_line);
  void ParseVLineNums(VertIter &vert_it);
  void ParseNum(CoordT &coord);
  void FindMinMax(VertIter &vert_it);

  // FLine
  void ParseFLine(PolyPcInT &face_i, std::string &obj_file_line);
  void ParseFMap(PolyPcInT &face_i);
  void ParseFMapEls(std::vector<Faces::FaceMap::MapEl> &map);
  void ParseFMapEl(Faces::FaceMap::MapEl &map_el);
  void ParseFMapElTok(Faces::FaceMap::MapEl &map_el, int &token_i);

  // Parser Utils
  bool IsFLine();
  bool IsVLine();

  bool IsEndOfLine();
  bool IsSlash();
  bool IsNextSlash();
  bool IsSpace();

  // Object methods
  void ObjectCentering();
  void FindCenterAxis(CoordT &center_axis, CoordT min, CoordT max);

 public:
  Object() = delete;
  Object(const std::string &file_name);

  std::vector<float> &GetGLVertices() { return glvertices_; }

  // utils
  void PrintArray();
  void FillGLvertices();
};
}  // namespace s21

#endif