#ifndef PARSER_H_
#define PARSER_H_

#include "../../api/primitives.h"
#include "../types.h"

namespace s21 {
class Object;

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
  Object& obj_;
  //
  StrIter ofl_it_{};
  StrIter eofl_it_{};
  ParseStatus parse_status_ = ParseStatus::None;
  bool parser_once_f_ = true;

 public:
  Parser() = delete;
  explicit Parser(Object& obj) : obj_(obj) {}

  void Parse();

 private:
  // VLine
  void ParseVLine(IndT& vert_i, std::string& obj_file_line);
  void ParseVLineNums(VertIter& v_it);
  void ParseNum(CoordT& coord);
  void FindMinMax(VertIter& v_it);

  // FLine
  void ParseFLine(IndT& face_i, std::string& obj_file_line);
  void ParseFMap(IndT& face_i);
  void ParseFMapEls(std::vector<MapEl>& map);
  void ParseFMapEl(MapEl& map_el);
  void ParseFMapElTok(MapEl& map_el, int& token_i);

  // Parser Utils --------------→
  bool IsFLine();
  bool IsVLine();

  bool IsEndOfLine();
  bool IsSlash();
  bool IsNextSlash();
  bool IsSpace();
};
}  // namespace s21
#endif
