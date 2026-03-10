#include "object_class.h"
namespace s21 {

void Object::Parser::ParseFLine(IndT &face_i, std::string &obj_file_line) {
  ofl_it_ = obj_file_line.begin();

  if (!IsFLine()) {
    return;
  }
  eofl_it_ = obj_file_line.end();
  ++ofl_it_;
  while (IsSpace()) {
    ++ofl_it_;
  }

  ParseFMap(face_i);
}

void s21::Object::Parser::ParseFMap(IndT &face_i) {
  obj_.faces_.push_back({});

  // while (!IsEndOfLine()) {
  ParseFMapEls(obj_.faces_[face_i++]);
  // }
}

void s21::Object::Parser::ParseFMapEls(std::vector<MapEl> &map) {
  int map_el_i = 0;
  while (!IsEndOfLine()) {
    map.push_back({});
    ParseFMapEl(map[map_el_i]);
    while (*ofl_it_ == ' ' || *ofl_it_ == '\r') {
      ++ofl_it_;
    }
    ++map_el_i;
  }
}

void Object::Parser::ParseFMapEl(MapEl &map_el) {
  int token_i = 0;
  while (token_i < obj_.dim_qty_ && *ofl_it_ != ' ' && !IsEndOfLine()) {
    // надо как-то выше выкидывать
    // try {

    ParseFMapElTok(map_el, token_i);
    // } catch (const s21::InvalidToken &e) {
    //   std::cerr << e.what() << '\n';
    // }
    // std::cout << token_i;
  }
}

void Object::Parser::ParseFMapElTok(MapEl &map_el, int &token_i) {
  if (IsSlash() && IsNextSlash()) {
    ++token_i;
    ofl_it_ += 2;
  } else if (IsSlash()) {
    ofl_it_ += 1;
  }

  IndT *token = nullptr;
  switch (token_i) {
  case TokenID::VerticeID:
    token = &map_el.vert_i;
    break;
  case TokenID::TextureID:
    token = &map_el.txr_i;
    break;
  case TokenID::NormalID:
    token = &map_el.norl_i;
    break;
  }

  std::string num{};
  while (!IsSlash() && !IsSpace() && !IsEndOfLine()) {
    num += *(ofl_it_);
    ++ofl_it_;
  }

  char **endptr{};
  *token = std::strtol(num.c_str(), endptr, 10);

  if (*token == 0) {
    // std::string message = {"Invalid token "};
    // message += std::to_string(token_i);
    // throw s21::InvalidToken{message};
  }
  ++token_i;
}

} // namespace s21
