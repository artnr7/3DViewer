#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../api/controller_interface.h"
#include <../api/model_interface.h>
#include <memory>
#include <qpixelformat.h>
#include <vector>

namespace s21 {

class Controller : public IController {

public:
  Controller(IModel *model) : model_(model) {
    testdata_ = CModelData();
    testdata_.background_color = RGBColor(128, 128, 128);
  }
  ~Controller() = default;

private:
  CModelData testdata_;
  // DATA -------------------------
  std::unique_ptr<IModel> model_;

  // METHODS ------------------------
  void BuildObject(const std::string &filename) override;

  // SETTERS -------------------------------
  void TranslateToX(float x) override;
  void TranslateToY(float x) override;
  void TranslateToZ(float x) override;

  void TranslateOnX(float x) override;
  void TranslateOnY(float x) override;
  void TranslateOnZ(float x) override;

  void RotateX(float) override;
  void RotateY(float) override;
  void RotateZ(float) override;

  void ScaleObject(float) override;

  void SetVertexSize() override;
  void SetVertexStyle() override;
  void SetVertexColor() override;
  void SetVertexThickness() override;
  void SetEdgeStyle() override;
  void SetEdgeColor() override;
  void SetBackgroundColor(int r, int g, int b) override;

  // GETTERS -------------------------------
  // get glvertices
  std::vector<float> &GetGLVertices() override;
  std::vector<uint> &GetEBO() override;

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
