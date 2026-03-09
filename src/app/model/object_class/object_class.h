#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <cctype>
#include <cstdint>
#include <fstream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

#include <memory>

#include "../../utils/logger.h"

// #include "../model.hpp"
// #include "../utils/exception.hpp"

#include "types.h"

namespace s21 {

class Object {
  using StrIter = std::string::iterator;

private:
  // Variables ----------→
  Vertices vertices_;
  Faces faces_;

  // GL
  std::vector<float> glvertices_;
  std::vector<uint> ebo_;

  // file
  std::string filename_;

  long double normalization_scale_;
  size_t GetVerticesSize();

  // Object methods -------------→
  void ObjectCentering();
  void FindCenterAxis(CoordT &center_axis, CoordT min, CoordT max);
  // Normalization
  void Normalization();

  // AFFINE ---------------------------------------------------→
  class Affine {
  public:
    void TranslateX(float x);
    void TranslateY(float y);
    void TranslateZ(float z);

    void RotateX();

  private:
    Object &obj_;

  private:
    // glm::mat4 model_ = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f));
    // glm::mat4 model_ = glm::translate(glm::mat4(1.0f),glm::vec3(0.5f));
    void Translate(const uint8_t shift, float arg);

  public:
    Affine(Object &obj) : obj_(obj) {}
  };

  // PARSER ---------------------------------------------------→
  class Parser {
    enum class ParseStatus : uint8_t {
      Good,
      Invalid,

      NoVertices,
      InvalidVertice,

      NoFaces,
      InvalidFace,

      NotEnoughVertices,
    };

    using VertIter = std::vector<vert_map>::iterator;
    using FaceIter = std::vector<FaceMap>::iterator;

  private:
    Object &obj_;

    StrIter ofl_it_{};
    StrIter eofl_it_{};
    ParseStatus parse_status_ = ParseStatus::Good;
    bool parser_once_f = true;

  public:
    Parser() = delete;
    Parser(Object &obj) : obj_(obj) {}

    void Parse();

  private:
    // VLine ----------------------------------------------------→
    void ParseVLine(IndT &vert_i, std::string &obj_file_line);
    void ParseVLineNums(VertIter &vert_it);
    void ParseNum(CoordT &coord);
    void FindMinMax(VertIter &vert_it);
    void Min(CoordT coord, CoordT &min);
    void Max(CoordT coord, CoordT &max);

    // FLine
    void ParseFLine(IndT &face_i, std::string &obj_file_line);
    void ParseFMap(IndT &face_i);
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
  };

  Parser p_;

public:
  Affine a_;
  // Constructors --------------------→
  Object() = delete;
  Object(const std::string &file_name);

  std::vector<float> &GetGLVertices() { return glvertices_; }
  std::vector<uint> &GetEBO() { return ebo_; }

  // utils
  void PrintArray();
  void PrintFaces();
  void PrintEBO();
  void FillGLverticesOnce();
  void FillGLvertices();
  void MakeEBO();
};
} // namespace s21

#endif
