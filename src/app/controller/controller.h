#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <../controller_interface/interface.h>
#include <../model_interface/interface.h>
#include <memory>
#include <qpixelformat.h>
#include <vector>

namespace s21 {

class Controller : public IController {

public:
  Controller(IModel *model) : model_(model) {
    testdata_ = CModelData();
    testdata_.background_color = RGBColor(255, 120, 50);
  }
  ~Controller() = default;

private:
  CModelData testdata_;
  // DATA -------------------------
  std::unique_ptr<IModel> model_;

  // METHODS ------------------------
  void BuildObject(const std::string &filename) override;

  // SETTERS -------------------------------
  void TranslateObject() override;
  void RotateObject() override;
  void ScaleObject() override;

  void SetVertexSize() override;
  void SetVertexStyle() override;
  void SetVertexColor() override;
  void SetVertexThickness() override;
  void SetEdgeStyle() override;
  void SetEdgeColor() override;
  void SetBackgroundColor() override;

  // GETTERS -------------------------------
  // get glvertices
  std::vector<float> &GetGLVertices() override;

  //
  void GetVertexSize() override;
  void GetVertexStyle() override;
  void GetVertexColor() override;
  void GetVertexThickness() override;
  void GetEdgeStyle() override;
  void GetEdgeColor() override;
  void GetBackgroundColor() override;

  CModelData &GetCModelData() override;
};

} // namespace s21

#endif // !CONTROLLER_H_
