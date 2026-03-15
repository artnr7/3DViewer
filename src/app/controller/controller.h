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
    testdata_.vertex_color = RGBColor(2, 255, 255);

    testdata_.edge_color = RGBColor(255, 255, 128);
    testdata_.edge_thickness = 0.5f;

    testdata_.vertex_size = 4.0f;

    testdata_.edge_style = 0;
    testdata_.vertex_style = 0;
  }
  ~Controller() = default;

private:
  CModelData testdata_;
  // DATA -------------------------
  IModel *model_;

  // METHODS ------------------------
  void BuildObject(const std::string &filename) override;

  // SETTERS -------------------------------
  void TranslateToX(float x) override;
  void TranslateToY(float x) override;
  void TranslateToZ(float x) override;

  void TranslateOnX(float x) override;
  void TranslateOnY(float x) override;
  void TranslateOnZ(float x) override;

  void RotateToX(float) override;
  void RotateToY(float) override;
  void RotateToZ(float) override;

  void RotateOnX(float) override;
  void RotateOnY(float) override;
  void RotateOnZ(float) override;

  void ScaleObject(float) override;

  void SetVertexSize(float) override;
  void SetVertexStyle(int x) override;
  void SetVertexColor(int r, int g, int b) override;

  void SetEdgeThickness(float) override;
  void SetEdgeStyle(int x) override;
  void SetEdgeColor(int r, int g, int b) override;
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
