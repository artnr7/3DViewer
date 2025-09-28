#include <iomanip>
#include <string>

#include "../../utils/logger.hpp"
#include "object_class.hpp"

size_t s21::Object::GetVerticesSize() {
  return vertices_.vertices.vertice_maps.size();
}

#define INDEX_SETW_SIZE 5
#define VAR_SETW_SIZE 5
void s21::Object::PrintArray() {
  s21::Logger::Log()->Msg(
      std::string(__func__) + " – Logging V- and F- strings...",
      s21::Logger::MessageType::Process);
  auto &vert = vertices_.vertices;
  s21::Logger::Log()->Msg("\n--------------------------\n");
  s21::Logger::Log()->Msg("v-strings", s21::Logger::MessageType::Variable);

  for (auto &it : vert.vertice_maps) {
    s21::Logger::Log()->Msg(std::to_string(it.i) + "\t" + std::to_string(it.x) +
                            " | " + std::to_string(it.y) + " | " +
                            std::to_string(it.z));
  }

  s21::Logger::Log()->Msg("\n--------------------------\n");
  s21::Logger::Log()->Msg("f-strings", s21::Logger::MessageType::Variable);

  for (auto &it : faces_.face_maps) {
    s21::Logger::Log()->Msg(std::to_string(it.i) + " -------");
    for (auto m_it = it.map.begin(); m_it != it.map.end(); ++m_it) {
      s21::Logger::Log()->Msg(std::to_string(m_it->vert_i) + "|" +
                              std::to_string(m_it->txr_i) + "|" +
                              std::to_string(m_it->norl_i));
    }
  }

  s21::Logger::Log()->Msg("\n-------------------\nmin max");
  s21::Logger::Log()->Msg("min_x = " + std::to_string(vert.min_x));
  s21::Logger::Log()->Msg("max_x = " + std::to_string(vert.max_x));
  s21::Logger::Log()->Msg("min_y = " + std::to_string(vert.min_y));
  s21::Logger::Log()->Msg("max_y = " + std::to_string(vert.max_y));
  s21::Logger::Log()->Msg("min_z = " + std::to_string(vert.min_z));
  s21::Logger::Log()->Msg("max_z = " + std::to_string(vert.max_z));

  // std::cout << "\n----------------------------------------\n"
  //           << "\nglvertices\n";

  // int i = 0;
  // for (auto it = glvertices_.begin(); it != glvertices_.end(); ++it, ++i) {
  //   std::cout << *it;
  //   if (i % 3 == 0 || i % 3 == 1) {
  //     std::cout << "/";
  //   }

  //   if (i % 3 == 2) {
  //     std::cout << "  |  ";
  //   }

  //   if (i % 9 == 8) {
  //     std::cout << "\n";
  //   }
  // }
  // std::cout << "\n----------------------------------------\n\n";
}

void s21::Object::FillGLvertices() {
  s21::Logger::Log()->Msg(std::string(__func__) + " – FillGLVertices...",
                          s21::Logger::MessageType::Process);

  auto &vert = vertices_.vertices;

  for (auto &it : faces_.face_maps) {
    for (auto &m_it : it.map) {
      glvertices_.push_back(vert.vertice_maps[m_it.vert_i - 1].x);
      glvertices_.push_back(vert.vertice_maps[m_it.vert_i - 1].y);
      glvertices_.push_back(vert.vertice_maps[m_it.vert_i - 1].z);
    }
  }
}