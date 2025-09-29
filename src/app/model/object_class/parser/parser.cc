#include "../../../utils/logger.hpp"
#include "../object_class.hpp"

void s21::Object::ObjectParser() {
  std::ifstream obj_file_stream(file_name_);

  if (!obj_file_stream.is_open()) {
    std::cerr << "Ошибка открытия файла: " << file_name_ << std::endl;
    // s21::Logger::Log();
    s21::Logger::Log()->Msg("Ошибка открытия файла : " + file_name_,
                            s21::Logger::MessageType::Warning);
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
