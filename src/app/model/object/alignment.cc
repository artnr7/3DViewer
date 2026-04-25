#include <algorithm>
#include <string>

#include "object.h"

namespace s21 {

void Object::ObjectCentering() {
  Lg::Log()->Info("Object::" + std::string(__func__));

  auto& mnx = vertices_.mnx;

  auto find_center_axis = [&](CoordT min, CoordT max) {
    return min + (max - min) / 2.0f;
  };

  CoordT center_x = find_center_axis(mnx.min_x, mnx.max_x);
  CoordT center_y = find_center_axis(mnx.min_y, mnx.max_y);
  CoordT center_z = find_center_axis(mnx.min_z, mnx.max_z);

  for (auto& it : vertices_.maps) {
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

#define SCALE_MULT 0.50  // { 0.0...1.0 }
void Object::Normalization() {
  Lg::Log()->Info("Object::" + std::string(__func__));

  auto& mnx = vertices_.mnx;

  CoordT diff_x = mnx.max_x - mnx.min_x;
  CoordT diff_y = mnx.max_y - mnx.min_y;
  CoordT diff_z = mnx.max_z - mnx.min_z;

  CoordT dim_max_diff = std::max({diff_x, diff_y, diff_z});

  normalization_scale_ = (SCALE_MULT - (SCALE_MULT * (-1))) / dim_max_diff;

  Lg::Log()->Debug("Object::" + std::string("normalization_scale_ = ") +
                   std::to_string(normalization_scale_));

  for (auto& it : vertices_.maps) {
    it.x *= normalization_scale_;
    it.y *= normalization_scale_;
    it.z *= normalization_scale_;
  }
}
}  // namespace s21
