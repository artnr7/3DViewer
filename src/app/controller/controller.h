#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <../controller_interface/interface.h>
#include <../model_interface/interface.h>
#include <memory>
#include <vector>

namespace s21 {

class Controller : public IController {

public:
  Controller(IModel *model) : model_(model) {};
  ~Controller() = default;

private:
  // DATA -------------------------
  std::unique_ptr<IModel> model_;

  // METHODS ------------------------
  void BuildObject(const std::string &filename) override;

  std::vector<float> &GetGLVertices() override;

  void TranslateObject() override;
  void RotateObject() override;
  void ScaleObject() override;
};

} // namespace s21

#endif // !CONTROLLER_H_
