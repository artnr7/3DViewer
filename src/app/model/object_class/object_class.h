#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <cctype>
#include <fstream>
#include <iostream>

#include <memory>

#include "../../utils/logger.h"

// #include "../model.hpp"
// #include "../utils/exception.hpp"

#include "types.h"

namespace s21 {

class Object {
  using StrIter = std::string::iterator;
  using VertIter = std::vector<VerticeMap>::iterator;
  using FaceIter = std::vector<FaceMap>::iterator;

private:
  // Variables ----------→
  Points points_;
  Faces faces_;

  // GL
  std::vector<float> glvertices_;
  std::vector<uint> ebo_;

  // file
  std::string filename_;
  StrIter ofl_it_;
  StrIter eofl_it_;

  ParseStatus parse_status_;

  long double scale_;

  // Methods ------------→
  void ObjectParser();

  size_t GetVerticesSize();
  // VLine ----------------------------------------------------→
  void ParseVLine(PolyPcInT &vert_i, std::string &obj_file_line);
  void ParseVLineNums(VertIter &vert_it);
  void ParseNum(CoordT &coord);
  void FindMinMax(VertIter &vert_it);

  // FLine
  void ParseFLine(PolyPcInT &face_i, std::string &obj_file_line);
  void ParseFMap(PolyPcInT &face_i);
  void ParseFMapEls(std::vector<MapEl> &map);
  void ParseFMapEl(MapEl &map_el);
  void ParseFMapElTok(MapEl &map_el, int &token_i);

  // Parser Utils --------------→
  bool IsFLine();
  bool IsVLine();

  bool IsEndOfLine();
  bool IsSlash();
  bool IsNextSlash();
  bool IsSpace();

  // Object methods -------------→
  void ObjectCentering();
  void FindCenterAxis(CoordT &center_axis, CoordT min, CoordT max);
  // Normalization
  void Normalization();

public:
  // Constructors --------------------→
  Object() = delete;
  Object(const std::string &file_name);

  std::vector<float> &GetGLVertices() { return glvertices_; }
  std::vector<uint> &GetEBO() { return ebo_; }

  // utils
  void PrintArray();
  void PrintEBO();
  void FillGLverticesOnce();
  void MakeEBO();
};
} // namespace s21

#endif
