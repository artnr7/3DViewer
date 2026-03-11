#include <iomanip>

#include "object_class.h"

#include "iostream"

namespace s21 {

size_t Object::GetVerticesSize() { return vertices_.maps.size(); }

#define INDEX_SETW_SIZE 5
#define VAR_SETW_SIZE 5

void Object::PrintArray() {
  std::cout << "\n   " << filename_ << "   " << std::endl;
  std::cout << "---------------------------------------- ";
  std::cout << "\n\nv-strings\n";

  int ind = 1;

  for (auto it = vertices_.maps.begin(); it != vertices_.maps.end(); ++it) {
    std::cout << std::setw(INDEX_SETW_SIZE) << ind++ << "  "
              << std::setw(VAR_SETW_SIZE) << it->x << " | "
              << std::setw(VAR_SETW_SIZE) << it->y << " | "
              << std::setw(VAR_SETW_SIZE) << it->z << std::endl;
  }
}

void Object::PrintVertMinMax() {
  auto print = [](const std::string &s, CoordT &mnx) {
    std::cout << s << mnx << std::endl;
  };
  std::cout << std::endl << "MIN MAX =======" << std::endl;

  print("min_x = ", vertices_.mnx.min_x);
  print("max_x = ", vertices_.mnx.max_x);
  print("min_y = ", vertices_.mnx.min_y);
  print("max_y = ", vertices_.mnx.max_y);
  print("min_z = ", vertices_.mnx.min_z);
  print("max_z = ", vertices_.mnx.max_z);

  std::cout << std::endl;
}

void Object::PrintFaces() {
  std::cout << "\n----------------------------------------\n"
            << "\nf-strings\n";

  int ind = 1;

  for (auto it = faces_.begin(); it != faces_.end(); ++it) {
    std::cout << std::setw(INDEX_SETW_SIZE) << ind++ << "  ";
    for (auto m_it = it->begin(); m_it != it->end(); ++m_it) {
      // std::cout << m_it->vert_i << "|" << m_it->txr_i << "|" << m_it->norl_i;
      std::cout << m_it->vert_i << "|" << "|";
      if (m_it + 1 != it->end()) {
        std::cout << " ";
      }
    }

    std::cout << "\n";
  }
}

void Object::PrintEBO() {

  for (auto el : ebo_) {
    std::cout << el << " ";
  }
}

void Object::FillGLverticesOnce() {
  Lg::Log()->Info("Object::" + std::string(__func__));

  for (auto it = faces_.begin(); it != faces_.end(); ++it) {

    for (auto m_it = it->begin(); m_it != it->end(); ++m_it) {
      // TODO: надо проверять что мы не выходим за границы массива
      // индекс, который лежит в faces может не ссылаться на vertice, который
      // вообще сущестукет
      auto el = vertices_.maps[m_it->vert_i - 1];
      // std::cout << "i = " << points_.vertices.vertice_maps[m_it->vert_i -
      // 1].i
      //           << std::endl;
      glvertices_.push_back(el.x);
      glvertices_.push_back(el.y);
      glvertices_.push_back(el.z);
    }
  }
}
void Object::FillGLvertices() {

  for (auto it = vertices_.maps.begin(); it != vertices_.maps.end(); ++it) {
    glvertices_.push_back(it->x);
    glvertices_.push_back(it->y);
    glvertices_.push_back(it->z);
  }
}

void Object::MakeEBO() {
  Lg::Log()->Info("Object::" + std::string(__func__));
  int shift = -1;

  for (auto it = faces_.begin(); it != faces_.end(); ++it) {
    auto m_it = it->begin();

    ebo_.push_back(m_it->vert_i + shift);

    for (; m_it != it->end(); ++m_it) {
      if (m_it == it->begin()) {
        continue;
      }

      for (int i = 0; i < 2; ++i) {
        ebo_.push_back(m_it->vert_i + shift);
      }
    }

    ebo_.push_back(it->begin()->vert_i + shift);
  }
}

} // namespace s21
