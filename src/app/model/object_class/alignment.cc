#include <algorithm>
#include <iostream>
#include <string>

#include "object_class.h"

void s21::Object::ObjectCentering() {
  Lg::Log()->Info("Object::" + std::string(__func__));

  CoordT center_x = 0;
  CoordT center_y = 0;
  CoordT center_z = 0;

  auto &mnx = vertices_.mnx;

  FindCenterAxis(center_x, mnx.min_x, mnx.max_x);
  FindCenterAxis(center_y, mnx.min_y, mnx.max_y);
  FindCenterAxis(center_z, mnx.min_z, mnx.max_z);

  for (auto &it : vertices_.maps) {
    it.x -= center_x;
    it.y -= center_y;
    it.z -= center_z;
  }

  Lg::Log()->Debug("Object::" + std::string("center_x = ") +
                   std::to_string(center_x));

  Lg::Log()->Debug("Object::" + std::string("center_y = ") +
                   std::to_string(center_y));

  Lg::Log()->Debug("Object::" + std::string("center_y = ") +
                   std::to_string(center_y));
}

void s21::Object::FindCenterAxis(CoordT &center_axis, CoordT min, CoordT max) {
  center_axis = min + (max - min) / 2.0f;
}

#define SCALE_MULT 0.50 // { 0.0...1.0 }
void s21::Object::Normalization() {
  Lg::Log()->Info("Object::" + std::string(__func__));

  auto &mnx = vertices_.mnx;

  CoordT diff_x = mnx.max_x - mnx.min_x;
  CoordT diff_y = mnx.max_y - mnx.min_y;
  CoordT diff_z = mnx.max_z - mnx.min_z;

  CoordT dim_max_diff = std::max({diff_x, diff_y, diff_z});

  normalization_scale_ = (SCALE_MULT - (SCALE_MULT * (-1))) / dim_max_diff;

  Lg::Log()->Debug("Object::" + std::string("normalization_scale_ = ") +
                   std::to_string(normalization_scale_));

  for (auto &it : vertices_.maps) {
    it.x *= normalization_scale_;
    it.y *= normalization_scale_;
    it.z *= normalization_scale_;
  }
}
