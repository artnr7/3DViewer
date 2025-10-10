#include <algorithm>
#include <iostream>

#include "object_class.hpp"

void s21::Object::ObjectCentering() {
  CoordT center_x = 0;
  CoordT center_y = 0;
  CoordT center_z = 0;

  auto &vert = vertices_.vertices;

  FindCenterAxis(center_x, vert.min_x, vert.max_x);
  FindCenterAxis(center_y, vert.min_y, vert.max_y);
  FindCenterAxis(center_z, vert.min_z, vert.max_z);

  
  for (auto &it : vert.vertice_maps) {
    it.x -= center_x;
    it.y -= center_y;
    it.z -= center_z;
  }
  std::cout << "center_ = x" << center_x << std::endl;
  std::cout << "center_ = y" << center_x << std::endl;
  std::cout << "center_ = z" << center_x << std::endl;
}

void s21::Object::FindCenterAxis(CoordT &center_axis, CoordT min, CoordT max) {
  center_axis = min + (max - min) / 2.0f;
}

#define SCALE_MULT 0.50  // { 0.0...1.0 }
void s21::Object::Normalization() {
  auto &vert = vertices_.vertices;
  CoordT diff_x = vert.max_x - vert.min_x;
  CoordT diff_y = vert.max_y - vert.min_y;
  CoordT diff_z = vert.max_z - vert.min_z;

  CoordT dim_max_diff = std::max({diff_x, diff_y, diff_z});
  std::cout << "dim = " << dim_max_diff << std::endl;

  scale_ = (SCALE_MULT - (SCALE_MULT * (-1))) / dim_max_diff;
  std::cout << "scale = " << scale_ << std::endl;

  for (auto &it : vert.vertice_maps) {
    it.x *= scale_;
    it.y *= scale_;
    it.z *= scale_;
  }
}