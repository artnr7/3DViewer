#include "model.hpp"

s21::Model *s21::Model::instance = nullptr;

s21::Model::Model(std::string &obj_filename) {

  obj_ = new s21::Object(obj_filename);
};

std::vector<float> &s21::Model::GetGLVertices() {
  if (!obj_) {
    throw std::runtime_error("obj is not initialized");
  }
  obj_->PrintArray();
  return obj_->GetGLVertices();
};

// void s21::Model::SetObjFilename(std::string &obj_filename) noexcept {
// obj_filename_ = obj_filename;
// }