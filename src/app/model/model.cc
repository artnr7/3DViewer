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
  obj_->a_.RotateToX(sett_control_->GetRotAngleX());
  obj_->a_.RotateToY(sett_control_->GetRotAngleY());
  obj_->a_.RotateToZ(sett_control_->GetRotAngleZ());

  obj_->a_.TranslateToX(sett_control_->GetTransFactorX());
  obj_->a_.TranslateToY(sett_control_->GetTransFactorY());
  obj_->a_.TranslateToZ(sett_control_->GetTransFactorZ());

  obj_->a_.Scale(sett_control_->GetScaleFactor());
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
