#include "object_class.hpp"

void s21::Object::ObjectCentering() {

  CoordT center_x = 0;
  CoordT center_y = 0;
  CoordT center_z = 0;

  auto vert = vertices_.vertices;

  FindCenterAxis(center_x, vert.min_x, vert.max_x);
  FindCenterAxis(center_y, vert.min_y, vert.max_y);
  FindCenterAxis(center_z, vert.min_z, vert.max_z);

  for (auto it = vertices_.vertices.vertice_maps.begin();
       it != vertices_.vertices.vertice_maps.end(); ++it) {
    it->x -= center_x;
    it->y -= center_y;
    it->z -= center_z;
  }
}

void s21::Object::FindCenterAxis(CoordT &center_axis, CoordT min, CoordT max) {
  center_axis = min + (max - min) / 2.0f;
}