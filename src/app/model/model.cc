#include "model.h"
#include "object_class/object_class.h"
#include <memory>

namespace s21 {

void Model::BuildObject(const std::string &filename) {
  obj_filename_ = filename;

  obj_ = std::make_unique<Object>(obj_filename_);
}

std::vector<float> &s21::Model::GetGLVertices() {
  if (obj_ == nullptr) {
    throw std::runtime_error("obj is not initialized");
  }

  return obj_->GetGLVertices();
}

void Model::TranslateObject() {}
void Model::ScaleObject() {}
} // namespace s21
