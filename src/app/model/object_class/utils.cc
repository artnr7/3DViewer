#include <iomanip>

#include "object_class.hpp"

size_t s21::Object::GetVerticesSize() {
  return vertices_.vertices.vertice_maps.size();
}

void s21::Object::SetFileName() { file_name_ = "objs/1.obj"; }

#define INDEX_SETW_SIZE 5
#define VAR_SETW_SIZE 5
void s21::Object::PrintArray() {
  std::cout << "\n   " << file_name_ << "   "
            << "---------------------------------------- " << "\n\nv-strings\n";

  for (auto it = vertices_.vertices.vertice_maps.begin();
       it != vertices_.vertices.vertice_maps.end(); ++it) {
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

// void s21::Object::FillFLines() {}

void s21::Object::FillGLvertices() {
  for (auto it = faces_.face_maps.begin(); it != faces_.face_maps.end(); ++it) {
    for (auto m_it = it->map.begin(); m_it != it->map.end(); ++m_it) {
      glvertices_.push_back(
          vertices_.vertices.vertice_maps[m_it->vert_i - 1].x);
      glvertices_.push_back(
          vertices_.vertices.vertice_maps[m_it->vert_i - 1].y);
      glvertices_.push_back(
          vertices_.vertices.vertice_maps[m_it->vert_i - 1].z);
      // glvertices_.push_back(0);
    }
  }
  // glvertices_.push_back(-0.5f);
  // glvertices_.push_back(-0.5f);
  // glvertices_.push_back(0.0f);

  // glvertices_.push_back(0.5f);
  // glvertices_.push_back(-0.5f);
  // glvertices_.push_back(0.0f);

  // glvertices_.push_back(0.0f);
  // glvertices_.push_back(0.5f);
  // glvertices_.push_back(0.0f);
}