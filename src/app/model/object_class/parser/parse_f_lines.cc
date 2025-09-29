#include "../object_class.hpp"

void s21::Object::ParseFLine(PolyPcInT &face_i, std::string &obj_file_line) {
  // std::cout << obj_file_line << std::endl;

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

void s21::Object::ParseFMap(PolyPcInT &face_i) {
  faces_.face_maps.push_back({});
  faces_.face_maps[face_i].i = (face_i + 1);
  faces_.face_maps[face_i].map = {};

  while (!IsEndOfLine()) {
    ParseFMapEls(faces_.face_maps[face_i].map);
  }
  ++face_i;
}

void s21::Object::ParseFMapEls(std::vector<Faces::FaceMap::MapEl> &map) {
  int map_el_i = 0;
  while (!IsEndOfLine()) {
    map.push_back({});
    ParseFMapEl(map[map_el_i]);
    while (*ofl_it_ == ' ' || *ofl_it_ == '\r') {
      ++ofl_it_;
    }
    // std::cout << "---mapel |" << map_el_i << "| ofl_it -|" << *ofl_it_
    //           << "|-\n----------------------\n";
    // std::cout << eofl_it_ - ofl_it_ << "\n";
    ++map_el_i;
  }
}

void s21::Object::ParseFMapEl(Faces::FaceMap::MapEl &map_el) {
  int token_i = 0;
  while (token_i < DIMENSION_QTY && *ofl_it_ != ' ' && !IsEndOfLine()) {
    // надо как-то выше выкидывать
    // try {

    ParseFMapElTok(map_el, token_i);
    // } catch (const s21::InvalidToken &e) {
    //   std::cerr << e.what() << '\n';
    // }
    // std::cout << token_i;
  }
}

void s21::Object::ParseFMapElTok(Faces::FaceMap::MapEl &map_el, int &token_i) {
  if (IsSlash() && IsNextSlash()) {
    ++token_i;
    ofl_it_ += 2;
  } else if (IsSlash()) {
    ofl_it_ += 1;
  }

  PolyPcInT *token = nullptr;
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
  // std::cout << "---token |" << *token << "| ofl_it |" << *ofl_it_
  //           << "| token_i |" << token_i << "| \n";
}