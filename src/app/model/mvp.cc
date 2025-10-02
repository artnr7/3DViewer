#include "model.hpp"

// mvp_ = m_projection * m_view_ *  m_model_
// m_model = m_translate  * m_rotate * m_scale

void s21::Model::MatrixCombination() {
  mvp_ = m_projection_ * m_view_ * obj_->GetModelMatrix();

  for (auto &el : obj_->GetVertices()) {
    QVector4D vec = {(float)el.x, (float)el.y, (float)el.z, 1.0};
    vec = mvp_ * vec;
    el.x = vec.x();
    el.y = vec.y();
    el.z = vec.z();
  }
}


void s21::Model::PerspectiveProjectionMatrix(const int &w, const int &h) {
  obj_->SetToIdentityIfNot(m_projection_);
  float angle = 45.0f;
  float near_plane = 0.01f;
  float far_plane = 100.0f;

  m_projection_.perspective(angle, w / float(h), near_plane, far_plane);
}

void s21::Model::OrthoProjectionMatrix() {
  obj_->SetToIdentityIfNot(m_projection_);
  float near_plane = 0.01f;
  float far_plane = 100.0f;

  m_projection_.ortho(-0.005523, 0.005523, -0.004142, 0.004142, near_plane,
                      far_plane);
}

void s21::Model::LookAt(const QVector3D &eye, const QVector3D &center,
                        const QVector3D &up) {
  obj_->SetToIdentityIfNot(m_view_);
  m_view_.lookAt(eye, center, up);
}