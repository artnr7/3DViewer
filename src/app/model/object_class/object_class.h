#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>

#include <memory>

#include "../../utils/logger.h"

// #include "../model.hpp"
// #include "../utils/exception.hpp"

#include "types.h"

namespace s21 {

class Object {

private:
  // Variables ----------→
  Vertices vertices_;
  Faces faces_;
  bool init_f_ = true;

  // GL
  std::vector<float> glvertices_;
  std::vector<uint> ebo_;

  // file
  std::string filename_;

  long double normalization_scale_;
  uint8_t dim_qty_ = THREE_DIMENSIONAL;

  // Object methods -------------→
  void ObjectCentering();
  void FindCenterAxis(CoordT &center_axis, CoordT min, CoordT max);
  // Normalization
  void Normalization();

  // AFFINE ---------------------------------------------------→
  class Affine {
  public:
    // void TranslateX(float x);
    // void TranslateY(float y);
    // void TranslateZ(float z);

    // Translate
    void TranslateToX(float);
    void TranslateToY(float);
    void TranslateToZ(float);

    void TranslateOnX(float);
    void TranslateOnY(float);
    void TranslateOnZ(float);

    void Scale(float);

    void RotateToX(float);
    void RotateToY(float);
    void RotateToZ(float);

    void RotateOnX(float);
    void RotateOnY(float);
    void RotateOnZ(float);

    // void SetTranslate(vec4);
    void RTS();
    void RotMat();

    void Multiply();

  private: // VARIABLES
    Object &obj_;
    //
    mat4 mat_trans_{};
    mat4 mat_scale_{};

    using angle = float;

    angle x_{}, y_{}, z_{};

    mat4 mat_rot_{};

    mat4 mat_rot_x_{};
    mat4 mat_rot_y_{};
    mat4 mat_rot_z_{};

    mat4 rts_{};

  public:
    Affine(Object &obj) : obj_(obj) {}
  };

  class Parser {
    enum class ParseStatus : uint8_t {
      None,

      Good,
      Invalid,

      NoVertices,
      InvalidVertice,

      NoFaces,
      InvalidFace,

      NotEnoughVertices,
    };

    using StrIter = std::string::iterator;
    using VertIter = VertMaps::iterator;
    using FaceIter = Faces::iterator;

  private:
    Object &obj_;
    //
    StrIter ofl_it_{};
    StrIter eofl_it_{};
    ParseStatus parse_status_ = ParseStatus::None;
    bool parser_once_f_ = true;

  public:
    Parser() = delete;
    Parser(Object &obj) : obj_(obj) {}

    void Parse();

  private:
    // VLine ----------------------------------------------------→
    void ParseVLine(IndT &vert_i, std::string &obj_file_line);
    void ParseVLineNums(VertIter &v_it);
    void ParseNum(CoordT &coord);
    void FindMinMax(VertIter &v_it);

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
  void PrintVertMinMax();
  void PrintArray();
  void PrintFaces();
  void PrintEBO();
  void PrintGLVertices();

  void MakeEBO();
};
} // namespace s21

#endif
