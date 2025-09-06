#include "object_class.hpp"

s21::Object::Object(std::string &file_name)
    : vertices_{}, faces_{}, file_name_{file_name}, obj_file_line_{},
      ofl_it_{} {}

void s21::Object::ObjectParser() {
  std::ifstream obj_file_stream(file_name_);

  if (!obj_file_stream.is_open()) {
    std::cerr << "Ошибка открытия файла: " << file_name_ << std::endl;
    return;
  }

  poly_pc_i_t vert_i = 0, face_i = 0;
  parse_status_ = ParseStatus::Good;

  int i = 0;
  while (std::getline(obj_file_stream, obj_file_line_)) {
    std::cout << obj_file_line_ << std::endl;
    ofl_it_ = obj_file_line_.begin();
    str_it_t old_ofl_it = ofl_it_;
    ParseVLine(vert_i, old_ofl_it);
    ParseFLine(face_i, old_ofl_it);
    std::cout << i++ << std::endl;
  }
}

void s21::Object::ParseFLine(poly_pc_i_t &face_i, str_it_t &old_ofl_it) {
  ofl_it_ = old_ofl_it;

  if (*ofl_it_ != 'f') {
    return;
  }

  ofl_it_ += 2;
  ParseFMap(face_i);
}

void s21::Object::ParseFMap(poly_pc_i_t &face_i) {
  faces_.push_back({});
  faces_[face_i].i = face_i;
  faces_[face_i].map = {};

  while (*ofl_it_ != '\n') {
    ParseFMapEls(faces_[face_i]);
  }
  ++face_i;
}

void s21::Object::ParseFMapEls(Face &face) {
  int map_el_i = 0;
  while (*ofl_it_ != '\n') {

    (face.map).push_back({});
    ParseFMapEl((face.map)[map_el_i]);
    if (*ofl_it_ == ' ') {
      ++ofl_it_;
    }
    std::cout << "\n\t\t\tmapel----" << map_el_i << "  |" << *ofl_it_
              << "|\n\n";
    ++map_el_i;
  }
}

void s21::Object::ParseFMapEl(MapEl &map_el) {
  int token_i = 0;
  while (token_i < TOKEN_QTY && *ofl_it_ != ' ' && *ofl_it_ != '\n') {
    // надо как-то выше выкидывать
    // try {

    ParseFMapElTok(map_el, token_i);
    // } catch (const s21::InvalidToken &e) {
    //   std::cerr << e.what() << '\n';
    // }
    // std::cout << token_i;
  }
}

void s21::Object::ParseFMapElTok(MapEl &map_el, int &token_i) {
  if (*ofl_it_ == '/' && *(ofl_it_ + 1) == '/') {
    ++token_i;
    ofl_it_ += 2;
  } else if (*ofl_it_ == '/') {
    ofl_it_ += 1;
  }

  poly_pc_i_t *token = nullptr;
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
  while (*ofl_it_ != '/' && *ofl_it_ != ' ' && *ofl_it_ != '\n') {
    num += *(ofl_it_++);
  }
  char **endptr{};
  *token = std::strtol(num.c_str(), endptr, 10);
  std::cout << "---  " << *token << "   |" << *ofl_it_ << "|           "
            << token_i << std::endl;

  if (*token == 0) {
    std::string message = {"Invalid token "};
    message += std::to_string(token_i);
    // throw s21::InvalidToken{message};
  }
  ++token_i;
}

void s21::Object::ParseVLine(poly_pc_i_t &vert_i, str_it_t &old_ofl_it) {
  ofl_it_ = old_ofl_it;

  if (*ofl_it_++ != 'v') {
    return;
  }

  vertices_.push_back({0, 0, 0, 0});

  vert_it_t vert_it = vertices_.begin() + vert_i;
  vert_it->i = vert_i++;

  ParseVLineNums(vert_it);
}

void s21::Object::ParseVLineNums(vert_it_t &vert_it) {
  ParseNum(vert_it->x);
  ParseNum(vert_it->y);
  ParseNum(vert_it->z);
}

void s21::Object::ParseNum(coord_t &coord) {
  std::string num{};
  while (*ofl_it_ != ' ' && *ofl_it_ != '\n') {
    num += *ofl_it_++;
  }
  char **endptr{};
  coord = std::strtold(num.c_str(), endptr);
}

void s21::Object::PrintArray() {
  for (auto it = vertices_.begin(); it < vertices_.end(); ++it) {
    std::cout << (*it).x << (*it).y << (*it).z << std::endl;
  }
  std::cout << "-----------" << file_name_ << std::endl;
}