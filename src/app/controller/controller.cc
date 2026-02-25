#include "../utils/logger.h"
#include <controller.h>
#include <string>

namespace s21 {

void Controller::BuildObject(const std::string &filename) {
  Lg::Log()->Info("Controller::" + std::string(__func__));
  model_->BuildObject(filename);
}

// SETTERS -------------------------------
void Controller::TranslateObject() {}
void Controller::RotateObject() {}
void Controller::ScaleObject() {}

void Controller::SetVertexSize() {}
void Controller::SetVertexStyle() {}
void Controller::SetVertexColor() {}
void Controller::SetVertexThickness() {}
void Controller::SetEdgeStyle() {}
void Controller::SetEdgeColor() {}
void Controller::SetBackgroundColor(int r, int g, int b) {
  testdata_.background_color.r = r;
  testdata_.background_color.g = g;
  testdata_.background_color.b = b;
}

// GETTERS -------------------------------
std::vector<float> &Controller::GetGLVertices() {
  return model_->GetGLVertices();
}
//
void Controller::GetVertexSize() {}
void Controller::GetVertexStyle() {}
void Controller::GetVertexColor() {}
void Controller::GetVertexThickness() {}
void Controller::GetEdgeStyle() {}
void Controller::GetEdgeColor() {}
void Controller::GetBackgroundColor() {}

Controller::CModelData &Controller::GetCModelData() {
  // Lg::Log()->Info("Controller::" + std::string(__func__));
  return testdata_;
}
} // namespace s21
