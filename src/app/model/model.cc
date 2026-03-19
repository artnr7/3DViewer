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

  return;
  // Settings upload
  auto &angles = sett_control_->GetRotAngles();
  obj_->a_.RotateToX(angles.x);
  obj_->a_.RotateToY(angles.y);
  obj_->a_.RotateToY(angles.z);

  auto &rates = sett_control_->GetRotAngles();
  obj_->a_.TranslateToX(rates.x);
  obj_->a_.TranslateToY(rates.y);
  obj_->a_.TranslateToZ(rates.z);

  obj_->a_.Scale(sett_control_->GetScaleRate());
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
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.TranslateToX(x);
  obj_->a_.UpdateGLVertices();
}
void Model::TranslateToY(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.TranslateToY(x);
  obj_->a_.UpdateGLVertices();
}
void Model::TranslateToZ(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.TranslateToZ(x);
  obj_->a_.UpdateGLVertices();
}

void Model::TranslateOnX(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.TranslateOnX(x);
  obj_->a_.UpdateGLVertices();
}

void Model::TranslateOnY(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.TranslateOnY(x);
  obj_->a_.UpdateGLVertices();
}

void Model::TranslateOnZ(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));
}

void Model::RotateToX(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.RotateToX(x);
  obj_->a_.UpdateGLVertices();
}
void Model::RotateToY(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.RotateToY(x);
  obj_->a_.UpdateGLVertices();
}
void Model::RotateToZ(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.RotateToZ(x);
  obj_->a_.UpdateGLVertices();
}
void Model::RotateOnX(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.RotateOnX(x);
  obj_->a_.UpdateGLVertices();
}
void Model::RotateOnY(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.RotateOnY(x);
  obj_->a_.UpdateGLVertices();
}
void Model::RotateOnZ(float x) {
  Lg::Log()->Trace("Model::" + std::string(__func__));

  obj_->a_.RotateOnZ(x);
  obj_->a_.UpdateGLVertices();
}

void Model::ScaleObject(float x) {
  Lg::Log()->Info("Model::" + std::string(__func__));
  obj_->a_.Scale(x);
  obj_->a_.UpdateGLVertices();
}

} // namespace s21
