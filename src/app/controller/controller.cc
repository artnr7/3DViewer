#include <controller.h>
#include <string>

namespace s21 {

void Controller::BuildObject(const std::string &filename) {
  model_->BuildObject(filename);
}

std::vector<float> &Controller::GetGLVertices() {
  return model_->GetGLVertices();
};

void Controller::TranslateObject() {}
void Controller::RotateObject() {}
void Controller::ScaleObject() {}

} // namespace s21
