#ifndef OBJECT_HPP_
#define OBJECT_HPP_
#include <QtOpenGL>
#include <cctype>
#include <fstream>
#include <iostream>

// #include "../model.hpp"
// #include "../utils/exception.hpp"

#include <qmatrix4x4.h>

#include <QtOpenGL>

#include "types.hpp"

namespace s21 {

class Object {
  using StrIter = std::string::iterator;
  using VertIter = std::vector<Vertices::Vertices::VerticeMap>::iterator;
  using FaceIter = std::vector<Faces::FaceMap>::iterator;

 private:
  // Variables ----------→
  Vertices vertices_;
  Faces faces_;

  std::vector<float> glvertices_;

  std::string file_name_;
  StrIter ofl_it_;
  StrIter eofl_it_;

  ParseStatus parse_status_;

  long double scale_;

  // Matrices
  QMatrix4x4 m_model_;

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
  void ParseFMapEls(std::vector<Faces::FaceMap::MapEl> &map);
  void ParseFMapEl(Faces::FaceMap::MapEl &map_el);
  void ParseFMapElTok(Faces::FaceMap::MapEl &map_el, int &token_i);

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
  // Matrix methods Model ----------→
  void MatrixTranslate(QVector3D &vec);
  void MatrixRotate(float &angle, QVector3D &vec);
  void MatrixScale(float &mult);

  void SetToIdentityIfNot(QMatrix4x4 &mtx);

  // Constructors --------------------→
  Object() = delete;
  Object(const std::string &file_name);

  // Getters --------------→
  std::vector<float> *GetGLVertices() { return &glvertices_; }
  std::vector<Vertices::Vertices::VerticeMap> &GetVertices() {
    return vertices_.vertices.vertice_maps;
  }
  QMatrix4x4 &GetModelMatrix() { return m_model_; }

  // Utils ----------→
  void PrintArray();
  void FillGLvertices();
};
}  // namespace s21

#endif