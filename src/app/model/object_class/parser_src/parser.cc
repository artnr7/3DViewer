// #include "logger.h"
#include "object_class.h"

namespace s21 {

void Object::Parser::Parse() {
  Lg::Log()->Info("Object::" + std::string(__func__));

  std::ifstream obj_file_stream(obj_.filename_);

  if (!obj_file_stream.is_open()) {
    std::cerr << "Ошибка открытия файла: " << obj_.filename_ << std::endl;
    s21::Lg::Log()->Err("Ошибка открытия файла : " + obj_.filename_);
    return;
  }

  PolyPcInT vert_i = 0;
  PolyPcInT face_i = 0;
  parse_status_ = ParseStatus::Good;

  std::string obj_file_line{};

  while (std::getline(obj_file_stream, obj_file_line)) {
    ParseVLine(vert_i, obj_file_line);
  }

  obj_file_stream.clear();
  obj_file_stream.seekg(0);

  while (std::getline(obj_file_stream, obj_file_line)) {
    ParseFLine(face_i, obj_file_line);
  }
}

} // namespace s21
