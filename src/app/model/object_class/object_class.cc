#include "object_class.hpp"
#include <limits>

s21::Object::Object(std::string &file_name)
    : vertices_{}, faces_{}, file_name_{file_name}, obj_file_line_{},
      ofl_it_{} {}

void s21::Object::ObjectParser() {
  std::ifstream obj_file_stream(file_name_);

  if (!obj_file_stream.is_open()) {
    std::cerr << "Ошибка открытия файла: " << file_name_ << std::endl;
    return;
  }

  poly_pc_i_t vert_i = 0;
  poly_pc_i_t face_i = 0;
  parse_status_ = ParseStatus::Good;

  while (std::getline(obj_file_stream, obj_file_line_)) {
    ofl_it_ = obj_file_line_.begin();
    eofl_it_ = obj_file_line_.end();

    // std::cout << obj_file_line_ << std::endl;

    str_it_t old_ofl_it = ofl_it_;
    ParseVLine(vert_i, old_ofl_it);
    ParseFLine(face_i, old_ofl_it);
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

  while (ofl_it_ != eofl_it_) {
    ParseFMapEls(faces_[face_i]);
  }
  ++face_i;
}

void s21::Object::ParseFMapEls(Face &face) {
  int map_el_i = 0;
  while (ofl_it_ != eofl_it_) {
    (face.map).push_back({});
    ParseFMapEl((face.map)[map_el_i]);
    while (*ofl_it_ == ' ' || *ofl_it_ == '\r') {
      ++ofl_it_;
    }
    // std::cout << "---mapel |" << map_el_i << "| ofl_it -|" << *ofl_it_
    //           << "|-\n----------------------\n";
    // std::cout << eofl_it_ - ofl_it_ << "\n";
    ++map_el_i;
  }
}

void s21::Object::ParseFMapEl(MapEl &map_el) {
  int token_i = 0;
  while (token_i < TOKEN_QTY && *ofl_it_ != ' ' && ofl_it_ != eofl_it_) {
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
  while (*ofl_it_ != '/' && *ofl_it_ != ' ' && ofl_it_ != eofl_it_) {
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

void s21::Object::ParseVLine(poly_pc_i_t &vert_i, str_it_t &old_ofl_it) {
  ofl_it_ = old_ofl_it;

  if (!(*ofl_it_ == 'v' && *(ofl_it_ + 1) == ' ')) {
    return;
  }
  ofl_it_ += 3;

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
  // std::cout << *ofl_it_ << std::endl;
  while (*ofl_it_ != ' ' && ofl_it_ != eofl_it_) {
    num += *ofl_it_++;
  }
  char **endptr{};
  coord = std::strtold(num.c_str(), endptr);
  while (*ofl_it_ == ' ') {
    ++ofl_it_;
  }
}

void s21::Object::PrintArray() {

  std::cout << "\n   " << file_name_ << "   "
            << "---------------------------------------- " << "\n\nv-strings\n";

  for (auto it = vertices_.begin(); it != vertices_.end(); ++it) {
    std::cout << (*it).x << " / " << (*it).y << " / " << (*it).z << std::endl;
  }

  std::cout << "\n----------------------------------------\n" << "\nf-strings";

  for (auto it = faces_.begin(); it != faces_.end(); ++it) {
    for (auto m_it = (*it).map.begin(); m_it != (*it).map.end(); ++m_it) {
      std::cout << (*m_it).vert_i << "/" << (*m_it).txr_i << "/"
                << (*m_it).norl_i;
      if (m_it + 1 != (*it).map.end()) {
        std::cout << " ";
      }
    }

    std::cout << "\n";
  }
  std::cout << "\n----------------------------------------\n\n";
}