#include "model.h"
#include "object_class/object_class.h"
#include <memory>

#include "../utils/logger.h"

namespace s21 {

void Model::BuildObject(const std::string &filename) {
  Lg::Log()->Info("Model::" + std::string(__func__));

  if (obj_.get() != nullptr) {
    obj_.reset();
  }

  obj_filename_ = filename;

  obj_ = std::make_unique<Object>(obj_filename_);
}

std::vector<float> &Model::GetGLVertices() {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  if (obj_ == nullptr) {
    throw std::runtime_error("obj is not initialized");
  }

  return obj_->GetGLVertices();
}
std::vector<uint> &Model::GetEBO() {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  if (obj_ == nullptr) {
    throw std::runtime_error("obj is not initialized");
  }

  return obj_->GetEBO();
}
void Model::TranslateToX(float x) {
  Lg::Log()->Info("Model::" + std::string(__func__));
}
void Model::TranslateToY(float x) {
  Lg::Log()->Info("Model::" + std::string(__func__));
}
void Model::TranslateToZ(float x) {
  Lg::Log()->Info("Model::" + std::string(__func__));
}

void Model::TranslateOnX(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));
  obj_->a_.TranslateX(x);
}

void Model::TranslateOnY(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));
  obj_->a_.TranslateY(x);
}

void Model::TranslateOnZ(float x) {
  Lg::Log()->Info("Model::" + std::string(__func__));
}

void Model::ScaleObject() {
  Lg::Log()->Info("Model::" + std::string(__func__));
}
} // namespace s21
