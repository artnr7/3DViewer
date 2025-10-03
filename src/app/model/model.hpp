#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "object_class/object_class.hpp"

namespace s21 {
class Model {
 protected:
  Model() = default;

 private:
  // Variables ----------→
  static std::unique_ptr<Model> instance;
  std::unique_ptr<Object> obj_;
  std::string obj_filename_;

  // Matrices
  QMatrix4x4 m_projection_;
  QMatrix4x4 m_view_;
  QMatrix4x4 mvp_;

 public:
  // Matrix methods ----------→
  void MatrixCombination();

  // Projection -------→
  void PerspectiveProjectionMatrix(const int &w, const int &h);
  void OrthoProjectionMatrix();
  void LookAt(const QVector3D &eye, const QVector3D &center,
              const QVector3D &up);

  void SetDefaultLookAt();

  // Constructors ----------→

  static Model *GetModel() {
    if (instance == nullptr) {
      instance = std::unique_ptr<Model>(new Model());
    }
    return instance.get();
  }

  std::vector<float> *GetGLVertices();
  void CreateNewObject(const std::string &obj_filename);
};

}  // namespace s21

#endif