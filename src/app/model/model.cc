#include "model.hpp"

s21::Model *s21::Model::instance = nullptr;

s21::Model::Model() {
  std::string file_name = "../objs/cube.obj";
  // std::string file_name = "../objs/1 copy.obj.obj";
  obj_ = new s21::Object(file_name);
};