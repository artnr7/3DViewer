#include <algorithm>
#include <iostream>
#include <string>

#include "../../utils/logger.hpp"
#include "object_class.hpp"

void s21::Object::ObjectCentering() {
  s21::Logger::Log()->Msg(std::string(__func__) + " – Centering...",
                          s21::Logger::MessageType::Process);
  CoordT center_x = 0;
  CoordT center_y = 0;
  CoordT center_z = 0;

  auto &vert = vertices_.vertices;

  FindCenterAxis(center_x, vert.min_x, vert.max_x);
  FindCenterAxis(center_y, vert.min_y, vert.max_y);
  FindCenterAxis(center_z, vert.min_z, vert.max_z);

  s21::Logger::Log()->Msg("center_x = " + std::to_string(center_x),
                          s21::Logger::MessageType::Variable);
  s21::Logger::Log()->Msg("center_y = " + std::to_string(center_y),
                          s21::Logger::MessageType::Variable);
  s21::Logger::Log()->Msg("center_y = " + std::to_string(center_z),
                          s21::Logger::MessageType::Variable);

  for (auto &it : vert.vertice_maps) {
    it.x -= center_x;
    it.y -= center_y;
    it.z -= center_z;
  }
}

void s21::Object::FindCenterAxis(CoordT &center_axis, CoordT min, CoordT max) {
  center_axis = min + (max - min) / 2.0f;
}

#define SCALE_MULT 0.30  // { 0.0...1.0 }
void s21::Object::Normalization() {
  s21::Logger::Log()->Msg(std::string(__func__) + " – Normalization...",
                          s21::Logger::MessageType::Process);

  auto &vert = vertices_.vertices;
  CoordT diff_x = vert.max_x - vert.min_x;
  CoordT diff_y = vert.max_y - vert.min_y;
  CoordT diff_z = vert.max_z - vert.min_z;

  CoordT dim_max_diff = std::max({diff_x, diff_y, diff_z});
  std::cout << "dim = " << dim_max_diff << std::endl;

  scale_ = (SCALE_MULT - (SCALE_MULT * (-1))) / dim_max_diff;
  s21::Logger::Log()->Msg("scale = " + std::to_string(scale_));

  for (auto &it : vert.vertice_maps) {
    it.x *= scale_;
    it.y *= scale_;
    it.z *= scale_;
  }
}