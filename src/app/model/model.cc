#include "model.h"
#include "object_class/object_class.h"
#include <memory>

#include "../utils/logger.h"

namespace s21 {

void Model::BuildObject(const std::string &filename) {
  Lg::Log()->Info("Model::" + std::string(__func__));
  obj_filename_ = filename;

  obj_ = std::make_unique<Object>(obj_filename_);
}

std::vector<float> &s21::Model::GetGLVertices() {
  // Lg::Log()->Info("Model::" + std::string(__func__));

  if (obj_ == nullptr) {
    throw std::runtime_error("obj is not initialized");
  }

  return obj_->GetGLVertices();
}
std::vector<float> &s21::Model::GetVBO() {
  // Lg::Log()->Info("Model::" + std::string(__func__));

  if (obj_ == nullptr) {
    throw std::runtime_error("obj is not initialized");
  }

  return obj_->GetVBO();
}

void Model::TranslateObject() {
  Lg::Log()->Info("Model::" + std::string(__func__));
}
void Model::ScaleObject() {
  Lg::Log()->Info("Model::" + std::string(__func__));
}
} // namespace s21
