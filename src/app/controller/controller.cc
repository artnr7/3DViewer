#include "controller.h"
#include "../utils/logger.h"
#include "iostream"
#include <string>

namespace s21 {

void Controller::BuildObject(const std::string &filename) {
  Lg::Log()->Info("Controller::" + std::string(__func__));
  model_->BuildObject(filename);
}

// SETTERS -------------------------------
void Controller::TranslateToX(float x) {
  // std::cout << "\n\n\n\n\n" << x << "\n\n\n\n";
  model_->TranslateToX(x);
}
void Controller::TranslateToY(float x) { model_->TranslateToY(x); }
void Controller::TranslateToZ(float x) { model_->TranslateToZ(x); }

void Controller::TranslateOnX(float x) { model_->TranslateOnX(x); }
void Controller::TranslateOnY(float x) { model_->TranslateOnY(x); }
void Controller::TranslateOnZ(float x) {}

void Controller::RotateToX(float x) { model_->RotateToX(x); }
void Controller::RotateToY(float x) { model_->RotateToY(x); }
void Controller::RotateToZ(float x) { model_->RotateToZ(x); }

void Controller::RotateOnX(float x) { model_->RotateOnX(x); }
void Controller::RotateOnY(float x) { model_->RotateOnY(x); }
void Controller::RotateOnZ(float x) { model_->RotateOnZ(x); }

void Controller::ScaleObject(float x) { model_->ScaleObject(x); }

void Controller::SetVertexSize(float x) { testdata_.vertex_size = x; }
void Controller::SetVertexStyle(int x) { testdata_.vertex_style = x; }
void Controller::SetVertexColor(int r, int g, int b) {
  testdata_.vertex_color.r = r;
  testdata_.vertex_color.g = g;
  testdata_.vertex_color.b = b;
}

void Controller::SetEdgeThickness(float x) { testdata_.edge_thickness = x; }
void Controller::SetEdgeStyle(int x) { testdata_.edge_style = x; }
void Controller::SetEdgeColor(int r, int g, int b) {
  testdata_.edge_color.r = r;
  testdata_.edge_color.g = g;
  testdata_.edge_color.b = b;
}

void Controller::SetBackgroundColor(int r, int g, int b) {
  testdata_.background_color.r = r;
  testdata_.background_color.g = g;
  testdata_.background_color.b = b;
}

// GETTERS -------------------------------
std::vector<float> &Controller::GetGLVertices() {
  return model_->GetGLVertices();
}
std::vector<uint> &Controller::GetEBO() { return model_->GetEBO(); }
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
