#include <iomanip>

#include "object_class.h"

#include "iostream"

namespace s21 {

size_t Object::GetVerticesSize() {
  return points_.vertices.vertice_maps.size();
}

#define INDEX_SETW_SIZE 5
#define VAR_SETW_SIZE 5
void Object::PrintArray() {
  std::cout << "\n   " << filename_ << "   "
            << "---------------------------------------- " << "\n\nv-strings\n";

  for (auto it = points_.vertices.vertice_maps.begin();
       it != points_.vertices.vertice_maps.end(); ++it) {
    std::cout << std::setw(INDEX_SETW_SIZE) << it->i << "  "
              << std::setw(VAR_SETW_SIZE) << it->x << " | "
              << std::setw(VAR_SETW_SIZE) << it->y << " | "
              << std::setw(VAR_SETW_SIZE) << it->z << std::endl;
  }

  std::cout << "\n----------------------------------------\n"
            << "\nf-strings\n";

  for (auto it = faces_.face_maps.begin(); it != faces_.face_maps.end(); ++it) {
    std::cout << std::setw(INDEX_SETW_SIZE) << it->i << "  ";
    for (auto m_it = it->map.begin(); m_it != it->map.end(); ++m_it) {
      std::cout << m_it->vert_i << "|" << m_it->txr_i << "|" << m_it->norl_i;
      if (m_it + 1 != it->map.end()) {
        std::cout << " ";
      }
    }

    std::cout << "\n";
  }

  std::cout << "MIN MAX =======\n";
  std::cout << "min_x = " << points_.vertices.min_x << std::endl;
  std::cout << "max_x = " << points_.vertices.max_x << std::endl;
  std::cout << "min_y = " << points_.vertices.min_y << std::endl;
  std::cout << "max_y = " << points_.vertices.max_y << std::endl;
  std::cout << "min_z = " << points_.vertices.min_z << std::endl;
  std::cout << "max_z = " << points_.vertices.max_z << std::endl;
  std::cout << "\n";

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

void Object::PrintEBO() {

  for (auto el : ebo_) {
    std::cout << el << " ";
  }
}

// void s21::Object::FillFLines() {}

void Object::FillGLverticesOnce() {
  Lg::Log()->Info("Object::" + std::string(__func__));

  for (auto it = faces_.face_maps.begin(); it != faces_.face_maps.end(); ++it) {

    for (auto m_it = it->map.begin(); m_it != it->map.end(); ++m_it) {
      // TODO: надо проверять что мы не выходим за границы массива
      // индекс, который лежит в faces может не ссылаться на vertice, который
      // вообще сущестукет
      auto el = points_.vertices.vertice_maps[m_it->vert_i - 1];
      glvertices_.push_back(el.x);
      glvertices_.push_back(el.y);
      glvertices_.push_back(el.z);
    }
  }
}

void Object::MakeEBO() {
  Lg::Log()->Info("Object::" + std::string(__func__));

  for (auto it = faces_.face_maps.begin(); it != faces_.face_maps.end(); ++it) {
    for (auto m_it = it->map.begin(); m_it != it->map.end(); ++m_it) {
      for (int i = 0; i < 2; ++i) {
        if (i && (m_it == it->map.begin() || m_it == it->map.end() - 1)) {
          continue;
        }
        ebo_.push_back(m_it->vert_i - 1);
      }
    }
  }
}

} // namespace s21
