#include <string>

#include "../../utils/logger.hpp"
#include "object_class.hpp"

s21::Object::Object(const std::string &obj_filename)
    : vertices_{},
      faces_{},
      glvertices_{},
      file_name_{obj_filename},
      ofl_it_{},
      eofl_it_(),
      scale_(),
      m_model_() {
  s21::Logger::Log()->Msg(std::string(__func__) + " – Loading Model...",
                          s21::Logger::MessageType::Process);
  ObjectParser();
  FillGLvertices();
}